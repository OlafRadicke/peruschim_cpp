/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright GNU Affero General Public License
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

#include <tntdb/connect.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>
#include <tntdb/row.h>
#include <tntdb/transaction.h>
#include <cxxtools/log.h>

#include <Core/manager/TableManager.h>
#include <Core/models/Config.h>

/*#include <iostream>  */  
// #include <ostream>
#include <sstream>

log_define("TableManager")


TableManager::TableManager()
    : m_conn(tntdb::connectCached( Config::it().dbDriver() ))
{ }

// G -------------------------------------------------------------------------

std::string TableManager::getTabeVersion(){
    std::string  tabVersion;
    
    tntdb::Statement st = m_conn.prepare( " SELECT data_value \
         FROM metadata \
         WHERE data_name = :data_name ;");

    // Wenn wir nur einen einzelnen Wert lesen wollen, dann verwenden wir tntdb::Statement::selectValue().

    tntdb::Value value = st.set( "data_name", "tableversion" )
                       .selectValue();

    value.get(tabVersion);
    return tabVersion;    
    
}

// S -------------------------------------------------------------------------

bool TableManager::setUpdate2(){
    tntdb::Transaction trans(m_conn);
    std::ostringstream sqlCommand;

    try{
        sqlCommand << "CREATE TABLE account_trust ("
        << "    id                   SERIAL    PRIMARY KEY,"
        << "    trusted_account_id   BIGINT    NOT NULL,"
        << "    guarantor_id         BIGINT    NOT NULL,"
        << "    createtime           TIMESTAMP NOT NULL,"
        << "    FOREIGN KEY  (trusted_account_id)   REFERENCES account (id),"
        << "    FOREIGN KEY  (guarantor_id) REFERENCES account (id)"
        << ");";
        m_conn.prepare( sqlCommand.str() ).execute();
        sqlCommand.flush();
        
        sqlCommand << "-- COMMENT ON TABLE account_trust IS 'Links for user trust user.';";
        m_conn.prepare( sqlCommand.str() ).execute(); 
        sqlCommand.flush();
        
        sqlCommand << "-- COMMENT ON COLUMN account_trust.trusted_account_id IS "
        << "'The account where we are in trust.';";
        m_conn.prepare( sqlCommand.str() ).execute(); 
        sqlCommand.flush();
        
        sqlCommand << "-- COMMENT ON COLUMN account_trust.guarantor_id IS "
        << "'This account give the guarant.';";
        m_conn.prepare( sqlCommand.str() ).execute(); 
        sqlCommand.flush();

        //  Default value
        sqlCommand << "INSERT INTO account_trust"
        << "("
        << "    trusted_account_id,"
        << "    guarantor_id,"
        << "    createtime"
        << ")"
        << "VALUES ("
        << "    1,"
        << "    1,"
        << "    now()"
        << ");";
        m_conn.prepare( sqlCommand.str() ).execute(); 
        sqlCommand.flush();
        
        sqlCommand << "UPDATE metadata "
        << "SET data_value = '00002', "
        << "data_parameter = 'alpha' "
        << "WHERE data_name = 'tableversion';";
        m_conn.prepare( sqlCommand.str() ).execute(); 
        sqlCommand.flush();

        trans.commit();
    }catch (...) {
        return false;
    }
    return true;
}

//  U ------------------------------------------------------------------------


    bool TableManager::update(){
        std::string version = getTabeVersion();
        
        if ( version == "00001" ) {
            if( setUpdate2() == false){
                log_info( "Table update 00002 failed!");
                return false;
            }else{
                log_info( "Table update 00002 is successful!");
            }
        }
   
        
/*      for next version...  
        if ( version = "00002" ) {
            if( setUpdate3() == false){
                log_info( "Table update 00003 failed!");
                return false;
            }else{
                log_info( "Table update 00003 is successful!");
            }
        } 
*/  

        return true;
        
    }
