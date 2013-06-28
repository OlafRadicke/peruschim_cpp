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

#include <cxxtools/jsondeserializer.h>
#include <cxxtools/jsonserializer.h>
#include <cxxtools/serializationinfo.h>
#include <tntdb/transaction.h>
#include <tntdb/connect.h>
#include <tntdb/connection.h>

#include "Config.h"
#include "OString.h"
#include "Quote.h"
#include "QuoteRegister.h"
#include "EditionManager.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

void QuoteRegister::deleteAllQuoteOfUser( const unsigned long userID ){
    DEBUG "deleteAllQuoteOfUser: " << userID << std::endl;
    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect( conn_para );
    tntdb::Transaction trans(conn);
    conn.prepare( "DELETE FROM  quote_keyword \n\
        WHERE quote_id IN ( SELECT id FROM quote WHERE owner_id= :v1 )")
    .set( "v1",  userID ).execute();

    conn.prepare( "DELETE FROM  quote \n\
        WHERE owner_id= :v1 ;").set( "v1",  userID ).execute();
    trans.commit();
}

void QuoteRegister::deleteQuote( const unsigned long quoteID ) {
    DEBUG "deleteQuote: " << quoteID << std::endl;
    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
    tntdb::Connection conn = tntdb::connect( conn_para );
    tntdb::Transaction trans(conn);
    conn.prepare( "DELETE FROM  quote_keyword \n\
        WHERE quote_id = :quoteid ")
    .set( "quoteid", quoteID ).execute();

    conn.prepare( "DELETE FROM  quote \n\
        WHERE id = :quoteid ;").set( "quoteid", quoteID ).execute();
    trans.commit();
}

std::vector<Quote> QuoteRegister::getQuotes ( tntdb::Statement st ){
    DEBUG std::endl;
    std::vector< Quote > quoteList;

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        DEBUG std::endl;
        tntdb::Row row = *it;
        Quote dataQuote = Quote();

        dataQuote.setBookTitle( row[0].getString() );
        dataQuote.setChapterBegin( row[1].getInt() );
        dataQuote.setChapterEnd( row[2].getInt() );
        dataQuote.setEditionID( row[3].getInt() );
        dataQuote.setID( row[4].getInt() );
        dataQuote.setIsPrivateData( row[5].getBool() );
        dataQuote.setNote( row[6].getString() );
        dataQuote.setOwnerID( row[7].getInt() );
        dataQuote.setQuoteText( row[8].getString() );
        dataQuote.setSentenceBegin ( row[9].getInt() );
        dataQuote.setSentenceEnd( row[10].getInt() );
        dataQuote.setSeries( row[11].getString() );

        quoteList.push_back( dataQuote );
    }
    return quoteList;

}

Quote QuoteRegister::getQuoteWithID( const unsigned long id ) {
    DEBUG std::endl;
    std::vector< Quote > quoteList;
    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
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
    WHERE id= " <<  id << std::endl;
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
        std::string errorinfo = "quote " + cxxtools::convert<std::string>( id ) + " does not exist!";
        // TODO never throw an std::string!!!
        throw errorinfo;
    }

}

std::vector<Quote> QuoteRegister::getAllPubQuoteOfKeyword( const std::string keyword ) {
    DEBUG std::endl;
    std::vector< Quote > quoteList;
    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
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
        dataQuote.setEditionID( row[3].getInt() );
        dataQuote.setID( row[4].getInt() );
        dataQuote.setIsPrivateData( row[5].getBool() );
        dataQuote.setNote( row[6].getString() );
        dataQuote.setOwnerID( row[7].getInt() );
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
* define how to deserialize the Edition
* @arg si serialization info
* @arg Edition
*/
void operator>>= ( const cxxtools::SerializationInfo& si, Edition& edition )
{
    DEBUG "deserialize the Edition..." << std::endl;
    std::string strValue;

    si.getMember("name") >>= strValue;
    DEBUG "strValue: " << strValue << std::endl;
    edition.setName(strValue);
    si.getMember("publisher-name") >>= strValue;
    edition.setPublisherName(strValue);
    si.getMember("release-date") >>= strValue;
    edition.setReleaseDate(strValue);
    si.getMember("release-number") >>= strValue;
    edition.setReleaseNumber(strValue);
    si.getMember("release-place") >>= strValue;
    edition.setReleasePlace(strValue);
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

/**
* define how to deserialize the Quote
* @arg si serialization info
* @arg Quote
*/
void operator>>= ( const cxxtools::SerializationInfo& si, Quote& quote)
{
    DEBUG "deserialize the Quote: " << std::endl;
    std::string strValue;
    int intValue;
    std::vector<std::string> vectorValue;
    bool boolValue;
    Edition editionValue;

    si.getMember( "book-title" ) >>= strValue;
    DEBUG "strValue: " << strValue << std::endl;
    quote.setBookTitle( strValue );
    si.getMember("chapter-begin") >>= intValue;
    quote.setChapterBegin( intValue );
    si.getMember("chapter-end") >>= intValue;
    quote.setChapterEnd( intValue );
    si.getMember("keywords") >>= vectorValue;
    quote.setKeywords( vectorValue );
    si.getMember("note") >>= strValue;
    quote.setNote( strValue );
    si.getMember("quote-text") >>= strValue;
    quote.setQuoteText( strValue );
    si.getMember("sentence-begin") >>= intValue;
    quote.setSentenceBegin( intValue );
    si.getMember("sentence-end") >>= intValue;
    quote.setSentenceEnd( intValue );
    si.getMember("private-data") >>= boolValue;
    quote.setIsPrivateData( boolValue );
    si.getMember("edition") >>= editionValue;
    quote.setTmpEditionData( editionValue );
}
/**
 * define a container object for user quotes export.
 */
struct QuoteExportContainer
{
    std::vector<Quote> allUserQuotes;
};


/**
* define how to serialize the QuoteExportContainer
* @arg si serialization info
* @arg QuoteExportContainer
*/
void operator<<= ( cxxtools::SerializationInfo& si, 
                   const QuoteExportContainer& quoteContainer )
{
    si.addMember("user-quotes") <<= quoteContainer.allUserQuotes;
}

/**
* define how to deserialize the QuoteExportContainer
* @arg si serialization info
* @arg QuoteExportContainer
*/
void operator>>= ( const cxxtools::SerializationInfo& si, 
                   QuoteExportContainer& quoteContainer)
{
    DEBUG "deserialize the QuoteExportContainer... " << std::endl;
    si.getMember("user-quotes") >>= quoteContainer.allUserQuotes;
}

std::string QuoteRegister::getJsonExport( const unsigned long userID ) {
    std::string json_text;
    DEBUG "userID: " << userID << std::endl;

    QuoteExportContainer quoteContainer;
    quoteContainer.allUserQuotes = QuoteRegister::getAllQuoteOfUser( userID );
    try
    {
        std::stringstream sstream;
        cxxtools::JsonSerializer serializer( sstream );
        // this makes it just nice to read
        serializer.beautify(true);
        serializer.serialize( quoteContainer ).finish();
        json_text = sstream.str();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return json_text;
}


std::vector<Quote> QuoteRegister::getAllQuoteOfUser( const unsigned long userID ) {
    DEBUG "userID: " << userID << std::endl;
    std::vector< Quote > quoteList;
    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
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
        const unsigned long userID ){

    DEBUG "keyword: " << keyword <<  std::endl;
    DEBUG "userID: " << userID << std::endl;
    std::vector< Quote > quoteList;
    Config config;

    std::string conn_para = config.get( "DB-DRIVER" );
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

void QuoteRegister::jsonImport( const std::string jsonText, 
                                unsigned long owner_id ) {
    try
    {
        // define a empty config object
        QuoteExportContainer quoteContainer;
        std::stringstream sstream;
        sstream.str( jsonText );

        // read json configuration struct from stdin:
        cxxtools::JsonDeserializer deserializer( sstream );
        deserializer.deserialize( quoteContainer );
        DEBUG "quoteContainer.allUserQuotes.size(): "
            << quoteContainer.allUserQuotes.size() <<  std::endl;


        for (unsigned n = 0; n < quoteContainer.allUserQuotes.size(); ++n) {
            DEBUG "n: " << n << std::endl;
            quoteContainer.allUserQuotes[n].setOwnerID( owner_id );
            Edition edition = quoteContainer.allUserQuotes[n].getTmpEditionData( );
            edition.setOwnerID( owner_id );
            quoteContainer.allUserQuotes[n]
                .setEditionID( edition.saveAsNewIfNotExist() );
            quoteContainer.allUserQuotes[n].saveAsNew();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}

