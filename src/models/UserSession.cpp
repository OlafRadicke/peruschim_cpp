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
#include <tntdb/statement.h>
#include <tntdb/connection.h>
#include <tntdb/connect.h>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


void UserSession::addRoll ( std::vector<std::string> rolls ) {
    DEBUG "addRoll" << std::endl;
    for ( unsigned int i=0; i<rolls.size(); i++) {
        DEBUG "Add roll: " << rolls[i] << std::endl;
        m_userroles.push_back ( rolls[i] );
    }
}

unsigned long UserSession::getUserID ( ) {
    DEBUG std::endl;
    Config config;
    if ( this->m_userID > 0 ) {
        DEBUG std::endl;
        return this->m_userID;
    } else {

        tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );
        tntdb::Statement st = conn.prepare( 
            "SELECT \
                id \
            FROM account \
            WHERE login_name = :username" 
        );
        st.set("username", this->m_username ).execute(); 
        
        for (tntdb::Statement::const_iterator it = st.begin();
            it != st.end(); ++it
        ) {
            tntdb::Row row = *it;
            this->m_userID = row[0].getInt();
        }
    }
    return this->m_userID;
}

void UserSession::logout( ) {
    DEBUG "logout..." << std::endl;
    this->m_userroles.clear();
    this->m_username = "";
    this->m_userID = 0;
}

bool UserSession::isInRole ( std::string siteroll ) {
    for ( unsigned int i=0; i<m_userroles.size(); i++) {
        if ( m_userroles[i] == siteroll ) {
            return true;
        }
    }
    return false;
}

bool UserSession::isInRole ( std::vector<std::string> siterolls ) {
    DEBUG "m_userroles.size(): " << m_userroles.size() << std::endl;

    for ( unsigned int i=0; i<m_userroles.size(); i++) {
        for ( unsigned int i2=0; i2<siterolls.size(); i2++) {
            if ( m_userroles[i] == siterolls[i2] ) {
                DEBUG "true" << std::endl;
                return true;
            }
        }
    }
    DEBUG "false" << std::endl;
    return false;
}
