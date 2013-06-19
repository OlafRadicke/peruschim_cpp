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

enum ItemView { ALLITEMS, PRIVATEITEMS };

/**
* This class represent a data set of a session.
**/
class UserSession {

public:


    UserSession () : m_username( "" ), m_userID( "" ) {};

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
     * Get back the mode of item view.
     */
    ItemView getItemViewMode() {
        return this->m_item_view;
    }

    /**
     * Get back the user login name.
     * @return login name.
     **/
    std::string getUserName() { return m_username; };


    /**
     * Get back the user ID.
     * @return ID of user.
     **/
    std::string getUserID();

    /**
     * Set the mode of item view.
     */
    void setItemViewMode ( ItemView mode) {
        this->m_item_view = mode;
    }

private:

    /**
     * Rolls of user.
     **/
    std::vector < std::string > m_userrolls;


    /**
     * Login name
     **/
    std::string m_username;

    /**
     * User ID
     **/
    std::string m_userID;

    /**
     * the mode of item view.
     * Options: "all","public"
     */
    ItemView m_item_view;

};


#endif
