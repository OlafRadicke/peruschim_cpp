#include "UserSession.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


void UserSession::addRoll ( std::vector<std::string> rolls ) {
    DEBUG "addRoll" << std::endl;
    for ( unsigned int i=0; i<rolls.size(); i++) {
        DEBUG "Add roll: " << rolls[i] << std::endl;
        m_userrolls.push_back ( rolls[i] );
    }
}


bool UserSession::isInRole ( std::string siteroll ) {
    DEBUG "siteroll: " << siteroll << std::endl;
    
    for ( unsigned int i=0; i<m_userrolls.size(); i++) {
        if ( m_userrolls[i] == siteroll ) {
            DEBUG "true" << std::endl;
            return true;
        }
    }
    DEBUG "false" << std::endl;
    return false;
}

bool UserSession::isInRole ( std::vector<std::string> siterolls ) {
    DEBUG "m_userrolls.size(): " << m_userrolls.size() << std::endl;
    
    for ( unsigned int i=0; i<m_userrolls.size(); i++) {
        for ( unsigned int i2=0; i2<siterolls.size(); i2++) {
            if ( m_userrolls[i] == siterolls[i2] ) {
                DEBUG "true" << std::endl;
                return true;
            }
        }
    }
    DEBUG "false" << std::endl;
    return false;
}