

#include "Config.h"
#include "Quote.h"
#include "QuoteRegister.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

std::vector<Quote> QuoteRegister::getQuotes ( tntdb::Statement st ){
    DEBUG std::endl;
    vector< Quote > quoteList;

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        DEBUG std::endl;
        tntdb::Row row = *it;
        Quote dataQuote = Quote();

        dataQuote.setBookTitle( row[0].getString() );
        dataQuote.setChapterBegin( row[1].getInt() );
        dataQuote.setChapterEnd( row[2].getInt() );
        dataQuote.setEditionID( row[3].getString() );
        dataQuote.setID( row[4].getString() );
        dataQuote.setIsPrivateData( row[5].getBool() );
        dataQuote.setNote( row[6].getString() );
        dataQuote.setOwnerID( row[7].getString() );
        dataQuote.setQuoteText( row[8].getString() );
        dataQuote.setSentenceBegin ( row[9].getInt() );
        dataQuote.setSentenceEnd( row[10].getInt() );
        dataQuote.setSeries( row[11].getString() );

        quoteList.push_back( dataQuote );
    }
    return quoteList;

}

Quote QuoteRegister::getQuoteWithID( const std::string id ) {
    DEBUG std::endl;
    vector< Quote > quoteList;
    Config config;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
//     tntdb::Result result;

    DEBUG std::endl;
    DEBUG "SQL: " << "SELECT \
        title, \
        chapter_begin, \
        chapter_end, \
        edition_id, \
        id, \
        privatedata, \
        note, \
        owner_id, \
        quote_text, \
        sentence_begin, \
        sentence_end, \
        series \
    FROM quote \
    WHERE id= " <<  id << endl;
    conn = tntdb::connect(conn_para);
    tntdb::Statement st = conn.prepare( "SELECT \
        title, \
        chapter_begin, \
        chapter_end, \
        edition_id, \
        id, \
        privatedata, \
        note, \
        owner_id, \
        quote_text, \
        sentence_begin, \
        sentence_end, \
        series \
    FROM quote \
    WHERE id= :v1 " );
    st.set( "v1", id )
    .execute();

    DEBUG std::endl;
    quoteList = getQuotes ( st );
    if ( quoteList.size() == 1 ) {
        DEBUG std::endl;
        return quoteList[0];
    } else {
        std::string errorinfo = "quote " + id + " is not exist!";
        throw errorinfo;
    }

}

std::vector<Quote> QuoteRegister::getAllPubQuoteOfKeyword( const std::string keyword ) {
    DEBUG std::endl;
    vector< Quote > quoteList;
    Config config;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;

    conn = tntdb::connect(conn_para);
    tntdb::Statement st = conn.prepare( "SELECT \
        title, \
        chapter_begin, \
        chapter_end, \
        edition_id, \
        id, \
        privatedata, \
        note, \
        owner_id, \
        quote_text, \
        sentence_begin, \
        sentence_end, \
        series \
    FROM quote \
    WHERE id in ( \
        SELECT quote_id \
        FROM quote_keyword \
        WHERE title= :v1) \
    AND privatedata = 'FALSE'\
    ORDER BY series, title, chapter_begin" );
    st.set("v1", keyword).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        Quote dataQuote = Quote();

        dataQuote.setBookTitle( row[0].getString() );
        dataQuote.setChapterBegin( row[1].getInt() );
        dataQuote.setChapterEnd( row[2].getInt() );
        dataQuote.setEditionID( row[3].getString() );
        dataQuote.setID( row[4].getString() );
        dataQuote.setIsPrivateData( row[5].getBool() );
        dataQuote.setNote( row[6].getString() );
        dataQuote.setOwnerID( row[7].getString() );
        dataQuote.setQuoteText( row[8].getString() );
        dataQuote.setSentenceBegin ( row[9].getInt() );
        dataQuote.setSentenceEnd( row[10].getInt() );
        dataQuote.setSeries( row[11].getString() );

        quoteList.push_back( dataQuote );
    }
    return quoteList;

}

/**
* define how to serialize the Edition
* @arg si serialization info
* @arg Edition
*/
void operator<<= ( cxxtools::SerializationInfo& si, const Edition& edition )
{
    si.addMember("name") <<= edition.getName();
    si.addMember("publisher-name") <<= edition.getPublisherName();
    si.addMember("release-date") <<= edition.getReleaseDate();
    si.addMember("release-number") <<= edition.getReleaseNumber();
    si.addMember("release-place") <<= edition.getReleasePlace();
}

/**
* define how to serialize the Quote
* @arg si serialization info
* @arg Quote
*/
void operator<<= ( cxxtools::SerializationInfo& si, const Quote& quote )
{
    si.addMember("book-title") <<= quote.getBookTitle();
    si.addMember("chapter-begin") <<= quote.getChapterBegin();
    si.addMember("chapter-end") <<= quote.getChapterEnd();
    si.addMember("keywords") <<= const_cast<Quote*>(&quote)->getKeywords();
    si.addMember("note") <<= quote.getNote();
    si.addMember("quote-text") <<= quote.getQuoteText();
    si.addMember("sentence-begin") <<= quote.getSentenceBegin();
    si.addMember("sentence-end") <<= quote.getSentenceEnd();
    si.addMember("private-data") <<= quote.isPrivateData();
    si.addMember("edition") <<= EditionManager::getEditionByID( quote.getEditionID() );
}

std::string QuoteRegister::getJsonExport( const std::string userID ) {
    std::string jason_text;
    DEBUG "userID: " << userID << std::endl;

    std::vector<Quote> allUserQuotes = QuoteRegister::getAllQuoteOfUser( userID );

    for ( unsigned int i_q = 0; i_q < allUserQuotes.size(); i_q++ ) {
        DEBUG "i_q: " << i_q << std::endl;
        for ( unsigned int i_k = 0; i_k < allUserQuotes[i_q].m_quoteKeywords.size(); i_k++ ) {
            DEBUG "allUserQuotes[i_q].m_quoteKeywords[i_k]: " << allUserQuotes[i_q].m_quoteKeywords[i_k] << std::endl;
        }
        // serialize to json
        try
        {
            std::stringstream sstream;
            cxxtools::JsonSerializer serializer( sstream );
            // this makes it just nice to read
            serializer.beautify(true);
            serializer.serialize( allUserQuotes[i_q] ).finish();

            while (sstream.good())
            {
                char c = sstream.get();
                if (sstream.good())
                    jason_text += c;

            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    return jason_text;
}


std::vector<Quote> QuoteRegister::getAllQuoteOfUser( const std::string userID ) {
    DEBUG "userID: " << userID << std::endl;
    vector< Quote > quoteList;
    Config config;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;

    conn = tntdb::connect(conn_para);
    tntdb::Statement st = conn.prepare( "SELECT \
        title, \
        chapter_begin, \
        chapter_end, \
        edition_id, \
        id, \
        privatedata, \
        note, \
        owner_id, \
        quote_text, \
        sentence_begin, \
        sentence_end, \
        series \
    FROM quote \
    WHERE owner_id= :v1  \
    ORDER BY series, title, chapter_begin" );
    st.set( "v1", userID ).execute();

    return getQuotes ( st );
}


std::vector<Quote> QuoteRegister::getAllQuoteOfKeyword(
        const std::string keyword,
        const std::string userID ){

    DEBUG "keyword: " << keyword <<  std::endl;
    DEBUG "userID: " << userID << std::endl;
    vector< Quote > quoteList;
    Config config;

    string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn;
//     tntdb::Result result;

    conn = tntdb::connect(conn_para);
    tntdb::Statement st = conn.prepare( "SELECT \
        title, \
        chapter_begin, \
        chapter_end, \
        edition_id, \
        id, \
        privatedata, \
        note, \
        owner_id, \
        quote_text, \
        sentence_begin, \
        sentence_end, \
        series \
    FROM quote \
    WHERE ( privatedata = 'FALSE'\
        OR owner_id= :v2 ) \
    AND  id in ( \
        SELECT quote_id \
        FROM quote_keyword \
        WHERE title= :v1) \
    ORDER BY series, title, chapter_begin" );
    st.set( "v1", keyword )
    .set( "v2", userID )
    .execute();

    return getQuotes ( st );
}


