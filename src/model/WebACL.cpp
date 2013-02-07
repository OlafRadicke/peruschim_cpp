
#include <string>
#include <list>
#include <iostream>
// #include <pqxx/pqxx>

#include <cxxtools/md5.h>
#include <cxxtools/log.h>

#include "DatabaseProxy.h"
#include "WebACL.h"


# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<





bool WebACL::authUser ( std::string user_name, std::string password ) {
    DEBUG "start..." << std::endl;
    std::string password_hash_a = "";
    std::string password_hash_b = "";
    std::string password_salt = "";
    std::string masqu_name = "";
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;
    database_proxy.setQuotaType ( "'" );
    
    DEBUG std::endl;
    masqu_name = DatabaseProxy::replace( user_name, "'", "\\'" );
    
    // password salt request.
    try {
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet ( "SELECT password_salt FROM a23t_account WHERE login_name = '" + masqu_name + "';");
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
        sqlResult = database_proxy.sqlGet ( "SELECT password_hash FROM a23t_account WHERE login_name = '" + masqu_name + "';");
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
        std::string email        
) {

    DEBUG "start..." << std::endl;
    std::string password_hash = "";
    std::string password_salt = "";
    std::string masqu_name = "";
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;
    database_proxy.setQuotaType ( "'" );
    
    password_salt = WebACL::genRandomSalt ( 16 );
    DEBUG "password_salt: " << password_salt << std::endl;
    password_hash = cxxtools::md5 ( new_password + password_salt );
    DEBUG "password_hash: " <<  password_hash <<  std::endl;
//     masqu_name = DatabaseProxy::replace( user_name, "'", "\\'" );
    masqu_name = DatabaseProxy::replace( user_name );
    
    DEBUG std::endl;
    DEBUG std::endl;
    
    database_proxy.sqlSet( \
        "INSERT INTO a23t_account \
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

}

string WebACL::genRandomSalt ( const int len) {
    string randomString = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        randomString.push_back ( alphanum[rand() % (sizeof(alphanum) - 1)] );
    }

    return randomString;
}

std::vector<std::string> WebACL::getRoll ( std::string user_name ){
    vector<std::string> rolls;
    return rolls;
}

bool WebACL::isUserExist ( std::string user_name ){
    DEBUG "start..." << std::endl;
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;
    DEBUG std::endl;
    try {
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet( "SELECT * FROM a23t_account \
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


void WebACL::setPassword (  std::string user_name, std::string new_password ) {

    DEBUG "start..." << std::endl;
    std::string password_hash = "";
    std::string password_salt = "";
    std::string masqu_name = "";
    vector< vector<string> > sqlResult;
    DatabaseProxy database_proxy;
    database_proxy.setQuotaType ( "'" );
    
    password_salt = genRandomSalt ( 16 );
    DEBUG "password_salt: " << password_salt << std::endl;
    password_hash = cxxtools::md5 ( new_password + password_salt );
    DEBUG "password_hash: " <<  password_hash <<  std::endl;
    masqu_name = DatabaseProxy::replace( user_name, "'", "\\'" );
    
    DEBUG std::endl;
    DEBUG std::endl;
    try {
        DEBUG std::endl;
        database_proxy.sqlSet( "UPDATE a23t_account \
            SET password_hash = '" + password_hash + "',\
            SET password_salt = '" + password_salt + "',\
            WHERE login_name = '" + user_name + "';");
    } catch ( ... ) {
        ERROR "Exception raised with: database_proxy.sqlSet ()" << endl;
    }

}