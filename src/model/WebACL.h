
#ifndef WEBACL_H
#define WEBACL_H 
 
#include <vector>
#include <string>
#include <iostream>


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
     * Create new account.
     * @para user_name name of user account.
     * @para password password of user.
     **/      
    void static createAccount (  
            std::string user_name, 
            std::string new_password     
    );    
    
    /**
     * Create new account.
     * @para user_name name of user account.
     * @para password password of user.
     * @para real_name real name of user.
     * @para email email of user.
     **/      
    void static createAccount (  
            std::string user_name, 
            std::string new_password,  
            std::string real_name = "",
            std::string email = ""        
    );
    
    /**
     * Check is user in database exist.
     * @para user_name name of the user.
     * @return true = exist, false = no exist.
     **/ 
    static bool isUserExist ( std::string user_name );
    
    /**
     * Get back the role from a user.
     * @para user_name name of the user.
     * @return list of user roles
     **/ 
    static std::list<std::string> getRole ( std::string user_name );
    
    /**
     * Set a new password from a user.
     * @para user_name name of the user.
     * @para new_password new password phrase.
     **/     
    void setPassword (  std::string user_name, std::string new_password );
    
private:
    /**
     * Generated a random string for password salt.
     * @para len length of sting.
     * @return a random string
     */
    std::string static genRandomSalt ( const int len ) ;

};

#endif 

