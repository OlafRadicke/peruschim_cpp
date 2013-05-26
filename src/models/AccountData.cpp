
#include "AccountData.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


// D --------------------------------------------------------------------------

void AccountData::deleteAllData() {

    DEBUG "saveUpdate" << std::endl;
    DEBUG "m_account_disable: " << m_account_disable << std::endl;
    std::string sqlcommand = "";
    Config config;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect( conn_para );
    tntdb::Transaction trans(conn);

    conn.prepare( "DELETE FROM  account_acl_roll \n\
        WHERE account_id= :v1 ;").set( "v1",  m_id ).execute();

    conn.prepare( "DELETE FROM  edition \n\
        WHERE owner_id= :v1 ;").set( "v1",  m_id ).execute();

    conn.prepare( "DELETE FROM  quote_keyword \n\
        WHERE quote_id IN ( SELECT id FROM quote WHERE owner_id= :v1 );")
    .set( "v1",  m_id ).execute();

    conn.prepare( "DELETE FROM  quote \n\
        WHERE owner_id= :v1 ;").set( "v1",  m_id ).execute();

    conn.prepare( "DELETE FROM  account \n\
        WHERE id= :v1 ;").set( "v1",  m_id ).execute();

    trans.commit();
}

// G --------------------------------------------------------------------------

string AccountData::genRandomSalt ( const int len) {
    /* initialize random seed: */
    srand (time(NULL));
    string randomString = "";
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < len; ++i) {
        int randNo = rand() % (sizeof(alphanum) - 1) ;
        DEBUG "randNo: " << randNo << endl;
        randomString.push_back ( alphanum[randNo] );
    }
    return randomString;
}

// S --------------------------------------------------------------------------

void AccountData::saveUpdate(){

    DEBUG "saveUpdate" << std::endl;
    DEBUG "m_account_disable: " << m_account_disable << std::endl;
    std::string sqlcommand = "";
    Config config;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect( conn_para );
    tntdb::Statement st = conn.prepare( "UPDATE account SET \n\
        login_name=:v1 ,  \n\
        real_name=:v2,  \n\
        email=:v3,  \n\
        account_disable=:v4 \n\
        WHERE id= :v5 ;");

    st.set( "v1", m_login_name )
    .set( "v2", m_real_name )
    .set( "v3", m_email )
    .set( "v4", m_account_disable )
    .set( "v5", m_id ).execute();

}


void AccountData::setNewPassword ( std::string newpassword ) {

    DEBUG "setNewPassword" << std::endl;
    std::string sqlcommand = "";
    std::string password_salt;
    std::string password_hash;
    Config config;
    vector<string>   list_1d;
    std:: string isPrivateData = "false";

    password_salt = AccountData::genRandomSalt ( 16 );
    password_hash = cxxtools::md5 ( newpassword + password_salt );

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect( conn_para );
    DEBUG std::endl;
    tntdb::Statement st = conn.prepare( "UPDATE account SET \n\
        password_hash=:v1,  \n\
        password_salt=:v2  \n\
        WHERE id= :v3 ;");

    st.set( "v1", password_hash )
        .set( "v2", password_salt )
        .set( "v3", this->m_id )
        .execute();

}

