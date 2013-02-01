
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

std::list<std::string> WebACL::getRole ( std::string user_name ) {
    std::list<std::string> list_role;
    return list_role;
    
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
    } catch ( char * errstr ) {
        ERROR "Exception raised: " << errstr << '\n';
    }

}