
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
    Config config;
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;
    
    conn = tntdb::connect(conn_para);
    result = conn.select( sqlcommand );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        string id;
        string name;
        string publisherName;
        string releaseNumber;
        string releasePlace;                
        Edition edition;
        
        edition.setID( row[0].getString () );
        row[1].get( name ); 
        edition.setName( name );
        row[2].get( publisherName ); 
        edition.setPublisherName( publisherName );
        row[3].get( releaseNumber ); 
        edition.setReleaseNumber( releaseNumber );
        row[4].get( releasePlace ); 
        edition.setReleasePlace( releasePlace );
        editionList.push_back ( edition );
    }    
    return editionList;
}
