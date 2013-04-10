
#include "KeywordRegister.h"
#include "Config.h"

using namespace std; 

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<



vector<string> KeywordRegister::getAllKeywordTitles( void ){
    DEBUG std::endl;
    vector<string> keywordList; 
    Config config;
    
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;
    
    conn = tntdb::connect(conn_para);
    result = conn.select( "SELECT DISTINCT title title FROM quote_keyword ORDER BY title" );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        std::string title;
        row[0].get(title); 
        keywordList.push_back( title ); 
    }    
    return keywordList;
}

vector< vector<string> > KeywordRegister::getAllKeywordTitlesAndCounds( void ){
    DEBUG std::endl;
    vector< vector<string> > keywordList; 
    Config config;
    
    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;
    
    conn = tntdb::connect(conn_para);
    result = conn.select( "SELECT title, COUNT(title) As Anzahl \
                            FROM quote_keyword GROUP BY title ORDER BY title" );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        vector<string> dataSet;
        std::string title;
        dataSet.push_back( row[0].getString() ); 
        dataSet.push_back( row[1].getString() ); 
        keywordList.push_back( dataSet ); 
    }    
    return keywordList;
}