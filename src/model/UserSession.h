#ifndef USERSESSION_H
#define USERSESSION_H 

#include <iostream>
#include <vector>
#include <string>

#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>

#include "Config.h"
#include "DatabaseProxy.h"

/**
* This class represent a data set of a session.
**/
class UserSession {
    
public:
    
    
    UserSession () : m_username ( "" ) {};
    
     /**
     * Add a roll.
     * @param roll account roll.
     **/
    void addRoll ( std::string roll ) {
        m_userrolls.push_back ( roll );
    };
    
    /**
     * Add a list of rolls.
     * @param roll list of account rolls.
     **/
    void addRoll ( std::vector<std::string> rolls ) ;
    
    /**
     * Clean the list of rolls.
     **/
    void cleanRoll ( ) { m_userrolls.clear(); } ;
    
    /**
     * Session logout.
     **/
    void lockout( ) ;    
    
    /**
     * Check is user in this site rolle.
     * @param siteroll the roll of this site which are allowed is.
     * @return true or false.
     **/
    bool isInRole ( std::string siteroll ) ; 
    
    /**
     * Check is user in this site rolle.
     * @param siterolls a vector of roll of from the site, which are allowed is.
     * @return true or false.
     **/    
    bool isInRole ( std::vector<std::string> siterolls ) ;
    
    void setUserName ( std::string username ) {
        m_username = username;
    };
    
    /**
     * Get back the user login name.
     * @return login name.
     **/            
    std::string getUserName ( void ) { return m_username; };
    

    /**
     * Get back the user ID.
     * @return ID of user.
     **/            
    std::string getUserID ( void );    
    
private:
    
    /**
     * Rolls of user.
     **/
    std::vector < std::string > m_userrolls;
    
    
    /**
     * Login name
     **/
    std::string m_username;
    
};


#endif 