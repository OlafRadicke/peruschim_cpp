
#include "Quote.h"


void Quote::saveAsNew() {
    DEBUG std::endl;
    std::string sqlcommand = "";
    Config config;
    vector<string>   list_1d;
    std:: string isPrivateData = "false";

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
    tntdb::Result result;

    conn = tntdb::connect( conn_para );
    DEBUG std::endl;
    result = conn.select( "SELECT nextval('quote_id_seq'::regclass);" );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it)
    {
        tntdb::Row row = *it;
        row[0].get( this->m_ID );
    }

    if ( m_isPrivateData ) {
        isPrivateData = "true";
    }
    DEBUG std::endl;

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
                        " + DatabaseProxy::replace( this->m_ownerID ) + ", \n\
                        " + DatabaseProxy::replace( this->m_editionID ) + ", \n\
                        '" + isPrivateData + "' \n\
                    ); \n";

    for (unsigned int i=0; this->m_quoteKeywords.size()>i; i++ ) {
        sqlcommand += "INSERT INTO quote_keyword \n\
                      ( \n\
                        quote_id, \n\
                        title \n\
                      ) VALUES ( \n\
                        " + this->m_ID + ", \n\
                        '" + this->m_quoteKeywords[i] + "' \n\
                        );\n";
    }

    sqlcommand += "COMMIT;";

    try {
        DEBUG "sqlcommand: " << sqlcommand << std::endl;
        conn.execute( sqlcommand );
        DEBUG std::endl;
    } catch( char * str ) {
        ERROR  "Exception raised: " << str << '\n';
    }
}

void Quote::setKeywords( std::string keywords ) {
    m_quoteKeywords.clear();
    unsigned int found;

    keywords = strReplace ( " ", "", keywords );
    keywords = lowercase ( keywords );
    std::string separator = ",";
    found = keywords.find_first_of( separator );
    while(found != string::npos){
        if(found > 0){
            m_quoteKeywords.push_back(keywords.substr(0,found));
        }
        keywords = keywords.substr(found+1);
        found = keywords.find_first_of(separator);
    }
    if(keywords.length() > 0){
        m_quoteKeywords.push_back(keywords);
    }
}

string Quote::lowercase ( string keywords ) {
    keywords = strReplace ( "A", "a", keywords);
    keywords = strReplace ( "B", "b", keywords);
    keywords = strReplace ( "C", "c", keywords);
    keywords = strReplace ( "D", "d", keywords);
    keywords = strReplace ( "E", "e", keywords);
    keywords = strReplace ( "F", "f", keywords);
    keywords = strReplace ( "G", "g", keywords);
    keywords = strReplace ( "H", "h", keywords);
    keywords = strReplace ( "I", "i", keywords);
    keywords = strReplace ( "J", "j", keywords);
    keywords = strReplace ( "K", "k", keywords);
    keywords = strReplace ( "L", "l", keywords);
    keywords = strReplace ( "M", "m", keywords);
    keywords = strReplace ( "N", "n", keywords);
    keywords = strReplace ( "O", "o", keywords);
    keywords = strReplace ( "P", "p", keywords);
    keywords = strReplace ( "Q", "q", keywords);
    keywords = strReplace ( "R", "r", keywords);
    keywords = strReplace ( "S", "s", keywords);
    keywords = strReplace ( "T", "t", keywords);
    keywords = strReplace ( "U", "u", keywords);
    keywords = strReplace ( "V", "v", keywords);
    keywords = strReplace ( "W", "w", keywords);
    keywords = strReplace ( "X", "x", keywords);
    keywords = strReplace ( "Y", "y", keywords);
    keywords = strReplace ( "Z", "z", keywords);
    keywords = strReplace ( "Ä", "ä", keywords);
    keywords = strReplace ( "Ö", "ö", keywords);
    keywords = strReplace ( "Ü", "ü", keywords);
    return keywords;
}


string Quote::strReplace (string rep, string wit, string in) {
  int pos;
  while (true) {
    pos = in.find(rep);
    if (pos == -1) {
      break;
    } else {
      in.erase(pos, rep.length());
      in.insert(pos, wit);
    }
  }
  return in;
}

