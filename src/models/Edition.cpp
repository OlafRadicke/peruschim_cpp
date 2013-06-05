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

# include "Edition.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

void Edition::saveAsNew(){
    DEBUG std::endl;
    std::string sqlcommand = "";
    Config config;
    vector<string>   list_1d;
    std:: string isPrivateData = "false";
    tntdb::Result result;
    string conn_para = config.get( "DB-DRIVER" );

    tntdb::Connection conn = tntdb::connect( conn_para );
    DEBUG std::endl;

    result = conn.select( "SELECT nextval('quote_id_seq'::regclass);" );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it)
    {
        tntdb::Row row = *it;
        this->m_id = row[0].getString();
    }

    sqlcommand =   "INSERT INTO edition  ( \n\
                        id, \n\
                        owner_id,  \n\
                        name,  \n\
                        publishername,  \n\
                        releasenumber,  \n\
                        releasedate,  \n\
                        releaseplace  \n\
                    ) VALUES ( \n \
                        " + DatabaseProxy::replace( this->m_id ) + ", \n\
                        " + DatabaseProxy::replace( this->m_owner_id ) + ", \n\
                        '" + DatabaseProxy::replace( this->m_name ) + "',  \n\
                        '',  \n\
                        '',  \n\
                        '',  \n\
                        ''  \n\
                    ) ";

    try {
        DEBUG "sqlcommand: " << sqlcommand << std::endl;
        conn.execute( sqlcommand );
        DEBUG std::endl;
    } catch( char * str ) {
        ERROR  "Exception raised: " << str << '\n';
    }
}

std::string  Edition::saveAsNewIfNotExist(){
    DEBUG std::endl;
    bool editionFound = false;
    std::string sqlcommand = "";
    Config config;
    vector<string>   list_1d;
    std:: string isPrivateData = "false";

    string conn_para = config.get( "DB-DRIVER" );

    tntdb::Connection conn = tntdb::connect( conn_para );
    DEBUG std::endl;

    tntdb::Statement st = conn.prepare( "SELECT id FROM edition \n\
                    WHERE owner_id = :v1  \n\
                    AND name = :v2; " );
    st.set("v1", this->m_owner_id )
    .set("v2", this->m_name ).execute();

    for ( tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it ) {
        tntdb::Row row = *it;
        DEBUG "id: " <<  row[0].getString() << std::endl;
        this->m_id = row[0].getString();
        editionFound = true;
    }

    if ( !editionFound ) {
        // create new data set.
        saveAsNew();
    }
    return this->m_id;
}

void Edition::saveUpdate(){
    DEBUG std::endl;
    std::string sqlcommand = "";
    Config config;
    vector<string>   list_1d;
    std:: string isPrivateData = "false";

    string conn_para = config.get( "DB-DRIVER" );

    tntdb::Connection conn = tntdb::connect( conn_para );
    DEBUG std::endl;

    sqlcommand =   "UPDATE edition SET \n\
                        owner_id = " + DatabaseProxy::replace( this->m_owner_id ) + ", \n\
                        name = '" + DatabaseProxy::replace( this->m_name ) + "', \
                        publishername = '" + DatabaseProxy::replace( this->m_publisherName ) + "', \
                        releasenumber = '" + DatabaseProxy::replace( this->m_releaseNumber ) + "', \
                        releasedate = '" + DatabaseProxy::replace( this->m_releaseDate ) + "', \
                        releaseplace = '" + DatabaseProxy::replace( this->m_releasePlace ) + "' \
                    WHERE id = " + this->m_id + "; \n";


    try {
        DEBUG "sqlcommand: " << sqlcommand << std::endl;
        conn.execute( sqlcommand );
        DEBUG std::endl;
    } catch( char * str ) {
        ERROR  "Exception raised: " << str << '\n';
    }
}
