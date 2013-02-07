#include "UserSession.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

bool UserSession::isInRole ( std::string siteroll ) {
    
    for ( unsigned int i=0; i<m_userroles.size(); i++) {
        if ( m_userroles[i] == siteroll ) {
            return true;
        }
    }
    return false;
}

bool UserSession::isInRole ( std::vector<std::string> siterolls ) {
    
    for ( unsigned int i=0; i<m_userroles.size(); i++) {
        for ( unsigned int i2=0; i2<siterolls.size(); i2++) {
            if ( m_userroles[i] == siterolls[i2] ) {
                return true;
            }
        }
    }
    return false;
}