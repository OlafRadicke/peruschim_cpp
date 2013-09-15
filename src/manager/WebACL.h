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

#include <models/AccountData.h>


class WebACL {

public:

    /**
     * verifies the authenticity.
     * @para user_name name of user.
     * @para password password of user.
     * @return "true" if okay, else "false".
     **/
    static bool authUser ( const std::string& user_name, const std::string& password );

    /**
     * Create new account.
     * @para user_name name of user account.
     * @para password password of user.
     **/
    static void createAccount (
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
    static void createAccount (
            std::string user_name,
            std::string new_password,
            std::string real_name = "",
            std::string email = "",
            std::string roll = ""
    );

    /**
     * Generated a random string for password salt.
     * @para len length of sting.
     * @return a random string
     */
    std::string static genRandomSalt ( const int len ) ;

    /**
     * Get a account data with a specific id.
     * @arg id id from a account.
     * @return account data.
     **/
    static AccountData getAccountsWithID ( unsigned long id );

    /**
     * Get back all account data.
     * @return list of all account datas.
     **/
    static std::vector<AccountData> getAllAccounts ( );


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
    static std::vector<std::string> getRoll( const std::string& user_name );

    /**
     * Get back search result as account datas.
     * @para serach_string a serach string.
     * @return list of all account datas.
     **/
    static std::vector<AccountData> getSearchAccounts( const std::string& serach_string );

    /**
     * Get back all account data where in trust of a specific user.
     * @arg guarantor_id id from a guarantor account/user.
     * @return list of account datas.
     **/
    static std::vector<AccountData> getTrustAccounts( unsigned long guarantor_id );

    /**
     * Check is this account trusted..
     * @para acount_id name of the user/account.
     * @return true = trusted, false = no trusted.
     **/
    static bool isTrustedAccount( unsigned long acount_id );

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
     * Remove a trusted link between tow user.
     * This delete recursive the complied trusted link tree from untrusted
     * account. Has a user no more guarantors, he can't publish his comments.
     * @para trusted_account_id id of a trust user.
     * @para guarantor_id id of his guarantor.
     **/
    void static setRevokeTrustAccounts(
        const unsigned long trusted_account_id,
        const unsigned long guarantor_id
    );


    /**
     * Reset user rolls. So it's delete all rolls of a user and than reset
     * with the given grup list.
     * @para user_id id of the user.
     * @para user_rolls list of rolls.
     */
    void static reSetUserRolls(
        const unsigned long user_id,
        const std::vector<std::string> user_rolls
    );

    /**
     * Set a trusted link between tow user.
     * Has a user a guarantor with trust, he can publish his comments.
     * But guarantor must be a trusted by other user!
     * @para trusted_account_id id of a trust user.
     * @para guarantor_id id of his guarantor.
     **/
    void static setTrustAccounts(
        const unsigned long trusted_account_id,
        const unsigned long guarantor_id
    );


};

#endif

