#include "Quote.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

    Quote::Quote():
        allBibleBooks(),
        BibleserverComNames()
    {
        this->m_isPrivateData = false;
        this->m_ownerID = "0";
        this->m_bookChapterBegin = 0;
        this->m_bookSentenceBegin = 0;
        this->m_bookChapterEnd = 0;
        this->m_bookSentenceEnd = 0;
        allBibleBooks.push_back("1. Mose");
        allBibleBooks.push_back("2. Mose");
        allBibleBooks.push_back("3. Mose");
        allBibleBooks.push_back("4. Mose");
        allBibleBooks.push_back("5. Mose");
        allBibleBooks.push_back("Josua");
        allBibleBooks.push_back("Richter");
        allBibleBooks.push_back("Rut");
        allBibleBooks.push_back("1. Samuel");
        allBibleBooks.push_back("2. Samuel");
        allBibleBooks.push_back("1. Könige");
        allBibleBooks.push_back("2. Könige");
        allBibleBooks.push_back("1. Chronik");
        allBibleBooks.push_back("2. Chronik");
        allBibleBooks.push_back("Esra");
        allBibleBooks.push_back("Nehemia");
        allBibleBooks.push_back("Tobit");
        allBibleBooks.push_back("Judit");
        allBibleBooks.push_back("Ester");
        allBibleBooks.push_back("1. Makkabäer");
        allBibleBooks.push_back("2. Makkabäer");
        allBibleBooks.push_back("3. Makkabäer");
        allBibleBooks.push_back("4. Makkabäer");
        allBibleBooks.push_back("Ijob");
        allBibleBooks.push_back("Psalmen");
        allBibleBooks.push_back("Sprichwörter");
        allBibleBooks.push_back("Kohelet");
        allBibleBooks.push_back("Hoheslied");
        allBibleBooks.push_back("Weisheit");
        allBibleBooks.push_back("Jesus Sirach");
        allBibleBooks.push_back("Gebet des Manasse");
        allBibleBooks.push_back("Psalmen Salomos");
        allBibleBooks.push_back("Klagelieder Jeremias");
        allBibleBooks.push_back("Jesaja");
        allBibleBooks.push_back("Jeremia");
        allBibleBooks.push_back("Ezechiel");
        allBibleBooks.push_back("Baruch");
        allBibleBooks.push_back("Brief des Jeremia");
        allBibleBooks.push_back("Daniel");
        allBibleBooks.push_back("Hosea");
        allBibleBooks.push_back("Joel");
        allBibleBooks.push_back("Amos");
        allBibleBooks.push_back("Obadja");
        allBibleBooks.push_back("Jona");
        allBibleBooks.push_back("Micha");
        allBibleBooks.push_back("Nahum");
        allBibleBooks.push_back("Habakuk");
        allBibleBooks.push_back("Zefanja");
        allBibleBooks.push_back("Haggai");
        allBibleBooks.push_back("Sacharja");
        allBibleBooks.push_back("Maleachi");
        allBibleBooks.push_back("Matthäus");
        allBibleBooks.push_back("Markus");
        allBibleBooks.push_back("Lukas");
        allBibleBooks.push_back("Johannes");
        allBibleBooks.push_back("Apostelgeschichte");
        allBibleBooks.push_back("Römer");
        allBibleBooks.push_back("1. Korinther");
        allBibleBooks.push_back("2. Korinther");
        allBibleBooks.push_back("Galater");
        allBibleBooks.push_back("Epheser");
        allBibleBooks.push_back("Philipper");
        allBibleBooks.push_back("Kolosser");
        allBibleBooks.push_back("1. Thessalonicher");
        allBibleBooks.push_back("2. Thessalonicher");
        allBibleBooks.push_back("1. Timotheus");
        allBibleBooks.push_back("2. Timotheus");
        allBibleBooks.push_back("Titus");
        allBibleBooks.push_back("Philemon");
        allBibleBooks.push_back("Hebräer");
        allBibleBooks.push_back("Jakobus");
        allBibleBooks.push_back("1. Petrus");
        allBibleBooks.push_back("2. Petrus");
        allBibleBooks.push_back("1. Johannes");
        allBibleBooks.push_back("2. Johannes");
        allBibleBooks.push_back("3. Johannes");
        allBibleBooks.push_back("Judas");
        allBibleBooks.push_back("Offenbarung");

        // the maching with book name of bibleserver.com
        BibleserverComNames["1. Mose"] = "1.Mose";
        BibleserverComNames["2. Mose"] = "2.Mose";
        BibleserverComNames["3. Mose"] = "3.Mose";
        BibleserverComNames["4. Mose"] = "4.Mose";
        BibleserverComNames["5. Mose"] = "5.Mose";
        BibleserverComNames["Josua"] = "Josua";
        BibleserverComNames["Richter"] = "Richter";
        BibleserverComNames["Rut"] = "Rut";
        BibleserverComNames["1. Samuel"] = "1.Samuel";
        BibleserverComNames["2. Samuel"] = "2.Samuel";
        BibleserverComNames["1. Könige"] = "1.Könige";
        BibleserverComNames["2. Könige"] = "2.Könige";
        BibleserverComNames["1. Chronik"] = "1.Chronik";
        BibleserverComNames["2. Chronik"] = "2.Chronik";
        BibleserverComNames["Esra"] = "Esra";
        BibleserverComNames["Nehemia"] = "Nehemia";
        BibleserverComNames["Tobit"] = "Tobit";
        BibleserverComNames["Judit"] = "Judit";
        BibleserverComNames["Ester"] = "Esther";
        BibleserverComNames["1. Makkabäer"] = "1.Makkabäer";
        BibleserverComNames["2. Makkabäer"] = "2.Makkabäer";
        BibleserverComNames["3. Makkabäer"] = "";
        BibleserverComNames["4. Makkabäer"] = "";
        BibleserverComNames["Ijob"] = "Hiob";
        BibleserverComNames["Psalmen"] = "Psalmen";
        BibleserverComNames["Sprichwörter"] = "Sprüche";
        BibleserverComNames["Kohelet"] = "Prediger";
        BibleserverComNames["Hoheslied"] = "Hoheslied";
        BibleserverComNames["Weisheit"] = "Weisheit";
        BibleserverComNames["Jesus Sirach"] = "Jesus Sirach";
        BibleserverComNames["Gebet des Manasse"] = "";
        BibleserverComNames["Psalmen Salomos"] = "";
        BibleserverComNames["Klagelieder Jeremias"] = "Klagelieder";
        BibleserverComNames["Jesaja"] = "Jesaja";
        BibleserverComNames["Jeremia"] = "Jeremia";
        BibleserverComNames["Ezechiel"] = "Hesekiel";
        BibleserverComNames["Baruch"] = "Baruch";
        BibleserverComNames["Brief des Jeremia"] = "";
        BibleserverComNames["Daniel"] = "Daniel";
        BibleserverComNames["Hosea"] = "Hosea";
        BibleserverComNames["Joel"] = "Joel";
        BibleserverComNames["Amos"] = "Amos";
        BibleserverComNames["Obadja"] = "Obadja";
        BibleserverComNames["Jona"] = "Jona";
        BibleserverComNames["Micha"] = "Micha";
        BibleserverComNames["Nahum"] = "Nahum";
        BibleserverComNames["Habakuk"] = "Habakuk";
        BibleserverComNames["Zefanja"] = "Zefanja";
        BibleserverComNames["Haggai"] = "Haggai";
        BibleserverComNames["Sacharja"] = "Sacharja";
        BibleserverComNames["Maleachi"] = "Maleachi";
        BibleserverComNames["Matthäus"] = "Matthäus";
        BibleserverComNames["Markus"] = "Markus";
        BibleserverComNames["Lukas"] = "Lukas";
        BibleserverComNames["Johannes"] = "Johannes";
        BibleserverComNames["Apostelgeschichte"] = "Apostelgeschichte";
        BibleserverComNames["Römer"] = "Römer";
        BibleserverComNames["1. Korinther"] = "1.Korinther";
        BibleserverComNames["2. Korinther"] = "2.Korinther";
        BibleserverComNames["Galater"] = "Galater";
        BibleserverComNames["Epheser"] = "Epheser";
        BibleserverComNames["Philipper"] = "Philipper";
        BibleserverComNames["Kolosser"] = "Kolosser";
        BibleserverComNames["1. Thessalonicher"] = "1.Thessalonicher";
        BibleserverComNames["2. Thessalonicher"] = "2.Thessalonicher";
        BibleserverComNames["1. Timotheus"] = "1.Timotheus";
        BibleserverComNames["2. Timotheus"] = "2.Timotheus";
        BibleserverComNames["Titus"] = "Titus";
        BibleserverComNames["Philemon"] = "Philemon";
        BibleserverComNames["Hebräer"] = "Hebräer";
        BibleserverComNames["Jakobus"] = "Jakobus";
        BibleserverComNames["1. Petrus"] = "1.Petrus";
        BibleserverComNames["2. Petrus"] = "2.Petrus";
        BibleserverComNames["1. Johannes"] = "1.Johannes";
        BibleserverComNames["2. Johannes"] = "2.Johannes";
        BibleserverComNames["3. Johannes"] = "3.Johannes";
        BibleserverComNames["Judas"] = "Judas";
        BibleserverComNames["Offenbarung"] = "Offenbarung";
    }


const std::string Quote::getBibleserverComURL() {
    if( this->m_bookTitle == "" ) return "";
    if( this->m_bookChapterBegin == 0 ) return "";

    std::stringstream sstr;
    sstr << this->m_bookChapterBegin;

    std::string url = "http://www.bibleserver.com/text/EU/";
    url += BibleserverComNames[this->m_bookTitle] + "/" + sstr.str();
    return url;
}

std::vector<std::string> Quote::getKeywords() {
    DEBUG std::endl;
    Config config;

    if ( this->m_quoteKeywords.size() < 1 && this->m_ID != "") {
        string conn_para = config.get( "DB-DRIVER" );
        tntdb::Connection conn;
        tntdb::Result result;

        conn = tntdb::connect( conn_para );
        DEBUG std::endl;
        tntdb::Statement st = conn.prepare( "SELECT title \
            FROM quote_keyword \
            WHERE quote_id = :v1 \
            ORDER BY title" );
        st.set("v1", this->m_ID ).execute();

        for ( tntdb::Statement::const_iterator it = st.begin();
            it != st.end(); ++it ) {
            DEBUG std::endl;
            tntdb::Row row = *it;
            Quote dataQuote = Quote();

            this->m_quoteKeywords.push_back( row[0].getString() );

        }
    }
    return this->m_quoteKeywords;
}

std::string Quote::getKeywordsAsString(){
    DEBUG std::endl;
    Config config;
    std::string keywordsAsString = "";

    if ( this->m_quoteKeywords.size() < 1 && this->m_ID != "") {
        string conn_para = config.get( "DB-DRIVER" );
        tntdb::Connection conn;
        tntdb::Result result;
        std::string seperator = "";

        conn = tntdb::connect( conn_para );
        DEBUG std::endl;
        tntdb::Statement st = conn.prepare( "SELECT title \
            FROM quote_keyword \
            WHERE quote_id = :v1 \
            ORDER BY title" );
        st.set("v1", this->m_ID ).execute();

        for ( tntdb::Statement::const_iterator it = st.begin();
            it != st.end(); ++it ) {
            tntdb::Row row = *it;
            Quote dataQuote = Quote();
            DEBUG "single keyword: " <<  row[0].getString() << std::endl;
            DEBUG "seperator: " <<  seperator << std::endl;
            keywordsAsString += seperator + row[0].getString();
            seperator =",";
        }

    } else {
        std::string seperator ="";
        for (unsigned int i=0; this->m_quoteKeywords.size()>i; i++ ) {
            DEBUG "single keyword: " <<  this->m_quoteKeywords[i];
            DEBUG "seperator: " <<  seperator << std::endl;
            keywordsAsString += seperator + this->m_quoteKeywords[i];
            seperator =",";
        }
    }

    return keywordsAsString;
}

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

void Quote::saveUpdate(){
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

    if ( m_isPrivateData ) {
        isPrivateData = "true";
    }
    DEBUG std::endl;

    sqlcommand =   "START TRANSACTION; \n\
                    UPDATE quote SET \n\
                        series = '" + DatabaseProxy::replace( this->m_bookSeries ) + "', \n\
                        title = '" + DatabaseProxy::replace( this->m_bookTitle ) + "', \n\
                        chapter_begin = " +  DatabaseProxy::convertIntToStr( this->m_bookChapterBegin ) + ", \n\
                        sentence_begin = " +  DatabaseProxy::convertIntToStr( this->m_bookSentenceBegin ) + ", \n\
                        chapter_end = " +  DatabaseProxy::convertIntToStr( this->m_bookChapterEnd ) + ", \n\
                        sentence_end = " +  DatabaseProxy::convertIntToStr( this->m_bookSentenceEnd ) + ", \n\
                        quote_text = '" + DatabaseProxy::replace( this->m_quoteText ) + "', \n\
                        note = '" + DatabaseProxy::replace( this->m_note ) + "', \n\
                        owner_id = " + DatabaseProxy::replace( this->m_ownerID ) + ", \n\
                        edition_id = " + DatabaseProxy::replace( this->m_editionID ) + ", \n\
                        privatedata = '" + isPrivateData + "' \n\
                    WHERE id = " + this->m_ID + "; \n";

    sqlcommand += "\n DELETE FROM quote_keyword WHERE quote_id = " + this->m_ID + "; \n";

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
    unsigned int keywordsize = 0;

    DEBUG std::endl;
    if ( keywords == "" ) return;
    DEBUG std::endl;
    keywords = strReplace ( " ", "", keywords );
    DEBUG std::endl;
    keywords = lowercase ( keywords );
    DEBUG std::endl;
    std::string separator = ",";
    found = keywords.find_first_of( separator, 0 );
    DEBUG std::endl;
    while(found!=std::string::npos){
        DEBUG "found: " << found << std::endl;
        string keyword = keywords.substr(0,found);
        m_quoteKeywords.push_back( keyword );
        DEBUG "keyword: " << keyword << std::endl;
        keywordsize = keyword.size();
        DEBUG "Start Index: " << (keywordsize+1) << std::endl;
        DEBUG "keywords.size(): " << keywords.size() << std::endl;
        if ( keywords.size() > (keywordsize+1) ) {
            keywords = keywords.substr(keywordsize+1);
            DEBUG  "keywords: " << keywords << std::endl;
            found = keywords.find_first_of(separator);
            DEBUG  "found: " << found << std::endl;
            if ( found==std::string::npos ) {
                DEBUG  "ENDE ENDE ENDE!!!" << std::endl;
                break;
            }
        } else {
            keywords == "";
            break;
        }
    }
    DEBUG "m_quoteKeywords.size(): "  << m_quoteKeywords.size() << std::endl;
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

