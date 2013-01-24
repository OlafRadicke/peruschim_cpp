
#include <string>
#include <list>
#include <iostream>
#include <pqxx/pqxx>

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#include "DatabaseProxy.h"
#include "WebACL.h"

# define DEBUG cout << "[WebACL]" <<

bool WebACL::authUser ( std::string user_name, std::string password ) {
    DatabaseProxy database_proxy;
    
//     C++-style    
    std::string password_2 = "Original String";
    unsigned char hash[20];
    SHA1( (unsigned char *)password_2.c_str(), password_2.length(), hash);
    DEBUG hash << std::endl;
  
//     C-style
//     const char ibuf[] = "compute sha1";
//     unsigned char obuf[20];
//     SHA1( (unsigned char *)ibuf, strlen(ibuf), obuf); 
//     DEBUG obuf << std::endl;
    
    return false;
}

void WebACL::connectDataBase (){
    
}

std::list<std::string> WebACL::getRole ( std::string user_name ) {
    std::list<std::string> list_role;
    return list_role;
    
}

