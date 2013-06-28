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

#include "Edition.h"
#include <tntdb/error.h>
#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/statement.h>
#include <iostream>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

void Edition::saveAsNew(){
    DEBUG std::endl;

    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    try {
        conn = tntdb::connect( conn_para );
        tntdb::Statement st = conn.prepare( 
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
                ) "
                                        );
        
        st.set("owner_id", this->m_ownerID )
        .set("name", this->m_name ).execute();
        
        this->m_ID = conn.lastInsertId("edition_id_seq");
    } catch( const tntdb::Error& e ) {
        ERROR  "Exception raised: " << e.what() << '\n';
    }        
    
}

unsigned long  Edition::saveAsNewIfNotExist(){
    DEBUG std::endl;
    bool editionFound = false;
    std::string sqlcommand = "";
    Config config;
    std::vector<std::string>   list_1d;

    std::string conn_para = config.get( "DB-DRIVER" );

    tntdb::Connection conn = tntdb::connect( conn_para );
    DEBUG std::endl;

    tntdb::Statement st = conn.prepare( "SELECT id FROM edition \n\
                    WHERE owner_id = :v1  \n\
                    AND name = :v2; " );
    st.set("v1", this->m_ownerID )
    .set("v2", this->m_name ).execute();

    for ( tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it ) {
        tntdb::Row row = *it;
        DEBUG "id: " <<  row[0].getString() << std::endl;
        this->m_ID = row[0].getInt();
        editionFound = true;
    }

    if ( !editionFound ) {
        // create new data set.
        saveAsNew();
    }
    return this->m_ID;
}

void Edition::saveUpdate(){
    DEBUG std::endl;

    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    try {
        conn = tntdb::connect( conn_para );
        tntdb::Statement st = conn.prepare( 
            "UPDATE edition SET \n\
                    owner_id = :ownerID, \n\
                    name = :name, \
                    publishername = :publisherName, \
                    releasenumber = :releaseNumber, \
                    releasedate = :releaseDate, \
                    releaseplace = :releasePlace \
                WHERE id = :id"
        );
        
        st.set("ownerID", this->m_ownerID )
        .set("name", this->m_name )
        .set("publisherName", this->m_publisherName )
        .set("releaseNumber", this->m_releaseNumber )
        .set("releaseDate", this->m_releaseDate )
        .set("releasePlace", this->m_releasePlace )
        .set("id", this->m_ID ).execute();
        
    } catch( const tntdb::Error& e ) {
        ERROR  "Exception raised: " << e.what() << '\n';
    }     

    
}
