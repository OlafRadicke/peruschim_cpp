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

#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H

#include <string>
#include "Config.h"


/**
* This class represent a data set of the tabe a23t_account (system data base).
**/
class AccountData {

public:

    /**
     * Constructor init strings.
     **/
    AccountData () :
        m_id ( 0 ),
        m_login_name ( "" ),
        m_real_name ( "" ),
        m_password_hash ( "" ),
        m_password_salt ( "" ),
        m_email ( "" ),
        m_account_disable ( false )
    {};


    /**
     * Delet all data of this account
     */
    void deleteAllData();

    void setID( unsigned long id ) { m_id = id; };
    unsigned long getID ( void ) { return m_id; };

    void setLogin_name( std::string login_name ) { m_login_name = login_name; };
    std::string getLogin_name( void ) { return m_login_name; };

    void setReal_name( std::string real_name ) { m_real_name = real_name; };
    std::string getReal_name( void ) { return m_real_name; };

    void setPassword_hash( std::string password_hash ) { m_password_hash = password_hash; };
    std::string getPassword_hash( void ) { return m_password_hash; };

    /**
     * Set a new passwort.
     * @arg newpassword the new password.
     */
    void setNewPassword( std::string newpassword );

    void setPassword_salt( std::string password_salt ) { m_password_salt = password_salt; };
    std::string getPassword_salt( void ) { return m_password_salt; };

    void setEmail( std::string email ) { m_email = email; };
    std::string getEmail( void ) { return m_email; };

    void setAccount_disable( bool account_disable ) { m_account_disable = account_disable; };
    bool getAccount_disable( void ) { return m_account_disable; };


    /**
     * Save date update in in database..
     **/
    void saveUpdate();

private:

    unsigned long m_id;
    std::string m_login_name;
    std::string m_real_name;
    std::string m_password_hash;
    std::string m_password_salt;
    std::string m_email;
    bool        m_account_disable;

    /**
     * Generated a random string for password salt.
     * @para len length of sting.
     * @return a random string
     */
    std::string static genRandomSalt( int len ) ;

};


#endif
