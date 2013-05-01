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

std::string UserSession::getUserID ( ) {
    DEBUG std::endl;
    std::string user_id = "";
    if ( this->m_userID != "" ) {
        return this->m_userID;
    } else {
        std::string sqlcommand =    "SELECT \n\
                            id \n\
                        FROM account \n\
                        WHERE login_name='" + this->m_username + "';";
        DatabaseProxy dbProxy;
        user_id = dbProxy.sqlGetSingle ( sqlcommand );
        this->m_userID = user_id;
        return user_id;
    }
}

void UserSession::lockout( ) {
    DEBUG "logout..." << endl;
    this->m_userrolls.clear();
    this->m_username = "";
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
