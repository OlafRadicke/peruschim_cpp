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

#include <string>
#include <list>
#include <iostream>

#include <cxxtools/md5.h>
#include <cxxtools/log.h>

#include "DatabaseProxy.h"
#include "WebACL.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
/* A ----------------------------------------------------------------------- */


bool WebACL::authUser ( std::string user_name, std::string password ) {
    DEBUG "start..." << std::endl;
    std::string password_hash_a = "";
    std::string password_hash_b = "";
    std::string password_salt = "";
    std::string masqu_name = "";
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;

    DEBUG std::endl;
    masqu_name = DatabaseProxy::replace( user_name, "'", "\\'" );

    // password salt request.
    try {
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet ( "SELECT password_salt \
             FROM account \
             WHERE login_name = '" + masqu_name + "' \
             AND account_disable IS NOT TRUE ;");
    } catch ( char * errstr ) {
        ERROR "Exception raised: " << errstr << '\n';
    }
    if ( sqlResult.size() > 0 ) {
        DEBUG std::endl;
        if ( sqlResult[0].size() > 0 ) {
            DEBUG std::endl;
            password_salt = sqlResult[0][0];
            DEBUG "password_sal: " << password_salt << std::endl;
        } else {
            DEBUG "The sql result has not column." << std::endl;
            return false;
        }
    } else {
//        Logger::Logger ( "User not foaunt in data base?", Logger::LOG_LEVEL_WARN );
        ERROR "User not foaunt in data base?" << std::endl;
        return false;
    }

    password_hash_a = cxxtools::md5 ( password + password_salt );
    DEBUG "password_hash_a: " << password_hash_a << std::endl;

    DEBUG std::endl;
    try {
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet ( "SELECT password_hash FROM account WHERE login_name = '" + masqu_name + "';");
    } catch ( char * errstr ) {
        ERROR "Exception raised: " << errstr << '\n';
    }
    if ( sqlResult.size() > 0 ) {
        DEBUG std::endl;
        if ( sqlResult[0].size() > 0 ) {
            DEBUG std::endl;
            password_hash_b = sqlResult[0][0];
        } else {
            DEBUG "The sql result has not column." << std::endl;
            return false;
        }
    } else {
//        Logger::Logger ( "User not foaunt in data base?", Logger::LOG_LEVEL_WARN );
        ERROR "User not foaunt in data base?" << std::endl;
        return false;
    }

    // is equal ?
    if ( password_hash_b == password_hash_a ) {
        DEBUG "Passwor ist rihtig" << std::endl;
        return true;
    } else {
        DEBUG "Passwor ist falsch" << std::endl;
        DEBUG "password_hash_b: " << password_hash_b << std::endl;
        DEBUG "password_hash_a: " << password_hash_a << std::endl;
        return false;
    }
}


/* C ----------------------------------------------------------------------- */

void WebACL::connectDataBase (){

}

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

    DEBUG "start..." << std::endl;
    std::string password_hash = "";
    std::string password_salt = "";
    std::string masqu_name = "";
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;

    password_salt = WebACL::genRandomSalt ( 16 );
    password_hash = cxxtools::md5 ( new_password + password_salt );
    masqu_name = DatabaseProxy::replace( user_name );

    database_proxy.sqlSet( \
        "INSERT INTO account \
        ( login_name, real_name, password_hash, password_salt, email, account_disable )\
        VALUES \
        ( '" + DatabaseProxy::replace( user_name ) + "',  \
            '" + DatabaseProxy::replace( real_name ) + "',  \
            '" + DatabaseProxy::replace( password_hash ) + "',  \
            '" + DatabaseProxy::replace( password_salt ) + "',  \
            '" + DatabaseProxy::replace( email ) + "',  \
            'FALSE'  \
        );"
    );

    if ( roll != "" ) {
        std::string sqlcommand =    "SELECT \n\
                            id \n\
                        FROM account \n\
                        WHERE login_name='" + DatabaseProxy::replace( user_name ) + "';";
        string user_id = database_proxy.sqlGetSingle ( sqlcommand );
        database_proxy.sqlSet( \
            "INSERT INTO account_acl_roll \
                ( account_id, acl_roll_id )\
            VALUES \
                ( " + user_id + ",  \
                    ( SELECT id FROM acl_roll \
                      WHERE name = '" + DatabaseProxy::replace( roll ) + "' ) \
                );"
         );

    }

}

/* G ----------------------------------------------------------------------- */

AccountData WebACL::getAccountsWithID ( const unsigned long id ){
    Config config;
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

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
        DEBUG "account_disable: "  << row[5].getBool() << std::endl;
//         if ( row[5].getString() == "t" ) {
        if ( row[5].getBool() ) {
            DEBUG "true" <<  std::endl;
            adata.setAccount_disable ( true );

        } else {
            DEBUG "false" <<  std::endl;
            adata.setAccount_disable ( false );
        }
        return adata;
    }
    std::string errorinfo = "no account found with this id" + id;
    throw errorinfo;
}

std::vector<AccountData> WebACL::getAllAccounts ( void ){

    DEBUG  std::endl;
    std::vector<AccountData> accounts;
    Config config;
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

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

    DEBUG "accounts.size(): " <<  accounts.size() << std::endl;
    return accounts;

}

string WebACL::genRandomSalt ( const int len) {
    /* initialize random seed: */
    srand (time(NULL));
    string randomString = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        int randNo = rand() % (sizeof(alphanum) - 1) ;
        DEBUG "randNo: " << randNo << endl;
        randomString.push_back ( alphanum[randNo] );
    }
    return randomString;
}

std::vector<std::string> WebACL::getAllRolls ( ){
    DatabaseProxy database_proxy;
    vector< vector<string> > sqlResult;
    vector<std::string> rolls;

    DEBUG std::endl;
    sqlResult = database_proxy.sqlGet
    (
            "SELECT DISTINCT name FROM acl_roll ORDER BY name;"
    );

    for ( unsigned int i=0; i<sqlResult.size(); i++) {
        DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
        rolls.push_back ( sqlResult[i][0] );
    }
    return rolls;
}


std::vector<std::string> WebACL::getRoll ( std::string user_name ){
    DatabaseProxy database_proxy;
    vector< vector<string> > sqlResult;
    vector<std::string> rolls;

    DEBUG std::endl;
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
        DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
        rolls.push_back ( sqlResult[i][0] );
    }


    return rolls;
}

/* I ----------------------------------------------------------------------- */

bool WebACL::isUserExist ( std::string user_name ){
    DEBUG "start..." << std::endl;
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;
    DEBUG std::endl;
    try {
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet( "SELECT * FROM account \
            WHERE login_name = '" + DatabaseProxy::replace( user_name ) + "';");
    } catch ( ... ) {
        ERROR "Exception raised with: database_proxy.sqlSet ()" << endl;
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
    DEBUG "m_userroles.size(): " << userroles.size() << std::endl;

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
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;

    password_salt = genRandomSalt ( 16 );
    DEBUG "password_salt: " << password_salt << std::endl;
    password_hash = cxxtools::md5 ( new_password + password_salt );
    DEBUG "password_hash: " <<  password_hash <<  std::endl;

    DEBUG std::endl;
    DEBUG std::endl;
    try {
        DEBUG std::endl;
        database_proxy.sqlSet( "UPDATE account \
            SET password_hash = '" + password_hash + "',\
            SET password_salt = '" + password_salt + "',\
            WHERE login_name = '" + user_name + "';");
    } catch ( ... ) {
        ERROR "Exception raised with: database_proxy.sqlSet ()" << endl;
    }

}

void WebACL::reSetUserRolls(
    const unsigned long  user_id,
    const std::vector<std::string> user_rolls
){

    DEBUG "reSetUserRolls" << std::endl;
    Config config;
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

    tntdb::Statement st = conn.prepare( "DELETE FROM account_acl_roll \
                WHERE account_id = :v1;");
    st.set( "v1", user_id ).execute();

    for ( unsigned int i_roll = 0; i_roll < user_rolls.size(); i_roll++ ) {
        DEBUG "user_rolls[i_roll]: " << user_rolls[i_roll] << std::endl;
        tntdb::Statement st = conn.prepare( "INSERT INTO account_acl_roll  \
                    ( account_id, acl_roll_id ) \n \
                    VALUES \n \
                    ( :v1, ( SELECT id FROM acl_roll WHERE name= :v2 ) );");
        st.set( "v1", user_id )
        .set( "v2", user_rolls[i_roll] ).execute();
    }
}
