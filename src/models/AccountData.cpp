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


#include <models/AccountData.h>
#include <manager/RSSfeedManager.h>
#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <stdlib.h>
#include <cxxtools/md5.h>
#include <cxxtools/log.h>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

log_define("models.AccountData")

// D --------------------------------------------------------------------------

void AccountData::deleteAllData( unsigned long liqudator_id ) {

    DEBUG "saveUpdate" << std::endl;
    DEBUG "m_account_disable: " << m_account_disable << std::endl;

    // Revoke trust links.
    revokeTrust( );

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

    // create a event feed.
    RSSfeed newFeed;
    newFeed.setTitle( "Account gelöscht" );
    std::string description = "Der Account mit der ID "
        + cxxtools::convert<std::string>( m_id ) \
        + " wurde gelöscht. Der Login-Name war: \"" + m_login_name
        + "\", und der reale name: \"" + m_real_name + "\".";
    newFeed.setDescription( description );
    newFeed.channels.push_back("account");
    RSSfeedManager feedManager;
    feedManager.addNewFeed( newFeed );
}

// G --------------------------------------------------------------------------


int AccountData::getGuarantorCount( ){
    int guarantorCount = 0;
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );

    tntdb::Statement st = conn.prepare( "SELECT \
                        count( guarantor_id )  \
                    FROM account_trust \
                    WHERE trusted_account_id = :m_id");

    st.set( "m_id", m_id ).execute();

    tntdb::Value value = st.selectValue( );
    value.get(guarantorCount);

    log_debug("guarantorCount: " <<  guarantorCount );
    return guarantorCount;
}

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

void AccountData::revokeTrust( ){
    log_debug( __LINE__ + "start...");
    tntdb::Statement st;
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );

    st = conn.prepare(
            "SELECT trusted_account_id  \
            FROM account_trust \
            WHERE guarantor_id = :m_id "
    );
    st.set( "m_id", m_id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        // Yes, this delete recursive the completed trusted link tree of this
        // user.
        AccountData::revokeTrust(
            row[0].getInt(),
            m_id
        );
    }

    st = conn.prepare(
        "DELETE FROM account_trust \
        WHERE trusted_account_id = :m_id ;"
    );
    st.set("m_id", m_id ).execute();

}

void AccountData::revokeTrust(
    const unsigned long guarantor_id
){
    AccountData::revokeTrust(
        m_id,
        m_id
    );
}

void AccountData::revokeTrust(
    const unsigned long trusted_account_id,
    const unsigned long guarantor_id
){
    log_debug( __LINE__ + "start...");
    tntdb::Statement st;
    AccountData accountData;
    accountData.setID( trusted_account_id );
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );


    if ( accountData.getGuarantorCount() <= 0 ) {
        st = conn.prepare(
                "SELECT trusted_account_id  \
                FROM account_trust \
                WHERE guarantor_id = :trusted_account_id "
        );
        st.set( "trusted_account_id", trusted_account_id ).execute();


        for (tntdb::Statement::const_iterator it = st.begin();
            it != st.end(); ++it
        ) {
            tntdb::Row row = *it;
            // Yes, this delete recursive the completed trusted link tree of this
            // user.
            revokeTrust(
                row[0].getInt(),
                trusted_account_id
            );
        }
    }

    st = conn.prepare(
        "DELETE FROM account_trust \
        WHERE trusted_account_id = :trusted_account_id \
        AND guarantor_id = :guarantor_id;"
    );
    st.set("trusted_account_id", trusted_account_id )
    .set("guarantor_id", guarantor_id ).execute();

}

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

