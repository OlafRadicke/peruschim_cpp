
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

#include "Quote.h"
#include "Config.h"
#include <tntdb/transaction.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>
#include <tntdb/error.h>
#include <cxxtools/join.h>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

Quote::Quote()
  : m_isPrivateData(false),
    m_ownerID(0),
    m_bookChapterBegin(0),
    m_bookSentenceBegin(0),
    m_bookChapterEnd(0),
    m_bookSentenceEnd(0)
{
}


std::vector<std::string> Quote::getKeywords() {
    Config config;

    if ( this->m_quoteKeywords.size() < 1 && this->m_ID > 0 ) {

        tntdb::Result result;
        tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );
        tntdb::Statement st = conn.prepare( "SELECT title \
            FROM quote_keyword \
            WHERE quote_id = :v1 \
            ORDER BY title" );
        st.set("v1", this->m_ID );

        for ( tntdb::Statement::const_iterator it = st.begin(); it != st.end(); ++it )
        {
            tntdb::Row row = *it;
            Quote dataQuote = Quote();
            this->m_quoteKeywords.push_back( row[0].getString() );
        }
    }
    return this->m_quoteKeywords;
}

std::string Quote::getKeywordsAsString()
{
    std::vector<std::string> keywords = getKeywords();
    return cxxtools::join(keywords.begin(), keywords.end(), ',');
}

void Quote::saveAsNew() {

    DEBUG std::endl;
    Config config;
    try {
        tntdb::Connection conn = 
            tntdb::connectCached( config.dbDriver() );

        DEBUG std::endl;
        tntdb::Transaction trans(conn);
        conn.prepare(
            "INSERT INTO quote \
            ( \
                series, \
                title, \
                chapter_begin, \
                sentence_begin, \
                chapter_end, \
                sentence_end, \
                quote_text, \
                note, \
                owner_id, \
                edition_id, \
                privatedata \
            ) VALUES ( \
                :bookSeries, \
                :bookTitle, \
                :bookChapterBegin, \
                :bookSentenceBegin, \
                :bookChapterEnd, \
                :bookSentenceEnd, \
                :quoteText, \
                :note, \
                :ownerID, \
                :editionID, \
                :isPrivateData \
            )"
        )
        .set( "bookSeries", this->m_bookSeries )
        .set( "bookTitle", this->m_bookTitle )
        .set( "bookChapterBegin", this->m_bookChapterBegin )
        .set( "bookSentenceBegin", this->m_bookSentenceBegin )
        .set( "bookChapterEnd", this->m_bookChapterEnd )
        .set( "bookSentenceEnd", this->m_bookSentenceEnd )
        .set( "quoteText", this->m_quoteText )
        .set( "note", this->m_note )
        .set( "ownerID", this->m_ownerID )
        .set( "editionID", this->m_editionID )
        .set( "isPrivateData", m_isPrivateData ).execute();

        DEBUG std::endl;
        this->m_ID = conn.lastInsertId("quote_id_seq");
        DEBUG std::endl;

        for (unsigned int i=0; this->m_quoteKeywords.size()>i; i++ ) {
            conn.prepare(
                "INSERT INTO quote_keyword \
                        ( \
                            quote_id, \
                            title \
                        ) VALUES ( \
                            :quote_id, \
                            :title \
                        )"
            ).set( "quote_id", this->m_ID )
            .set( "title", this->m_quoteKeywords[i] ).execute();
        }

        DEBUG std::endl;
        trans.commit();

    } catch( const tntdb::Error& e ) {
        ERROR  "Exception raised: " << e.what() << '\n';
    } 
}

void Quote::saveUpdate(){

    DEBUG std::endl;
    Config config;
    try {
        tntdb::Connection conn = 
            tntdb::connectCached( config.dbDriver() );

        tntdb::Transaction trans(conn);
        conn.prepare(
            "UPDATE quote SET \
                series = :bookSeries, \
                title = :bookTitle, \
                chapter_begin = :bookChapterBegin, \
                sentence_begin = :bookSentenceBegin, \
                chapter_end = :bookChapterEnd, \
                sentence_end = :bookSentenceEnd, \
                quote_text = :quoteText, \
                note = :note, \
                owner_id = :ownerID, \
                edition_id = :editionID, \
                privatedata = :isPrivateData \
            WHERE id = :id"
        )
        .set( "bookSeries", this->m_bookSeries )
        .set( "bookTitle", this->m_bookTitle )
        .set( "bookChapterBegin", this->m_bookChapterBegin )
        .set( "bookSentenceBegin", this->m_bookSentenceBegin )
        .set( "bookChapterEnd", this->m_bookChapterEnd )
        .set( "bookSentenceEnd", this->m_bookSentenceEnd )
        .set( "quoteText", this->m_quoteText )
        .set( "note", this->m_note )
        .set( "ownerID", this->m_ownerID )
        .set( "editionID", this->m_editionID )
        .set( "isPrivateData", m_isPrivateData )
        .set( "id", this->m_ID ).execute();

        for (unsigned int i=0; this->m_quoteKeywords.size()>i; i++ ) {
            conn.prepare(
                "INSERT INTO quote_keyword \
                        ( \
                            quote_id, \
                            title \
                        ) VALUES ( \
                            :quote_id, \
                            :title \
                        )"
            ).set( "quote_id", this->m_ID )
            .set( "title", this->m_quoteKeywords[i] ).execute();
        }
        trans.commit();
    } catch( const tntdb::Error& e ) {
        ERROR  "Exception raised: " << e.what() << '\n';
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
        std::string keyword = keywords.substr(0,found);
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
                if ( keywords.size() > 0 ) {
                    m_quoteKeywords.push_back( keywords );
                }
                break;
            }
        } else {
            keywords == "";
            break;
        }
    }
    DEBUG "m_quoteKeywords.size(): "  << m_quoteKeywords.size() << std::endl;
}


std::string Quote::lowercase ( std::string keywords ) {
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

std::string Quote::strReplace (std::string rep, std::string with, std::string in) {
  int pos;
  while (true) {
    pos = in.find(rep);
    if (pos == -1) {
      break;
    } else {
      in.erase(pos, rep.length());
      in.insert(pos, with);
    }
  }
  return in;
}

