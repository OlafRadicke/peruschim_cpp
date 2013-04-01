
#include "Quote.h"

void Quote::saveAsNew() {
    DEBUG std::endl;
    std::string sqlcommand = "";
    Config config;
    unsigned int     row_count;
    vector<string>   list_1d;   
    std:: string isPrivateData = "false";
    
    string conn_para = "password=" + config.get( "DB-PASSWD" ) +\
        " dbname=" + config.get( "DB-NAME" ) + \
        " host=" + config.get( "DB-HOST" ) + \
        " port=" + config.get( "DB-PORT" ) + \
        " user=" + config.get( "DB-USER" ) ;   
    DEBUG std::endl;
    pqxx::connection pg_conn( conn_para );
    try {
        pqxx::work  pg_worker( pg_conn );
        pqxx::result res;
        DEBUG std::endl;
        
        sqlcommand = "SELECT nextval('quote_id_seq'::regclass);";
        res = pg_worker.exec( sqlcommand );     
        pg_worker.commit();     
        for (row_count=0; row_count < res.size(); row_count++) {
            this->m_ID = res[row_count][0].as<string>();
        }    
        
        if ( m_isPrivateData ) {
            isPrivateData = "true";
        }
        DEBUG std::endl;
        
        pg_conn.disconnect();
    } catch( char * str ) {
        ERROR  "Exception raised: " << str << '\n';
    }
    
    sqlcommand =   "START TRANSACTION; \n\
                    INSERT INTO quote \n\
                    ( \n\
                        id,  \n\
                        series, \n\
                        title, \n\
                        chapter_begin, \n\
                        sentence_begin, \n\
                        chapter_end, \n\
                        sentence_end, \n\
                        quote_text, \n\
                        note, \n\
                        owner_id, \n\
                        edition_id, \n\
                        privatedata \n\
                    ) VALUES ( \n\
                        " + this->m_ID + ", \n\
                        '" + DatabaseProxy::replace( this->m_bookSeries ) + "', \n\
                        '" + DatabaseProxy::replace( this->m_bookTitle ) + "', \n\
                        " +  DatabaseProxy::convertIntToStr( this->m_bookChapterBegin ) + ", \n\
                        " +  DatabaseProxy::convertIntToStr( this->m_bookSentenceBegin ) + ", \n\
                        " +  DatabaseProxy::convertIntToStr( this->m_bookChapterEnd ) + ", \n\
                        " +  DatabaseProxy::convertIntToStr( this->m_bookSentenceEnd ) + ", \n\
                        '" + DatabaseProxy::replace( this->m_quoteText ) + "', \n\
                        '" + DatabaseProxy::replace( this->m_note ) + "', \n\
                        '" + DatabaseProxy::replace( this->m_ownerID ) + "', \n\
                        '" + DatabaseProxy::replace( this->m_editionID ) + "', \n\
                        '" + isPrivateData + "' \n\
                    ); \n";    
    
    for (unsigned int i=0; this->m_quoteLabels.size()>i; i++ ) {
        sqlcommand += "INSERT INTO quote_label \n\
                      ( \n\
                        quote_id, \n\
                        title \n\
                      ) VALUES ( \n\
                        " + this->m_ID + ", \n\
                        '" + this->m_quoteLabels[i] + "' \n\
                        );\n";
    }
 
    sqlcommand += "COMMIT;";

    try {    
        pqxx::work  pg_worker2( pg_conn );
        DEBUG "sqlcommand: " << sqlcommand << std::endl;   
        pqxx::result res = pg_worker2.exec( sqlcommand );  
        DEBUG std::endl;      
        pg_worker2.commit();
        
        pg_conn.disconnect();
    } catch( char * str ) {
        ERROR  "Exception raised: " << str << '\n';
    }
    
    
}

void Quote::setLabels( std::string labels ) {
    m_quoteLabels.clear();
    unsigned int found;
    std::string separator = ",";
    found = labels.find_first_of( separator );
    while(found != string::npos){
        if(found > 0){
            m_quoteLabels.push_back(labels.substr(0,found));
        }
        labels = labels.substr(found+1);
        found = labels.find_first_of(separator);
    }
    if(labels.length() > 0){
        m_quoteLabels.push_back(labels);
    }    
}

