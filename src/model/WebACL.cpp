
#include <string>
#include <list>
#include <iostream>
#include <pqxx/pqxx>
 
#include "WebACL.h"


bool WebACL::authUser ( std::string user_name, std::string password ) {
    return false;
}

void WebACL::connectDataBase (){
    
}

std::list<std::string> WebACL::getRole ( std::string user_name ) {
    std::list<std::string> list_role;
    return list_role;
    
}

