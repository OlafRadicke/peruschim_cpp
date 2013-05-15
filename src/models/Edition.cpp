# include "Edition.h"


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
