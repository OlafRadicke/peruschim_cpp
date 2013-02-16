#ifndef USERSESSION_H
#define USERSESSION_H 

#include <iostream>
#include <vector>
#include <string>

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