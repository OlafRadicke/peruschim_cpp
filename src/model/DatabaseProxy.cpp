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
    Config config;
//     m_config = new Config();
    m_pg_db_name = config.get( "DB-NAME" );
    m_pg_db_host = config.get( "DB-HOST" ); 
    m_pg_db_user = config.get( "DB-USER" ); 
    m_pg_db_passwd = config.get( "DB-PASSWD" ); 
    m_pg_db_port = config.get( "DB-PORT" ); 
    DEBUG "m_pg_db_name: " << m_pg_db_name << endl ;
    DEBUG "m_pg_db_host: " << m_pg_db_host << endl;
    DEBUG "m_pg_db_user: " << m_pg_db_user << endl;
    DEBUG "m_pg_db_passwd: " << m_pg_db_passwd << endl;
    DEBUG "m_pg_db_port: " << m_pg_db_port << endl;
    
    DEBUG "========== init end ==========" << endl;

}


DatabaseProxy::DatabaseProxy( TeamDataBase team_db ){      
    DEBUG "========== init begin ========== \n" ;

    m_pg_db_name = team_db.getDatabase_name ();
    m_pg_db_host = team_db.getServer_name (); 
    m_pg_db_user = team_db.getDB_user (); 
    m_pg_db_passwd = team_db.getDB_password (); 
    m_pg_db_port =  team_db.getPort_no (); 
    
    DEBUG "m_pg_db_name: " << m_pg_db_name << endl ;
    DEBUG "m_pg_db_host: " << m_pg_db_host << endl;
    DEBUG "m_pg_db_user: " << m_pg_db_user << endl;
    DEBUG "m_pg_db_passwd: " << m_pg_db_passwd << endl;
    DEBUG "m_pg_db_passwd: " << m_pg_db_port << endl;
    
    DEBUG "========== init end ==========" << endl;
}

string DatabaseProxy::convertIntToStr( int number )
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

DatabaseProxy::~DatabaseProxy() {
    DEBUG "========== destructor begin =========="  << endl;
//     delete m_config;
    DEBUG "========== destructor end =========="  << endl;
    
}

vector< vector<string> > DatabaseProxy::sqlGet ( string sqlcommand )
{
    DEBUG "sqlGet" <<  endl;
    string conn_para = "password=" + m_pg_db_passwd +\
        " dbname=" + m_pg_db_name + \
        " host=" + m_pg_db_host + \
        " port=" + m_pg_db_port + \
        " user=" + m_pg_db_user ;    
    pqxx::connection pg_conn( conn_para );
    pqxx::work  pg_worker( pg_conn );
    pqxx::result res;
    unsigned int     row_count;
    unsigned int     col_count;
    vector<string>   list_1d;
    vector< vector<string> >  list_2d;
    res = pg_worker.exec( sqlcommand );         
    pg_worker.commit();
//     DEBUG " found: " << res.size() << endl;
    
    for (row_count=0; row_count < res.size(); row_count++) {
//         DEBUG "row nr.:" << row_count  << endl;
        for (col_count=0; col_count < res[row_count].size(); col_count++) {
//             DEBUG "col nr.:" << col_count  << endl;
//             DEBUG "value:" << res[row_count][col_count].as<string>() << "\t"  << endl;
            list_1d.push_back ( res[row_count][col_count].as<string>() );
        }
        list_2d.push_back ( list_1d );
        list_1d.clear();
    }    
    
    pg_conn.disconnect();
    return list_2d;
    
}

string DatabaseProxy::sqlGetSingle ( string sqlcommand )
{
    string conn_para = "password=" + m_pg_db_passwd +\
        " dbname=" + m_pg_db_name + \
        " host=" + m_pg_db_host + \
        " port=" + m_pg_db_port + \
        " user=" + m_pg_db_user ;    

    pqxx::connection pg_conn( conn_para ); 
    pqxx::work  pg_worker( pg_conn );
    pqxx::result res;       
    DEBUG  endl;
    unsigned int     row_count;
    unsigned int     col_count;

    
    DEBUG  endl;
    pg_worker.commit();
    DEBUG " found: " << res.size() << endl;
    DEBUG  endl;
    
    for (row_count=0; row_count < res.size(); row_count++) {
        DEBUG "row nr.:" << row_count  << endl;
        for (col_count=0; col_count < res[row_count].size(); col_count++) {
            DEBUG "col nr.:" << col_count  << endl;
            DEBUG "value:" << res[row_count][col_count].as<string>() << "\t"  << endl;
            return res[row_count][col_count].as<string>() ;
        }
    }    
    DEBUG  endl;
    pg_conn.disconnect();
    return "";
}


void DatabaseProxy::sqlSet ( string sqlcommand )
{
    string conn_para = "password=" + m_pg_db_passwd +\
        " dbname=" + m_pg_db_name + \
        " host=" + m_pg_db_host + \
        " port=" + m_pg_db_port + \
        " user=" + m_pg_db_user ;    

    pqxx::connection pg_conn( conn_para ); 
    pqxx::work  pg_worker( pg_conn );
    pqxx::result res;         
    DEBUG "sqlSet" << endl;
    unsigned int     row;
    unsigned int     col;
    DEBUG "SQL-CODE: \n <code>" << sqlcommand  << "</code>" << endl;
    DEBUG endl ;

    DEBUG endl ;
    res = pg_worker.exec ( sqlcommand );
    DEBUG endl ;
    pg_worker.commit();
    DEBUG endl ;

    
//     catch ( ... ) {
//         ERROR "unknow exception raised!"  << endl;
//         return;
//     }
    DEBUG endl ;
    
    for (row=0; row < res.size(); row++) {
        DEBUG "row nr.:" << row  << endl;
        for (col=0; col < res[row].size(); col++) {
            DEBUG "col nr.:" << col  << endl;
            DEBUG "value:" << res[row][col].as<string>() << "\t"  << endl;
        }
        DEBUG "end of loop" << endl;
    }    
    DEBUG  endl;    
    pg_conn.disconnect();
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
    if ( s.length() == 0 ) {
        return s;
    }
    std::string::size_type p = 0;
    p = s.find(k, p);
    while ( p != std::string::npos) {
        s.replace(p, k.length(), r);
        p += r.length();
        p = s.find(k, p);
    }
    return s;
}

void DatabaseProxy::setQuotaType ( string quotaTyp ){
    m_sqlQuotas = quotaTyp;
}
