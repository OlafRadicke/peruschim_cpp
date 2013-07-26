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


#include "AccountData.h"
#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <stdlib.h>
#include <cxxtools/md5.h>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


// D --------------------------------------------------------------------------

void AccountData::deleteAllData() {

    DEBUG "saveUpdate" << std::endl;
    DEBUG "m_account_disable: " << m_account_disable << std::endl;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Transaction trans(conn);

    conn.prepare(
           "DELETE FROM account_acl_roll \
             WHERE account_id= :v1")
        .set( "v1",  m_id )
        .execute();

    conn.prepare(
           "DELETE FROM  edition \
             WHERE owner_id= :v1")
        .set( "v1",  m_id )
        .execute();

    conn.prepare(
           "DELETE FROM  quote_keyword \
             WHERE quote_id IN ( SELECT id \
                                   FROM quote \
                                  WHERE owner_id= :v1 )")
        .set( "v1", m_id )
        .execute();

    conn.prepare(
           "DELETE FROM quote \
             WHERE owner_id= :v1")
        .set( "v1", m_id )
        .execute();

    conn.prepare(
           "DELETE FROM  account \
             WHERE id= :v1")
        .set( "v1", m_id )
        .execute();

    trans.commit();
}

// G --------------------------------------------------------------------------

std::string AccountData::genRandomSalt ( int len) {

    /* initialize random seed: */
    srand (time(NULL));
    std::string randomString;

    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len; ++i) {
        int randNo = rand() % (sizeof(alphanum) - 1) ;
        DEBUG "randNo: " << randNo << std::endl;
        randomString.push_back ( alphanum[randNo] );
    }

    return randomString;
}

// S --------------------------------------------------------------------------

void AccountData::saveUpdate() {

    DEBUG "saveUpdate" << std::endl;
    DEBUG "m_account_disable: " << m_account_disable << std::endl;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Statement st = conn.prepare(
        "UPDATE account \
            SET login_name      = :v1, \
                real_name       = :v2, \
                email           = :v3, \
                account_disable = :v4  \
          WHERE id= :v5");

    st.set( "v1", m_login_name )
      .set( "v2", m_real_name )
      .set( "v3", m_email )
      .set( "v4", m_account_disable )
      .set( "v5", m_id )
      .execute();

}


void AccountData::setNewPassword ( std::string newpassword ) {

    DEBUG "setNewPassword" << std::endl;
    std::string password_salt;
    std::string password_hash;

    password_salt = AccountData::genRandomSalt ( 16 );
    password_hash = cxxtools::md5 ( newpassword + password_salt );

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    DEBUG std::endl;
    tntdb::Statement st = conn.prepare(
        "UPDATE account \
            SET password_hash=:v1, \
                password_salt=:v2  \
          WHERE id= :v3");

    st.set( "v1", password_hash )
      .set( "v2", password_salt )
      .set( "v3", this->m_id )
      .execute();

}

