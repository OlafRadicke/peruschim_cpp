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

#include <Core/models/Config.h>
#include <Core/models/PeruschimException.h>
#include <Core/models/Quote.h>
#include <Core/manager/QuoteRegister.h>
#include <Core/manager/EditionManager.h>
#include <Core/manager/QuoteManager.h>

#include <cxxtools/jsondeserializer.h>
#include <cxxtools/jsonserializer.h>
#include <cxxtools/log.h>
#include <cxxtools/serializationinfo.h>
#include <tntdb/transaction.h>
#include <tntdb/connect.h>
#include <tntdb/connection.h>

#include <ostream>


log_define("core.manager.QuoteRegister")

void QuoteRegister::deleteAllQuoteOfUser( const unsigned long userID ){
    log_debug( "deleteAllQuoteOfUser: " << userID );

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Transaction trans(conn);
    conn.prepare( "DELETE FROM  quote_keyword \n\
        WHERE quote_id IN ( SELECT id FROM quote WHERE owner_id= :v1 )")
    .set( "v1",  userID ).execute();

    conn.prepare( "DELETE FROM  quote \n\
        WHERE owner_id= :v1 ;").set( "v1",  userID ).execute();
    trans.commit();
}

void QuoteRegister::deleteQuote( const unsigned long quoteID ) {
    log_debug( "deleteQuote: " << quoteID );

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    tntdb::Transaction trans(conn);
    conn.prepare( "DELETE FROM  quote_keyword \n\
        WHERE quote_id = :quoteid ")
    .set( "quoteid", quoteID ).execute();

    conn.prepare( "DELETE FROM  quote \n\
        WHERE id = :quoteid ;").set( "quoteid", quoteID ).execute();
    trans.commit();
}

std::vector<Quote> QuoteRegister::getQuotes ( tntdb::Statement st ){
    std::vector< Quote > quoteList;

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

Quote QuoteRegister::getQuoteWithID( const unsigned long id ) {
    std::vector< Quote > quoteList;
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
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

    quoteList = getQuotes ( st );
    if ( quoteList.size() == 1 ) {
        return quoteList[0];
    } else {
        std::ostringstream errorText;
        errorText <<  "quote " <<  id
            << " does not exist!";
        throw Core::PeruschimException( errorText.str() );
    }

}

std::vector<Quote> QuoteRegister::getAllPubQuoteOfKeyword( const std::string keyword ) {
    std::vector< Quote > quoteList;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
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
    log_debug( "deserialize the Edition..." );
    std::string strValue;

    si.getMember("name") >>= strValue;
    log_debug( "strValue: " << strValue );
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
    EditionManager editionManager;
    si.addMember("book-title") <<= quote.getBookTitle();
    si.addMember("chapter-begin") <<= quote.getChapterBegin();
    si.addMember("chapter-end") <<= quote.getChapterEnd();
    si.addMember("keywords") <<= const_cast<Quote*>(&quote)->getKeywords();
    si.addMember("note") <<= quote.getNote();
    si.addMember("quote-text") <<= quote.getQuoteText();
    si.addMember("sentence-begin") <<= quote.getSentenceBegin();
    si.addMember("sentence-end") <<= quote.getSentenceEnd();
    si.addMember("private-data") <<= quote.isPrivateData();
    si.addMember("edition") <<= editionManager.getEditionByID( quote.getEditionID() );
}

/**
* define how to deserialize the Quote
* @arg si serialization info
* @arg Quote
*/
void operator>>= ( const cxxtools::SerializationInfo& si, Quote& quote)
{
    log_debug( "deserialize the Quote: " );
    std::string strValue;
    int intValue;
    std::vector<std::string> vectorValue;
    bool boolValue;
    Edition editionValue;

    si.getMember( "book-title" ) >>= strValue;
    log_debug( "strValue: " << strValue );
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
    log_debug( "deserialize the QuoteExportContainer... " );
    si.getMember("user-quotes") >>= quoteContainer.allUserQuotes;
}

std::string QuoteRegister::getJsonExport( const unsigned long userID ) {
    std::string json_text;
    log_debug( "getJsonExport for userID: " << userID );

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
    log_debug( "userID: " << userID );
    std::vector< Quote > quoteList;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
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
    ORDER BY series, title, chapter_begin, sentence_begin" );
    st.set( "v1", userID ).execute();

    return getQuotes ( st );
}


std::vector<Quote> QuoteRegister::getAllQuoteOfKeyword(
        const std::string keyword,
        const unsigned long userID ){

    log_debug( "getAllQuoteOfKeyword keyword: " << keyword );
    log_debug( "getAllQuoteOfKeyword userID: " << userID );
    std::vector< Quote > quoteList;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
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
        QuoteExportContainer quoteContainer;
        std::stringstream sstream;
        sstream.str( jsonText );

        // read json configuration struct from stdin:
        cxxtools::JsonDeserializer deserializer( sstream );
        deserializer.deserialize( quoteContainer );
        log_debug( "quoteContainer.allUserQuotes.size(): "
            << quoteContainer.allUserQuotes.size() );

        tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
        tntdb::Transaction trans(conn);

        EditionManager editionManager(conn);
        QuoteManager quoteManager(conn);

        for (unsigned n = 0; n < quoteContainer.allUserQuotes.size(); ++n)
        {
            quoteContainer.allUserQuotes[n]
                          .setOwnerID( owner_id );

            Edition edition = quoteContainer.allUserQuotes[n]
                                            .getTmpEditionData( );

            edition.setOwnerID( owner_id );

            quoteContainer.allUserQuotes[n]
                          .setEditionID( editionManager.saveAsNewIfNotExist(edition) );

            quoteManager.saveAsNew(quoteContainer.allUserQuotes[n]);
        }

        trans.commit();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

}

