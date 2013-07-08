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

#include "WebACL.h"
#include "DatabaseProxy.h"
#include <string>

#include <tntdb/connect.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>
#include <cxxtools/md5.h>
#include <cxxtools/log.h>

/* A ----------------------------------------------------------------------- */

log_define("models.WebACL")




bool WebACL::authUser ( const std::string& user_name, const std::string& password )
{
    log_debug("start...");
    std::string password_hash_a;
    std::string password_hash_b;
    std::string password_salt;

    Config config;
    tntdb::Connection conn = tntdb::connectCached(config.dbDriver());

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
    Config config;


    password_salt = WebACL::genRandomSalt ( 16 );
    password_hash = cxxtools::md5 ( new_password + password_salt );

    tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );
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
        conn = tntdb::connectCached( config.dbDriver() );
        st = conn.prepare(
                "SELECT \
                    id \
                FROM account \
                WHERE login_name = :user_name"
        );
        st.set( "user_name", user_name ).execute();
        for ( tntdb::Statement::const_iterator it = st.begin();
            it != st.end();
            ++it
        ) {
            tntdb::Row row = *it;
            user_id = row[0].getInt();
        }

        conn = tntdb::connectCached( config.dbDriver() );
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
        .set( "roll", roll ).execute();

    }

}

/* G ----------------------------------------------------------------------- */


AccountData WebACL::getAccountsWithID ( unsigned long id ){
    Config config;
    tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );

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
    std::string errorinfo = "no account found with this id" + id;
    throw errorinfo;
}

std::vector<AccountData> WebACL::getAllAccounts (){

    std::vector<AccountData> accounts;
    Config config;

    tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );
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

std::string WebACL::genRandomSalt ( const int len) {
    /* initialize random seed: */
    srand (time(NULL));
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

// bis hier

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

void WebACL::reSetUserRolls(
    const unsigned long  user_id,
    const std::vector<std::string> user_rolls
){

    log_debug("reSetUserRolls");
    Config config;
    tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );
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
