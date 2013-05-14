
#include "EditionManager.h"


# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<



/* G ----------------------------------------------------------------------- */


std::vector<Edition> EditionManager::getAllEditions ( const string user_id ){
    DEBUG "user_id: " << user_id  << std::endl;
    std::vector<Edition> editionList;
    Config config;
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

    tntdb::Statement st = conn.prepare( "SELECT \
                        id, \
                        name, \
                        publishername, \
                        releasenumber, \
                        releaseplace, \
                        releasedate \
                    FROM edition \
                    WHERE owner_id = :v1;");
    st.set( "v1", user_id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        Edition edition;

        edition.setID( row[0].getString () );
        edition.setName( row[1].getString () );
        edition.setPublisherName( row[2].getString () );
        edition.setReleaseNumber( row[3].getString () );
        edition.setReleasePlace( row[4].getString () );
        edition.setOwnerID( user_id );
        edition.setReleaseDate( row[5].getString () );

        editionList.push_back ( edition );
    }

    DEBUG "editionList.size(): " <<  editionList.size() << std::endl;
    return editionList;
}


Edition EditionManager::getEditionByID ( const string id ) {
    Edition edition;
    Config config;
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

    tntdb::Statement st = conn.prepare( "SELECT \
                        id, \
                        owner_id, \
                        name, \
                        publishername, \
                        releasenumber, \
                        releaseplace, \
                        releasedate \
                    FROM edition \
                    WHERE id= :v1 ;");
    st.set( "v1", id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        Edition edition;

        edition.setID( row[0].getString () );
        edition.setOwnerID( row[1].getString () );
        edition.setName( row[2].getString () );
        edition.setPublisherName( row[3].getString () );
        edition.setReleaseNumber( row[4].getString () );
        edition.setReleasePlace( row[5].getString () );
        edition.setReleaseDate( row[6].getString () );

        return edition;
    }
    string errorinfo = "Edition with id " + id + " no found!";
    throw errorinfo;

}
