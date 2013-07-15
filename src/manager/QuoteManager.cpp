/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#include <manager/QuoteManager.h>

#include <models/Config.h>
#include <models/Quote.h>

#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <tntdb/statement.h>

QuoteManager::QuoteManager(tntdb::Connection& conn_)
    : conn(conn_)
{ }

QuoteManager::QuoteManager()
    : conn(tntdb::connectCached( Config().dbDriver() ))
{
}

/**
 * Save Quote as new data set in database.
 **/
void QuoteManager::saveAsNew(Quote& quote)
{
    tntdb::Transaction trans(conn);

    tntdb::Statement insQuote = conn.prepare(
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
    );

    insQuote.set( "bookSeries", quote.m_bookSeries )
            .set( "bookTitle", quote.m_bookTitle )
            .set( "bookChapterBegin", quote.m_bookChapterBegin )
            .set( "bookSentenceBegin", quote.m_bookSentenceBegin )
            .set( "bookChapterEnd", quote.m_bookChapterEnd )
            .set( "bookSentenceEnd", quote.m_bookSentenceEnd )
            .set( "quoteText", quote.m_quoteText )
            .set( "note", quote.m_note )
            .set( "ownerID", quote.m_ownerID )
            .set( "editionID", quote.m_editionID )
            .set( "isPrivateData", quote.m_isPrivateData )
            .execute();

    quote.m_ID = conn.lastInsertId("quote_id_seq");

    tntdb::Statement insQuoteKeyword = conn.prepare(
            "INSERT INTO quote_keyword \
             ( \
                 quote_id, \
                 title \
             ) VALUES ( \
                 :quote_id, \
                 :title \
             )"
        );

    insQuoteKeyword.set( "quote_id", quote.m_ID );

    for (unsigned int i=0; i < quote.m_quoteKeywords.size(); ++i )
    {
        insQuoteKeyword.set( "title", quote.m_quoteKeywords[i] )
                       .execute();
    }

    trans.commit();
}

/**
 * Update Quote in database.
 **/
void QuoteManager::update(const Quote& quote)
{
    tntdb::Transaction trans(conn);

    tntdb::Statement updQuote = conn.prepare(
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
    );

    updQuote.set( "bookSeries", quote.m_bookSeries )
            .set( "bookTitle", quote.m_bookTitle )
            .set( "bookChapterBegin", quote.m_bookChapterBegin )
            .set( "bookSentenceBegin", quote.m_bookSentenceBegin )
            .set( "bookChapterEnd", quote.m_bookChapterEnd )
            .set( "bookSentenceEnd", quote.m_bookSentenceEnd )
            .set( "quoteText", quote.m_quoteText )
            .set( "note", quote.m_note )
            .set( "ownerID", quote.m_ownerID )
            .set( "editionID", quote.m_editionID )
            .set( "isPrivateData", quote.m_isPrivateData )
            .set( "id", quote.m_ID )
            .execute();

    tntdb::Statement delQuoteKeywords = conn.prepare(
            "DELETE FROM quote_keyword \
              WHERE quote_id = :quote_id");

    delQuoteKeywords.set("quote_id", quote.m_ID)
                    .execute();

    tntdb::Statement insQuoteKeyword = conn.prepare(
            "INSERT INTO quote_keyword \
             ( \
                 quote_id, \
                 title \
             ) VALUES ( \
                 :quote_id, \
                 :title \
             )"
        );

    insQuoteKeyword.set( "quote_id", quote.m_ID );

    for (unsigned int i=0; i < quote.m_quoteKeywords.size(); ++i )
    {
        insQuoteKeyword.set( "title", quote.m_quoteKeywords[i] )
                       .execute();
    }

    trans.commit();
}
