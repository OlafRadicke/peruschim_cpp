
#include "DatabaseProxy.h"
#include "TeamDataBase.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<



void TeamDataBase::deleteConnection ( void ) {

    DEBUG "start..." << std::endl;
    DatabaseProxy database_proxy;
    
    DEBUG std::endl;
    
    database_proxy.sqlSet( \
        "DELETE FROM  db_account \
        WHERE account_id=" + m_account_id + ";"
    );  
}

void TeamDataBase::saveConnection ( void ) {
    DEBUG "start..." << std::endl;
    DatabaseProxy database_proxy;
    
    DEBUG std::endl;
    
    database_proxy.sqlSet( \
        "INSERT INTO db_account \
        ( \
            account_name    , \
            server_name     , \
            database_name   , \
            port_no         , \
            db_encoding     , \
            db_user         , \
            db_password     , \
            db_sslmode      , \
            owner_id         \
        )\
        VALUES \
        ( \
            '" + DatabaseProxy::replace( m_account_name ) + "',  \
            '" + DatabaseProxy::replace( m_server_name ) + "',  \
            '" + DatabaseProxy::replace( m_database_name ) + "',  \
            " + m_port_no + ",  \
            '" + DatabaseProxy::replace( m_db_encoding ) + "',  \
            '" + DatabaseProxy::replace( m_db_user ) + "',  \
            '" + DatabaseProxy::replace( m_db_password ) + "',  \
            '" + DatabaseProxy::replace( m_db_sslmode ) + "',  \
            " + m_owner_id + "  \
        );"
    );    
    
}

void TeamDataBase::saveChanges ( void ) {
    DEBUG "start..." << std::endl;
    DatabaseProxy database_proxy;
    
    DEBUG std::endl;
    
    database_proxy.sqlSet( \
        "UPDATE db_account SET \
            account_name='" + DatabaseProxy::replace( m_account_name ) + "', \
            server_name='" + DatabaseProxy::replace( m_server_name ) + "', \
            database_name='" + DatabaseProxy::replace( m_database_name ) + "', \
            port_no=" + m_port_no + ", \
            db_encoding='" + DatabaseProxy::replace( m_db_encoding ) + "', \
            db_user='" + DatabaseProxy::replace( m_db_user ) + "', \
            db_password='" + DatabaseProxy::replace( m_db_password ) + "', \
            db_sslmode='" + DatabaseProxy::replace( m_db_sslmode ) + "', \
            owner_id=" + m_owner_id + "  \
        WHERE account_id=" + m_account_id + ";"
    );    
    
}