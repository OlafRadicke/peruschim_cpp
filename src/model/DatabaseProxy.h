#ifndef DATABASEPROXY_H
#define DATABASEPROXY_H 
 
#include <vector>
#include <string>
#include <iostream>
#include <pqxx/pqxx>

#include "Config.h"

using namespace std;
 
class DatabaseProxy {
    
public:

    string m_dbbackent;
    
    DatabaseProxy( );
    DatabaseProxy( int i ) { cout << "[" << __FILE__ << ":" << __LINE__ << "] " << endl; };
    ~DatabaseProxy();
    
    
    void sqlSet( string sqlcommand );

    vector< vector<string> > sqlGet( string sqlcommand );
    
    /**
     * Replace a char with a string.
     * @param s origin string
     * @param K searching char
     * @param r replace string
     * @return a string with the replaceings.
     */ 
    static std::string replace(std::string s, const std::string& k, const std::string& r);
    
    /**
     * Set the type of quota.
     * @param quotaTyp default set is '
     */
    void setQuotaType ( string quotaTyp ); 

private:
    
    
    /**
     * Global config class.
     */
    Config           *m_config;
    
    /**
     * PostreSQL types
     */
    pqxx::connection *m_pg_conn;
    
    pqxx::work       *m_pg_work;
    
    /** PostreSQL database name */    
    string           m_pg_db_name;
    /** PostreSQL database host */    
    string           m_pg_db_host;
    /** PostreSQL database user */  
    string           m_pg_db_user;
    /** PostreSQL database password */  
    string           m_pg_db_passwd;
    /** PostreSQL database port */  
    string           m_pg_db_port;
    
    /**
     * The pyte of used quotas. Default is '
     */
    string              m_sqlQuotas;

   
};

#endif 
