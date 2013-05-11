

#include "Config.h"
#include "Quote.h"
#include "QuoteRegister.h"

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

std::vector<Quote> QuoteRegister::getAllQuoteOfKeyword(
        const std::string keyword,
        const std::string userID ){

    DEBUG std::endl;
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


