#include "DatabaseProxy.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


using namespace std;

DatabaseProxy::DatabaseProxy( ) : 
    m_pg_db_name (""), 
    m_pg_db_host (""), 
    m_pg_db_user (""),
    m_pg_db_passwd (""),
    m_pg_db_port (""),
    m_sqlQuotas ("'") 
{      
    DEBUG "========== init begin ========== \n" ;
//     Config config;
    m_config = new Config();
    m_pg_db_name = m_config->get( "DB-NAME" );
    DEBUG "m_pg_db_name: " << m_pg_db_name << endl ;
    m_pg_db_host = m_config->get( "DB-HOST" ); 
    DEBUG "m_pg_db_host: " << m_pg_db_host << endl;
    m_pg_db_user = m_config->get( "DB-USER" ); 
    DEBUG "m_pg_db_user: " << m_pg_db_user << endl;
    m_pg_db_passwd = m_config->get( "DB-PASSWD" ); 
    DEBUG "m_pg_db_passwd: " << m_pg_db_passwd << endl;
    m_pg_db_port = m_config->get( "DB-PORT" ); 
    DEBUG "m_pg_db_passwd: " << m_pg_db_port << endl;
    
    DEBUG  endl;
    
    DEBUG  endl;
    
    string conn_para = "password=" + m_pg_db_passwd +\
        " dbname=" + m_pg_db_name + \
        " host=" + m_pg_db_host + \
        " port=" + m_pg_db_port + \
        " user=" + m_pg_db_user ;
        
    DEBUG "conn_para:  " << conn_para << endl;
    
    m_pg_conn = new pqxx::connection( conn_para );
    
    DEBUG endl ;
    
    m_pg_work = new pqxx::work( *(m_pg_conn) );
    DEBUG "========== init end ==========" << endl;

}

DatabaseProxy::~DatabaseProxy() {
    DEBUG "========== destructor begin =========="  << endl;
    delete m_config;
    DEBUG  endl;
    delete m_pg_work;  
    DEBUG  endl;
    m_pg_conn->disconnect();
    DEBUG endl;
    delete m_pg_conn;  
    DEBUG "========== destructor end =========="  << endl;
    
}

vector< vector<string> > DatabaseProxy::sqlGet ( string sqlcommand )
{
    DEBUG  endl;
    unsigned int     row;
    unsigned int     col;
    vector< vector<string> >  list_2d;

    DEBUG  endl;
/*    
    m_pg_work->exec(
         "INSERT INTO category (title, subtitle) \
         VALUES ( 'Tier', 'Hund');" );
    DEBUG  endl;
    */

//    m_pg_work.commit();
    
    pqxx::result res = m_pg_work->exec( sqlcommand );  
    DEBUG  endl;
    m_pg_work->commit();
    DEBUG " found: " << res.size() << endl;
    DEBUG  endl;
    
    for (row=0; row < res.size(); row++) {
        DEBUG "row nr.:" << row  << endl;
        for (col=0; col < res[row].size(); col++) {
            DEBUG "col nr.:" << col  << endl;
            DEBUG "value:" << res[row][col].as<string>() << "\t"  << endl;
        }
        DEBUG "end of loop" << endl;
    }    
    DEBUG  endl;
    return list_2d;
 
    
    
}



void DatabaseProxy::sqlSet ( string sqlcommand )
{
/*    
    DEBUG "SQL-CODE: \n <begin>" << sqlcommand  << "<end>";
    DEBUG "[OR1336745746] sqlSet ( string sqlcommand )" ;
        
    DEBUG "========== pgTest - begin ==========" ;

    DEBUG "========== pgTest - 1 ==========" ;
    m_pg_work->exec(
        "INSERT INTO category (title, subtitle) \
        VALUES ( 'Tier', 'Hund');" );

    DEBUG "========== pgTest - end ==========" ;
    */
}

std::string DatabaseProxy::replace (  std::string s ){
    if ( s == "" ) {
        return "";
    }
    return DatabaseProxy::replace ( s, "'", "\\'" );
}
    
std::string DatabaseProxy::replace ( 
    std::string s, 
    const std::string& k, 
    const std::string& r
){
    DEBUG "[OR1345988343] replace";
    DEBUG "s" << s;
    DEBUG "k" << k;
    DEBUG "r" << r;
    if ( s.length() == 0 ) {
        return s;
    }
    std::string::size_type p = 0;
    DEBUG endl;
    p = s.find(k, p);
    while ( p != std::string::npos) {
        DEBUG endl;
        s.replace(p, k.length(), r);
        DEBUG endl;
        p += r.length();
        DEBUG " p " << p << endl;
        p = s.find(k, p);
    }

    DEBUG "return s" << s << endl;
    return s;
}

void DatabaseProxy::setQuotaType ( string quotaTyp ){
    m_sqlQuotas = quotaTyp;
}
