
#include <string>
#include <list>
#include <iostream>
#include <pqxx/pqxx>

#include <cxxtools/md5.h>
#include <cxxtools/log.h>

/*
 * openssl-variante
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
*/

#include "DatabaseProxy.h"
#include "WebACL.h"


# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

bool WebACL::authUser ( std::string user_name, std::string password ) {
    DEBUG "start..." << std::endl;
    std::string password_hash_a = "";
    DEBUG std::endl;
    std::string password_hash_b = "";
    DEBUG std::endl;
    std::string masqu_name = "";
    DEBUG std::endl;
    vector< vector<string> > sqlResult;
    DEBUG std::endl;
    DatabaseProxy database_proxy;
    DEBUG std::endl;
    database_proxy.setQuotaType ( "'" );
    DEBUG std::endl;
//     C++-style    
//     std::string password_2 = "Original String";
//     unsigned char hash[20];
//     SHA1( (unsigned char *)password_2.c_str(), password_2.length(), hash);
//     DEBUG hash << std::endl;
  
//     C-style
//     const char ibuf[] = "compute sha1";
//     unsigned char obuf[20];
//     SHA1( (unsigned char *)ibuf, strlen(ibuf), obuf); 
//     DEBUG obuf << std::endl;
    
    // cxxtools-style
    DEBUG std::endl;
    password_hash_a = cxxtools::md5(password);
    DEBUG std::endl;
    // simple password salt
    password_hash_a = cxxtools::md5(password + password_hash_a);
    DEBUG "hexDigest_a " << password_hash_a << std::endl;
//     masqu_name = DatabaseProxy::replace( user_name, "'", "\\'" );
    
    DEBUG std::endl;
    database_proxy.sqlSet( "SELECT password_hash FROM a23i_account WHERE login_name = '" + masqu_name + "';");
    DEBUG std::endl;
    try {
        sqlResult = database_proxy.sqlGet ( "SELECT password_hash FROM a23i_account WHERE login_name = '" + masqu_name + "';");
    } catch ( char * errstr ) {
        ERROR "Exception raised: " << errstr << '\n';
    }
    if ( sqlResult.size() > 0 ) {
        if ( sqlResult[0].size() > 0 ) {
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
    if ( password_hash_b == password_hash_a ) {
        return true;
    } else {
        return false;
    }
}

void WebACL::connectDataBase (){
    
}

std::list<std::string> WebACL::getRole ( std::string user_name ) {
    std::list<std::string> list_role;
    return list_role;
    
}

