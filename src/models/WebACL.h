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

#ifndef WEBACL_H
#define WEBACL_H

#include <vector>
#include <string>
#include <iostream>

#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>

#include "AccountData.h"


class WebACL {

public:

    /**
     * verifies the authenticity.
     * @para user_name name of user.
     * @para password password of user.
     * @return "true" if okay, else "false".
     **/
    bool static authUser ( std::string user_name, std::string password );

    /**
     * Open connatct with database.
     * */
    void connectDataBase ();

    /**
     * Create new account.
     * @para user_name name of user account.
     * @para password password of user.
     **/
    void static createAccount (
            std::string user_name,
            std::string new_password
    );

    /**
     * Create new account.
     * @para user_name name of user account.
     * @para password password of user.
     * @para real_name real name of user.
     * @para email email of user.
     * @para roll roll of user.
     **/
    void static createAccount (
            std::string user_name,
            std::string new_password,
            std::string real_name = "",
            std::string email = "",
            std::string roll = ""
    );

    /**
     * Get a account data with a specific id.
     * @arg id id from a account.
     * @return account data.
     **/
    static AccountData getAccountsWithID ( const std::string id );

    /**
     * Get back all account data.
     * @return list of all account datas.
     **/
    static std::vector<AccountData> getAllAccounts ( void );

    /**
     * Get back all exist roles.
     * @return list of user roles
     **/
    static std::vector<std::string> getAllRolls();

    /**
     * Get back the roles from a user.
     * @para user_name name of the user.
     * @return list of user roles
     **/
    static std::vector<std::string> getRoll( std::string user_name );

    /**
     * Check is user in database exist.
     * @para user_name name of the user.
     * @return true = exist, false = no exist.
     **/
    static bool isUserExist( std::string user_name );

    /**
     * Check is user in a roll.
     * @para user_name name of the user.
     * @para roll roll.
     * @return true = has roll, false = has no this roll.
     **/
    static bool isUserInRole(
        const std::string user_name,
        const std::string roll
    );

    /**
     * Set a new password from a user.
     * @para user_name name of the user.
     * @para new_password new password phrase.
     **/
    void setPassword(
        std::string user_namelogin_name,
        std::string new_password
    );

    /**
     * Generated a random string for password salt.
     * @para len length of sting.
     * @return a random string
     */
    std::string static genRandomSalt ( const int len ) ;

    /**
     * Reset user rolls. So it's delete all rolls of a user and than reset
     * with the given grup list.
     * @para user_id id of the user.
     * @para user_rolls list of rolls.
     */
    void static reSetUserRolls(
        const std::string user_id,
        const std::vector<std::string> user_rolls
    );

private:

};

#endif

