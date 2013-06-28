/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or later
* version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "EditionManager.h"
#include <tntdb/connect.h>
#include <tntdb/statement.h>


# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

/* D ----------------------------------------------------------------------- */

void EditionManager::deleteEditionByID ( const unsigned long id ) {
    Config config;
    std::string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

    tntdb::Statement st = conn.prepare( "DELETE FROM edition \
                    WHERE id= :v1 ;");
    st.set( "v1", id ).execute();
}

/* G ----------------------------------------------------------------------- */


std::vector<Edition> EditionManager::getAllEditions ( const unsigned long user_id ){
    DEBUG "user_id: " << user_id  << std::endl;
    std::vector<Edition> editionList;
    Config config;
    std::string conn_para = config.get( "DB-DRIVER" );
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

        edition.setID( row[0].getInt() );
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


Edition EditionManager::getEditionByID ( const unsigned long id ) {
    Edition edition;
    Config config;
    std::string conn_para = config.get( "DB-DRIVER" );
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

        edition.setID( row[0].getInt() );
        edition.setOwnerID( row[1].getInt() );
        edition.setName( row[2].getString () );
        edition.setPublisherName( row[3].getString () );
        edition.setReleaseNumber( row[4].getString () );
        edition.setReleasePlace( row[5].getString () );
        edition.setReleaseDate( row[6].getString () );

        return edition;
    }
    std::string errorinfo = "Edition with id " + cxxtools::convert<std::string>( id ) + " no found!";
    throw errorinfo;

}

/* I ----------------------------------------------------------------------- */

int EditionManager::isEditionInUse ( const unsigned long id ){
    Config config;
    std::string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect(conn_para);

    tntdb::Statement st = conn.prepare( " SELECT COUNT(edition_id) \
         FROM quote \
         WHERE edition_id = :v1 ;");
    st.set( "v1", id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        Edition edition;

        return row[0].getInt();
    }
    return 0;

}
