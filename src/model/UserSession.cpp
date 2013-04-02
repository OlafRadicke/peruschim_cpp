#include "UserSession.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


void UserSession::addRoll ( std::vector<std::string> rolls ) {
    DEBUG "addRoll" << std::endl;
    for ( unsigned int i=0; i<rolls.size(); i++) {
        DEBUG "Add roll: " << rolls[i] << std::endl;
        m_userrolls.push_back ( rolls[i] );
    }
}

std::string UserSession::getUserID ( void ) { 
    DEBUG std::endl;
    std::string user_id = "";
    
    Config config; 
    string conn_para = "password=" + config.get( "DB-PASSWD" );
    conn_para += " dbname=" + config.get( "DB-NAME" ) ;
    conn_para += " host=" + config.get( "DB-HOST" ) ;
    conn_para += " port=" + config.get( "DB-PORT" ) ;
    conn_para += " user=" + config.get( "DB-USER" ) ;
        
    std::string sqlcommand =    "SELECT \n\
                        id \n\
                    FROM account \n\
                    WHERE login_name='" + this->m_username + "';";
    DEBUG "sql-code: " << sqlcommand << std::endl;
    pqxx::connection pg_conn( conn_para );
    pqxx::work  pg_worker( pg_conn );
    pqxx::result res;
    unsigned int row_count;
    vector<string>   list_1d;
    vector< vector<string> >  list_2d;
    res = pg_worker.exec( sqlcommand );         
    pg_worker.commit();
//     DEBUG " found: " << res.size() << endl;
    for (row_count=0; row_count < res.size(); row_count++) {
        user_id = res[row_count][0].as<string>();
    }    
    pg_conn.disconnect();
    return user_id;
}

void UserSession::lockout( ) { 
    DEBUG "logout..." << endl;
    this->m_userrolls.clear(); 
    this->m_username = "";
}  

bool UserSession::isInRole ( std::string siteroll ) {
    DEBUG "siteroll: " << siteroll << std::endl;
    
    for ( unsigned int i=0; i<m_userrolls.size(); i++) {
        if ( m_userrolls[i] == siteroll ) {
            DEBUG "true" << std::endl;
            return true;
        }
    }
    DEBUG "false" << std::endl;
    return false;
}

bool UserSession::isInRole ( std::vector<std::string> siterolls ) {
    DEBUG "m_userrolls.size(): " << m_userrolls.size() << std::endl;
    
    for ( unsigned int i=0; i<m_userrolls.size(); i++) {
        for ( unsigned int i2=0; i2<siterolls.size(); i2++) {
            if ( m_userrolls[i] == siterolls[i2] ) {
                DEBUG "true" << std::endl;
                return true;
            }
        }
    }
    DEBUG "false" << std::endl;
    return false;
}