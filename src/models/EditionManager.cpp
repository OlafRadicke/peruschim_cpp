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
#include "Config.h"
#include <tntdb/connect.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>
#include <tntdb/row.h>
#include <cxxtools/log.h>

log_define("EditionManager")


EditionManager::EditionManager()
    : m_conn(tntdb::connectCached( Config().get( "DB-DRIVER" ) ))
{ }

EditionManager::EditionManager(tntdb::Connection& conn)
    : m_conn(conn)
{ }

/* D ----------------------------------------------------------------------- */

void EditionManager::deleteEditionByID ( unsigned long id ) {

    tntdb::Statement st = m_conn.prepare( "DELETE FROM edition \
                    WHERE id= :v1 ;");

    st.set( "v1", id )
      .execute();
}

/* G ----------------------------------------------------------------------- */


std::vector<Edition> EditionManager::getAllEditions ( unsigned long user_id ){
    log_debug("user_id: " << user_id);

    std::vector<Edition> editionList;

    tntdb::Statement st = m_conn.prepare( "SELECT \
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

    log_debug("editionList.size(): " <<  editionList.size());
    return editionList;
}


Edition EditionManager::getEditionByID ( unsigned long id ) {

    tntdb::Statement st = m_conn.prepare( "SELECT \
                        id, \
                        owner_id, \
                        name, \
                        publishername, \
                        releasenumber, \
                        releaseplace, \
                        releasedate \
                    FROM edition \
                    WHERE id= :v1 ");
    Edition edition;
    try
    {
        // Um eine einzelne Zeile zu lesen, verwenden wir tntdb::Statement::selectRow().
        // Sie wirft eine Exception vom Typ tntdb::Notfound, wenn keine Zeile gefunden wurde.

        tntdb::Row row = st.set( "v1", id )
                           .selectRow();

        edition.setID( row[0].getInt() );
        edition.setOwnerID( row[1].getInt() );
        edition.setName( row[2].getString () );
        edition.setPublisherName( row[3].getString () );
        edition.setReleaseNumber( row[4].getString () );
        edition.setReleasePlace( row[5].getString () );
        edition.setReleaseDate( row[6].getString () );

    }
    catch (const tntdb::NotFound&)
    {
        std::string errorinfo = "Edition with id " + cxxtools::convert<std::string>( id ) + " no found!";
        throw std::runtime_error(errorinfo);
    }

    return edition;
}

/* I ----------------------------------------------------------------------- */

bool EditionManager::isEditionInUse ( unsigned long id ){

    tntdb::Statement st = m_conn.prepare( " SELECT COUNT(edition_id) \
         FROM quote \
         WHERE edition_id = :v1 ;");

    // Wenn wir nur einen einzelnen Wert lesen wollen, dann verwenden wir tntdb::Statement::selectValue().

    tntdb::Value v = st.set( "v1", id )
                       .selectValue();

    unsigned count = 0;
    v.get(count);
    return count > 0;

}

void EditionManager::saveAsNew( Edition& edition )
{
    tntdb::Statement st = m_conn.prepare( 
        "INSERT INTO edition  ( \
                owner_id,       \
                name,           \
                publishername,  \
                releasenumber,  \
                releasedate,    \
                releaseplace    \
            ) VALUES (          \
                :owner_id,      \
                :name,          \
                '',             \
                '',             \
                '',             \
                ''              \
            ) " );

    
    st.set("owner_id", edition.m_ownerID )
      .set("name", edition.m_name )
      .execute();
    
    edition.setID(m_conn.lastInsertId("edition_id_seq"));

}

unsigned long  EditionManager::saveAsNewIfNotExist( Edition& edition )
{
    try
    {
        tntdb::Statement st = m_conn.prepare( "SELECT id FROM edition \n\
                        WHERE owner_id = :v1  \n\
                        AND name = :v2 " );

        st.set("v1", edition.getOwnerID() )
          .set("v2", edition.getName() )
          .selectValue();
    }
    catch (const tntdb::NotFound&)
    {
        saveAsNew(edition);
    }

    return edition.getID();
}

void EditionManager::saveUpdate( const Edition& edition )
{
    tntdb::Statement st = m_conn.prepare( 
        "UPDATE edition SET \n\
                owner_id = :ownerID, \n\
                name = :name, \
                publishername = :publisherName, \
                releasenumber = :releaseNumber, \
                releasedate = :releaseDate, \
                releaseplace = :releasePlace \
            WHERE id = :id"
    );
    
    st.set("ownerID", edition.m_ownerID )
      .set("name", edition.m_name )
      .set("publisherName", edition.m_publisherName )
      .set("releaseNumber", edition.m_releaseNumber )
      .set("releaseDate", edition.m_releaseDate )
      .set("releasePlace", edition.m_releasePlace )
      .set("id", edition.m_ID )
      .execute();
}
