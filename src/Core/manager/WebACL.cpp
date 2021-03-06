/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or later
* version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <Core/models/DatabaseProxy.h>
#include <Core/models/PeruschimException.h>
#include <Core/manager/RSSfeedManager.h>
#include <Core/manager/WebACL.h>

#include <tntdb/connect.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>
#include <cxxtools/md5.h>
#include <cxxtools/log.h>

#include <string>


/* A ----------------------------------------------------------------------- */

log_define("models.WebACL")

bool WebACL::authUser ( const std::string& user_name, const std::string& password )
{
    log_debug("start...");
    std::string password_hash_a;
    std::string password_hash_b;
    std::string password_salt;

    tntdb::Connection conn = tntdb::connectCached(Config::it().dbDriver());

    // password salt request.
    try
    {
        tntdb::Statement sel = conn.prepare(
            "SELECT password_salt, password_hash \
               FROM account \
              WHERE login_name = :login_name \
                AND NOT account_disable");

        tntdb::Row row = sel.set("login_name", user_name).selectRow();

        row[0].get(password_salt);
        row[1].get(password_hash_b);

        log_debug( "password_salt: " << password_salt << " password_hash_b: " << password_hash_b);
    }
    catch ( const tntdb::NotFound& )
    {
        log_error("User not found in data base?");
        return false;
    }

    password_hash_a = cxxtools::md5 ( password + password_salt );
    log_debug("password_hash_a: " << password_hash_a);

    // is equal ?
    if ( password_hash_b == password_hash_a )
    {
        log_debug("Passwort ist richtig");
        return true;
    }
    else
    {
        log_debug("Passwort ist falsch");
        log_debug("password_hash_b: " << password_hash_b);
        log_debug("password_hash_a: " << password_hash_a);
        return false;
    }
}


/* C ----------------------------------------------------------------------- */

void WebACL::createAccount (
        std::string user_name,
        std::string new_password
) {
    WebACL::createAccount ( user_name, new_password,  "", "", "user");
}


void WebACL::createAccount (
        std::string user_name,
        std::string new_password,
        std::string real_name,
        std::string email,
        std::string roll
) {

    log_debug("start...");
    std::string password_hash = "";
    std::string password_salt = "";
    unsigned long user_id = 0;

    password_salt = WebACL::genRandomSalt ( 16 );
    password_hash = cxxtools::md5 ( new_password + password_salt );

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Statement st = conn.prepare(
        "INSERT INTO account \
        (   login_name, \
            real_name, \
            password_hash, \
            password_salt, \
            email, \
            account_disable )\
        VALUES \
        (   :user_name,  \
            :real_name,  \
            :password_hash,  \
            :password_salt,  \
            :email,  \
            'FALSE'  \
        );"
    );
    st.set("user_name", user_name )
    .set("real_name", real_name )
    .set("password_hash", password_hash )
    .set("password_salt", password_salt )
    .set("email", email ).execute();


    if ( roll != "" ) {
        user_id = conn.lastInsertId();

        st = conn.prepare(

            "INSERT INTO account_acl_roll \
                ( account_id, acl_roll_id )\
            VALUES \
                ( :user_id,  \
                    ( SELECT id FROM acl_roll \
                      WHERE name = :roll ) \
                )"
        );
        st.set( "user_id", user_id )
          .set( "roll", roll )
          .execute();

    }

    RSSfeed newFeed;
    newFeed.setTitle( "Neuer Account" );
    std::string description = "Der Account mit der ID "
        + cxxtools::convert<std::string>( user_id ) \
        + " wurde neu erstellt. Als Login wurde \"" + user_name
        + "\" gewählt, und als real name: \"" + real_name + "\".";
    newFeed.setDescription( description );
    newFeed.channels.push_back("account");
    RSSfeedManager feedManager;
    feedManager.addNewFeed( newFeed );

}

/* G ----------------------------------------------------------------------- */

AccountData WebACL::getAccountsWithID ( unsigned long id ){
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );

    tntdb::Statement st = conn.prepare( "SELECT \
                login_name, \
                real_name, \
                password_hash, \
                password_salt, \
                email, \
                account_disable  \
            FROM account \
            WHERE id = :v1;");
    st.set( "v1", id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        AccountData adata;

        adata.setID ( id );
        adata.setLogin_name ( row[0].getString() );
        adata.setReal_name ( row[1].getString() );
        adata.setPassword_hash ( row[2].getString() );
        adata.setPassword_salt ( row[3].getString() );
        adata.setEmail ( row[4].getString() );
        log_debug("account_disable: "  << row[5].getBool());
//         if ( row[5].getString() == "t" ) {
        if ( row[5].getBool() ) {
            log_debug("true");
            adata.setAccount_disable ( true );

        } else {
            log_debug("false");
            adata.setAccount_disable ( false );
        }
        return adata;
    }

    std::stringstream errorText;
    errorText << "no account found with this id" << id;
    log_debug( errorText );
    throw Core::PeruschimException( errorText.str() );
}

std::vector<AccountData> WebACL::getAllAccounts (){

    std::vector<AccountData> accounts;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Statement st = conn.prepare(
            "SELECT \
                id, \
                login_name, \
                real_name, \
                password_hash, \
                password_salt, \
                email, \
                account_disable  \
            FROM account \
            ORDER BY login_name"
    );
    st.execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
//         Edition edition;
        AccountData accountData;

        accountData.setID( row[0].getInt() );
        accountData.setLogin_name( row[1].getString () );
        accountData.setReal_name( row[2].getString () );
        accountData.setPassword_hash( row[3].getString () );
        accountData.setPassword_salt( row[4].getString () );
        accountData.setEmail( row[5].getString () );
        accountData.setAccount_disable( row[5].getBool () );

        accounts.push_back ( accountData );
    }

    log_debug("accounts.size(): " <<  accounts.size());
    return accounts;

}

std::vector<std::string> WebACL::getAllRolls ( ){
    DatabaseProxy database_proxy;
    std::vector< std::vector<std::string> > sqlResult;
    std::vector<std::string> rolls;

    sqlResult = database_proxy.sqlGet
    (
            "SELECT DISTINCT name FROM acl_roll ORDER BY name;"
    );

    for ( unsigned int i=0; i<sqlResult.size(); i++) {
        log_debug("push_back (" <<  i << "): " << sqlResult[i][0]);
        rolls.push_back ( sqlResult[i][0] );
    }
    return rolls;
}


std::string WebACL::genRandomSalt ( const int len) {
    // Set this in the main-function... initialize random seed: */
    //srand (time(NULL));

    std::string randomString = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        int randNo = rand() % (sizeof(alphanum) - 1) ;
        log_debug("randNo: " << randNo);
        randomString.push_back ( alphanum[randNo] );
    }
    return randomString;
}


std::vector<std::string> WebACL::getRoll ( const std::string& user_name ){
    DatabaseProxy database_proxy;
    std::vector< std::vector<std::string> > sqlResult;
    std::vector<std::string> rolls;

    sqlResult = database_proxy.sqlGet
    (
            "SELECT acl_roll.name \
            FROM acl_roll, account, account_acl_roll \
            WHERE account.login_name = '" + DatabaseProxy::replace( user_name ) + "' \
            AND account.id = account_acl_roll.account_id  \
            AND account_acl_roll.acl_roll_id = acl_roll.id \
            ORDER BY acl_roll.name;"
    );

    for ( unsigned int i=0; i<sqlResult.size(); i++) {
        log_debug("push_back (" <<  i << "): " << sqlResult[i][0]);
        rolls.push_back ( sqlResult[i][0] );
    }


    return rolls;
}


std::vector<AccountData> WebACL::getSearchAccounts( const std::string& serach_string_ ) {
    std::string serach_string = "%" + serach_string_ + "%";
    std::vector<AccountData> accounts;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Statement st = conn.prepare(
            "SELECT \
                id, \
                login_name, \
                real_name, \
                password_hash, \
                password_salt, \
                email, \
                account_disable  \
            FROM account \
            WHERE login_name LIKE :search \
            OR real_name LIKE :search \
            ORDER BY login_name"
    );
    st.set( "search", serach_string ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        AccountData accountData;

        accountData.setID( row[0].getInt() );
        accountData.setLogin_name( row[1].getString () );
        accountData.setReal_name( row[2].getString () );
        accountData.setPassword_hash( row[3].getString () );
        accountData.setPassword_salt( row[4].getString () );
        accountData.setEmail( row[5].getString () );
        accountData.setAccount_disable( row[5].getBool () );

        accounts.push_back ( accountData );
    }

    log_debug("accounts.size(): " <<  accounts.size());
    return accounts;

}



/* I ----------------------------------------------------------------------- */


bool WebACL::isUserExist ( std::string user_name ){
    log_debug("start...");
    std::vector< std::vector<std::string> > sqlResult;
    DatabaseProxy database_proxy;
    try {
        sqlResult = database_proxy.sqlGet( "SELECT * FROM account \
            WHERE login_name = '" + DatabaseProxy::replace( user_name ) + "';");
    } catch ( ... ) {
        log_error("Exception raised with: database_proxy.sqlSet ()");
        return false;
    }
    if ( sqlResult.size() > 0 ) {
        return true;
    } else {
        return false;
    }
}

bool WebACL::isUserInRole ( const std::string login_name, const std::string roll ) {
    std::vector<std::string> userroles = WebACL::getRoll( login_name );
    log_debug("m_userroles.size(): " << userroles.size());

    for ( unsigned int i=0; i< userroles.size(); i++) {
        if ( userroles[i] == roll ) {
            return true;
        }
    }
    return false;
}

/* S ----------------------------------------------------------------------- */



void WebACL::setPassword (  std::string user_name, std::string new_password ) {
    std::string password_hash = "";
    std::string password_salt = "";
    std::string masqu_name = "";
    std::vector< std::vector<std::string> > sqlResult;
    DatabaseProxy database_proxy;

    password_salt = genRandomSalt ( 16 );
    log_debug("password_salt: " << password_salt);
    password_hash = cxxtools::md5 ( new_password + password_salt );
    log_debug("password_hash: " <<  password_hash);

    try {
        database_proxy.sqlSet( "UPDATE account \
            SET password_hash = '" + password_hash + "',\
            SET password_salt = '" + password_salt + "',\
            WHERE login_name = '" + user_name + "';");
    } catch ( ... ) {
        log_error("Exception raised with: database_proxy.sqlSet ()");
    }

}


/* R ----------------------------------------------------------------------- */

void WebACL::reSetUserRolls(
    const unsigned long  user_id,
    const std::vector<std::string> user_rolls
){

    log_debug("reSetUserRolls");
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Statement st = conn.prepare( "DELETE FROM account_acl_roll \
                WHERE account_id = :v1;");
    st.set( "v1", user_id ).execute();

    for ( unsigned int i_roll = 0; i_roll < user_rolls.size(); i_roll++ ) {
        log_debug("user_rolls[i_roll]: " << user_rolls[i_roll]);
        tntdb::Statement st = conn.prepare( "INSERT INTO account_acl_roll  \
                    ( account_id, acl_roll_id ) \n \
                    VALUES \n \
                    ( :v1, ( SELECT id FROM acl_roll WHERE name= :v2 ) );");
        st.set( "v1", user_id )
        .set( "v2", user_rolls[i_roll] ).execute();
    }
}
