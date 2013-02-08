#include "UserSession.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


void UserSession::addRoll ( std::vector<std::string> rolls ) {
    for ( unsigned int i=0; i<rolls.size(); i++) {
        m_userrolls.push_back ( rolls[i] );
    }
}


bool UserSession::isInRole ( std::string siteroll ) {
    
    for ( unsigned int i=0; i<m_userrolls.size(); i++) {
        if ( m_userrolls[i] == siteroll ) {
            return true;
        }
    }
    return false;
}

bool UserSession::isInRole ( std::vector<std::string> siterolls ) {
    
    for ( unsigned int i=0; i<m_userrolls.size(); i++) {
        for ( unsigned int i2=0; i2<siterolls.size(); i2++) {
            if ( m_userrolls[i] == siterolls[i2] ) {
                return true;
            }
        }
    }
    return false;
}