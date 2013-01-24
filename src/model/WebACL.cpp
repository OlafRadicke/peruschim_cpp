
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
    
    std::string password_2 = "Original String";
    unsigned char hash[20];
    SHA1( password_2.c_str(), password_2.length(), hash);
    DEBUG hash << std::endl;
    
    return false;
}

void WebACL::connectDataBase (){
    
}

std::list<std::string> WebACL::getRole ( std::string user_name ) {
    std::list<std::string> list_role;
    return list_role;
    
}

