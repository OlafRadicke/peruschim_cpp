#include "DatabaseProxy.h"

# define DEBUG cout << "[Config]" <<



using namespace std;

DatabaseProxy::DatabaseProxy( ) : 
    m_pg_db_name (""), 
    m_pg_db_host (""), 
    m_pg_db_user (""),
    m_pg_db_passwd (""),
    m_pg_db_port (""),
    m_sqlQuotas ("'") 
{
        
    DEBUG "========== init begin ==========" ;
    DEBUG "----------init 0.1 " ;
//     Config config;
    m_config = new Config();
    m_pg_db_name = m_config->get( "DB-NAME" );
    DEBUG "----------m_pg_db_name: " << m_pg_db_name ;
    m_pg_db_host = m_config->get( "DB-HOST" ); 
    DEBUG "----------m_pg_db_host: " << m_pg_db_host ;
    m_pg_db_user = m_config->get( "DB-USER" ); 
    DEBUG "----------m_pg_db_user: " << m_pg_db_user ;
    m_pg_db_passwd = m_config->get( "DB-PASSWD" ); 
    DEBUG "----------m_pg_db_passwd: " << m_pg_db_passwd ;
    m_pg_db_port = m_config->get( "DB-PORT" ); 
    DEBUG "----------m_pg_db_passwd: " << m_pg_db_port ;
    
    DEBUG "----------init 1.1 " ;
    
    DEBUG "init 2.1 " ;
    
    string conn_para = "password=" + m_pg_db_passwd +\
        " dbname=" + m_pg_db_name + \
        " host=" + m_pg_db_host + \
        " port=" + m_pg_db_port + \
        " user=" + m_pg_db_user ;
        
    DEBUG "conn_para:  " << conn_para;
    
    m_pg_conn = new pqxx::connection( conn_para );
    
    DEBUG "init 2.2 " ;
    
    m_pg_work = new pqxx::work( *(m_pg_conn) );

    DEBUG "========== init begin ==========" ;

}

DatabaseProxy::~DatabaseProxy() {
    DEBUG "========== destructor begin ==========" ;
    
    DEBUG "========== destructor end ==========" ;
    
}

vector< vector<string> > DatabaseProxy::sqlGet ( string sqlcommand )
{
    DEBUG "sqlGet 1.1 " ;
    unsigned int     row;
    unsigned int     col;
    vector< vector<string> >  list_2d;
    
        
    DEBUG "========== pgTest - begin ==========" ;

    DEBUG "========== pgTest - 1 ==========" ;
    m_pg_work->exec(
        "INSERT INTO category (title, subtitle) \
        VALUES ( 'Tier', 'Hund');" );
    DEBUG "========== pgTest - 2 ==========" ;

//    m_pg_work.commit();
    DEBUG "========== pgTest - 3 ==========" ;
    
    pqxx::result res = m_pg_work->exec(
        "SELECT title, subtitle \
        FROM category ORDER BY title, subtitle;");  
    DEBUG "========== pgTest - 4 ==========" ;
    DEBUG "[pgTest] found: " << res.size() ;
    DEBUG "========== pgTest - 5 ==========" ;
    
    for (row=0; row < res.size(); row++) {
        DEBUG "[pgTest] row nr.:" << row ;
        for (col=0; col < res[row].size(); col++) {
            DEBUG "[pgTest] col nr.:" << col ;
            DEBUG "[pgTest] value:" << res[row][col].as<string>() << "\t" ;
        }
        DEBUG "end of loop";
    }    
    DEBUG "========== pgTest - end ==========" ;
    return list_2d;
 
    
    
}

string DatabaseProxy::sqlMasquerading ( string origin ){
    DEBUG "[OR1345988559] sqlMasquerading";
    if ( m_sqlQuotas == "\'" ) {
        DEBUG "[OR1345988559] 1";
        return replace( origin, "'", "\\'" );
    } else if ( m_sqlQuotas == "\"" ) {
        DEBUG "[OR1345988559] 2";
        return replace( origin, "\"", "\\\"" );
    } else {
        DEBUG "[OR1345988559] 3";
        throw "unknown quota type!";
    }
}

void DatabaseProxy::sqlSet ( string sqlcommand )
{
    
    DEBUG "SQL-CODE: \n <begin>" << sqlcommand  << "<end>";
    DEBUG "[OR1336745746] sqlSet ( string sqlcommand )" ;
        
    DEBUG "========== pgTest - begin ==========" ;

    DEBUG "========== pgTest - 1 ==========" ;
    m_pg_work->exec(
        "INSERT INTO category (title, subtitle) \
        VALUES ( 'Tier', 'Hund');" );

    DEBUG "========== pgTest - end ==========" ;
}

std::string& DatabaseProxy::replace(std::string& s, char c, const std::string& r)
{
    std::string::size_type p = 0;

    while ((p = s.find(c, p)) != std::string::npos) {
        s.replace(p, 1, r);
        p += r.length();
    }

    return s;
}

std::string& DatabaseProxy::replace(std::string& s, const std::string& k, const std::string& r)
{
    DEBUG "[OR1345988343] replace";
    DEBUG "s" << s;
    DEBUG "k" << k;
    DEBUG "r" << r;
    
    std::string::size_type p = 0;

    while ((p = s.find(k, p)) != std::string::npos) {
        s.replace(p, k.length(), r);
        p += r.length();
  }

  DEBUG "return s" << s;
  return s;
}

void DatabaseProxy::setQuotaType ( string quotaTyp ){
    m_sqlQuotas = quotaTyp;
}
