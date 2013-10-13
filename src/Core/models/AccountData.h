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
#include <Core/models/Config.h>


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
     * Constructor init strings.
     * @arg account_id id of account.
     **/
    AccountData ( unsigned long account_id ) :
        m_id ( account_id ),
        m_login_name ( "" ),
        m_real_name ( "" ),
        m_password_hash ( "" ),
        m_password_salt ( "" ),
        m_email ( "" ),
        m_account_disable ( false )
    {};

// D --------------------------------------------------------------------------

    /**
     * Delete all data of this account
     * @arg liqudator_id how is the liqudator, the user that this account delete.
     */
    void deleteAllData( unsigned long liqudator_id );

// G --------------------------------------------------------------------------

    /**
     * Get count of guarantor from a user.
     * @return count of guarantor.
     **/
    int getGuarantorCount( );

    /**
     * Get back all guarantors of this accont/user.
     * @return list of account datas.
     **/
    std::vector<AccountData> getGuarantors();

    /** Get back account id. */
    unsigned long getID ( void ) { return m_id; };

    /** Get back login name. */
    std::string getLogin_name( void ) { return m_login_name; };

    /** Get back real name. */
    std::string getReal_name( void ) { return m_real_name; };

    /** Get back password hash. */
    std::string getPassword_hash( void ) { return m_password_hash; };

    /** Get back password salt. */
    std::string getPassword_salt( void ) { return m_password_salt; };

    /** Get back emil address. */
    std::string getEmail( void ) { return m_email; };

    /** Get back true when the account is disabled. */
    bool getAccount_disable( void ) { return m_account_disable; };

    /**
     * Get back all account data where in trust of this user.
     * @return list of account datas.
     **/
    std::vector<AccountData> getTrustAccounts();

// I --------------------------------------------------------------------------

    /**
     * Check is more than one user this account trusted.
     * @return true = trusted, false = no trusted.
     **/
    bool isTrustedAccount();

// R --------------------------------------------------------------------------

    /**
     * Remove all trusted link between tow a user.
     * This delete recursive the complied trusted link tree.
     * Has a user no more guarantors, he can't publish his comments.
     * @return A list of account ids, where has been revoked the trust.
     **/
    std::vector<unsigned long> revokeTrust();

    /**
     * Remove a trusted link between tow user.
     * This delete recursive the complied trusted link tree from untrusted
     * account. Has a user no more guarantors, he can't publish his comments.
     * @para guarantor_id id of revoked guarantor.
     * @return A list of account ids, where has been revoked the trust.
     **/
    std::vector<unsigned long> revokeTrust( const unsigned long guarantor_id );

// S --------------------------------------------------------------------------

    /**
     * Save date update in in database..
     **/
    void saveUpdate();

    void setID( unsigned long id ) { m_id = id; };

    void setLogin_name( std::string login_name ) { m_login_name = login_name; };

    void setReal_name( std::string real_name ) { m_real_name = real_name; };

    void setPassword_hash( std::string password_hash ) { m_password_hash = password_hash; };

    /**
     * Set a new passwort.
     * @arg newpassword the new password.
     */
    void setNewPassword( std::string newpassword );

    void setPassword_salt( std::string password_salt ) { m_password_salt = password_salt; };

    void setEmail( std::string email ) { m_email = email; };

    void setAccount_disable( bool account_disable ) { m_account_disable = account_disable; };


// T --------------------------------------------------------------------------

    /**
     * Set a trusted link between tow user.
     * Has a user a guarantor with trust, he can publish his comments.
     * But guarantor must be a trusted by other user!
     * @para guarantor_id id of his guarantor.
     **/
    void trustedByGuarantor(
        const unsigned long guarantor_id
    );


private:

    unsigned long m_id;
    std::string m_login_name;
    std::string m_real_name;
    std::string m_password_hash;
    std::string m_password_salt;
    std::string m_email;

    /** Value is true when the account is disabled. */
    bool        m_account_disable;

// G --------------------------------------------------------------------------
    /**
     * Generated a random string for password salt.
     * @para len length of sting.
     * @return a random string
     */
    std::string static genRandomSalt( unsigned int len ) ;

// R --------------------------------------------------------------------------
    /**
     * Remove a trusted link between tow user.
     * This delete recursive the complied trusted link tree from untrusted
     * account. Has a user no more guarantors, he can't publish his comments.
     * @para trusted_account_id id of a trust user.
     * @para guarantor_id id of his guarantor.
     * @return A list of account ids, where has been revoked the trust.
     **/
    static std::vector<unsigned long> revokeTrust(
        const unsigned long trusted_account_id,
        const unsigned long guarantor_id
    );

    /**
     * This function search user where don't have any guarantors and remove
     * the trust link to other user their are truster. Because only trusted
     * user can trusted other user.
     * @return A list of account ids, where has been revoked the trust.
     **/
    static std::vector<unsigned long> cleanUpTrust();

    /**
     * This function search user where don't have any guarantors and remove
     * the trust link to other user their are truster. Because only trusted
     * user can trusted other user.
     * This delete recursive the complied trusted link tree from untrusted
     * account. Has a user no more guarantors, he can't publish his comments.
     * @return A list of account ids, where has been revoked the trust.
     **/
    static std::vector<unsigned long> cleanUpTrustRecursively();

};


#endif
