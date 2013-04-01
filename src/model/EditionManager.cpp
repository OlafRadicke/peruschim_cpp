
#include <string>
#include <list>
#include <iostream>
#include <cxxtools/log.h>
#include <vector>
#include <pqxx/pqxx>

#include "Config.h"
#include "EditionManager.h"
#include "Edition.h"


# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<



/* G ----------------------------------------------------------------------- */


std::vector<Edition> EditionManager::getAllEditions ( void ){
    std::vector<Edition> editionList;
    DEBUG std::endl;
    
    Config config;
    std::string db_name = config.get( "DB-NAME" );
    std::string db_host = config.get( "DB-HOST" ); 
    std::string db_user = config.get( "DB-USER" ); 
    std::string db_passwd = config.get( "DB-PASSWD" ); 
    std::string db_port = config.get( "DB-PORT" ); 
    
    std::string sqlcommand =    "SELECT \
                        id, \
                        name, \
                        publishername, \
                        releasenumber, \
                        releaseplace \
                    FROM edition;";    
 
    string conn_para = "password=" + db_passwd +\
        " dbname=" + db_name + \
        " host=" + db_host + \
        " port=" + db_port + \
        " user=" + db_user ;    
    pqxx::connection pg_conn( conn_para );
    pqxx::work  pg_worker( pg_conn );
    pqxx::result res;
    unsigned int     row_count;
    vector<string>   list_1d;
    vector< vector<string> >  list_2d;
    res = pg_worker.exec( sqlcommand );         
    pg_worker.commit();
//     DEBUG " found: " << res.size() << endl;
    
    for (row_count=0; row_count < res.size(); row_count++) {
        Edition edition;
        edition.setID( res[row_count][0].as<string>() );
        edition.setName( res[row_count][1].as<string>() );
        edition.setPublisherName( res[row_count][2].as<string>() );
        edition.setReleaseNumber( res[row_count][3].as<string>() );
        edition.setReleasePlace( res[row_count][4].as<string>() );
        editionList.push_back ( edition );
    }    
    
    pg_conn.disconnect();
    return editionList;
}
