/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or later
* version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
        DEBUG std::endl;
        return this->m_userID;
    } else {
        DEBUG std::endl;
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
    this->m_userID = "";
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
