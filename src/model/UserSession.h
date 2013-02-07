#ifndef USERSESSION_H
#define USERSESSION_H 

#include <iostream>
#include <vector>
#include <string>

class UserSession {
    
public:
    UserSession ();
    
     /**
     * Add a roll.
     * @param roll account roll.
     **/
    void addRoll ( std::strin roll ) {
        m_userroles.push_back ( roll );
    };
    
    /**
     * Add a list of rolls.
     * @param roll list of account rolls.
     **/
    void addRoll ( std::list<std::string> rolls ) {
//         m_userroles.push_back ( roll );
    }:
    
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
    

    
private:
    std::vector < std::string > m_userroles;
    
};


#endif 