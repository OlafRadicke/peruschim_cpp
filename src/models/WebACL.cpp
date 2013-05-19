
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
        sqlResult = database_proxy.sqlGet ( "SELECT password_salt FROM account WHERE login_name = '" + masqu_name + "';");
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
        return true;
    } else {
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
    WebACL::createAccount ( user_name, new_password,  "", "");
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

AccountData WebACL::getAccountsWithID ( const std::string id ){
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
        DEBUG "account_disable: "  << row[5].getString() << std::endl;
        if ( row[5].getString() == "true" ) {
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

    DatabaseProxy database_proxy;
    vector< vector<string> > sqlResult;
    vector<AccountData> accounts;

    DEBUG std::endl;
    sqlResult = database_proxy.sqlGet
    (
            "SELECT \
                id, \
                login_name, \
                real_name, \
                password_hash, \
                password_salt, \
                email, \
                account_disable  \
            FROM account;"
    );

    for ( unsigned int i=0; i<sqlResult.size(); i++) {
        DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
        AccountData adata;

        adata.setID ( sqlResult[i][0] );
        adata.setLogin_name ( sqlResult[i][1] );
        adata.setReal_name ( sqlResult[i][2] );
        adata.setPassword_hash ( sqlResult[i][3] );
        adata.setPassword_salt ( sqlResult[i][4] );
        adata.setEmail ( sqlResult[i][5] );
        DEBUG "account_disable (" <<  i << "): " << sqlResult[i][6] << std::endl;
        if ( sqlResult[i][6] == "true" ) {
            DEBUG "true" <<  std::endl;
            adata.setAccount_disable ( true );

        } else {
            DEBUG "false" <<  std::endl;
            adata.setAccount_disable ( false );
        }
        accounts.push_back ( adata );
    }
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
            AND account_acl_roll.acl_roll_id = acl_roll.id ;"
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

/* S ----------------------------------------------------------------------- */

/* S ----------------------------------------------------------------------- */


void WebACL::setPassword (  std::string user_name, std::string new_password ) {

    DEBUG "start..." << std::endl;
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
