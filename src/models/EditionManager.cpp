
#include "EditionManager.h"


# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<



/* G ----------------------------------------------------------------------- */


std::vector<Edition> EditionManager::getAllEditions ( void ){
    std::vector<Edition> editionList;
    DEBUG std::endl;
    std::string sqlcommand =    "SELECT \
                        id, \
                        name, \
                        publishername, \
                        releasenumber, \
                        releaseplace \
                    FROM edition;";  
    DEBUG std::endl; 
    Config config;
    DEBUG std::endl;
    string conn_para = config.get( "DB-DRIVER" );
    DEBUG std::endl;
    tntdb::Connection conn;
    DEBUG std::endl;
    tntdb::Result result;
    DEBUG std::endl;
    
    conn = tntdb::connect(conn_para);
    DEBUG std::endl;
    result = conn.select( sqlcommand );
    DEBUG std::endl;
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        DEBUG std::endl;
        tntdb::Row row = *it;
        DEBUG std::endl;           
        Edition edition;
        DEBUG std::endl;
        
        edition.setID( row[0].getString () );
        DEBUG std::endl;
        edition.setName( row[1].getString () );
        DEBUG std::endl;
        edition.setPublisherName( row[2].getString () );
        DEBUG std::endl;
        edition.setReleaseNumber( row[3].getString () );
        DEBUG std::endl;
        edition.setReleasePlace( row[4].getString () );
        DEBUG std::endl;
        
        editionList.push_back ( edition );
    }    
    DEBUG std::endl;
    return editionList;
}
