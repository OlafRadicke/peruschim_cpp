
#ifndef WEBACL_H
#define WEBACL_H 
 
#include <vector>
#include <string>
#include <iostream>

//#include <pgxx/pgxx>

class WebACL {
    
public: 
    
    /**
     * verifies the authenticity.
     * @para user_name name of user.
     * @para password password of user.
     * @return "true" if okay, else "false".
     **/     
    bool static authUser ( std::string user_name, std::string password );
    
    /**
     * Open connatct with database.
     * */
    void connectDataBase ();
    
    /**
     * Get back the role from a user.
     * @para user_name name of the user.
     * @return list of user roles
     **/ 
    static std::list<std::string> getRole ( std::string user_name );

};

#endif 

