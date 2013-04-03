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
    
    /**
     * The default construktor set the database connection on the system 
     * database.
     **/
    DatabaseProxy( );
    
     /**
     * Convert int to string.
     * @param sqlcommand a sql command.
     **/       
    static std::string convertIntToStr( int number );  
    
     /**
     * Do a SQL command without result.
     * @param sqlcommand a sql command.
     **/      
    void sqlSet( string sqlcommand );

     /**
     * get back a SQL result as 3d vector.
     * @param sqlcommand a sql command.
     * @return If nothing found, it is get back a empty string. 
     **/   
    vector< vector<string> >  sqlGet( string sqlcommand );
    
    /**
     * get back the first fund of result.
     * @param sqlcommand a sql command.
     * @return If nothing found, it is get back a empty string. 
     **/
    string  sqlGetSingle ( string sqlcommand );

    /**
     * Replace a char with a string.
     * @param s origin string
     * @return a string with the replaceings.
     */ 
    static std::string replace ( std::string s );    
    
    /**
     * Replace a char with a string.
     * @param s origin string
     * @param K searching char
     * @param r replace string
     * @return a string with the replaceings.
     */ 
    static std::string replace (
        std::string s, 
        const std::string& k, 
        const std::string& r 
    );
    
    /**
     * Set the type of quota.
     * @param quotaTyp default set is '
     */
    void setQuotaType ( string quotaTyp ); 

private:
    
    
    /**
     * Global config class.
     */
//     Config           *m_config;
    
    
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
