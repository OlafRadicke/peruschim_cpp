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

#include <iostream>

#include <cxxtools/log.h>
#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>


#include "models/WebACL.h"
#include "models/UserSession.h"

#include "manager/BibleManager.h"
#include "manager/EditionManager.h"
#include "manager/QuoteManager.h"
#include "models/Edition.h"
#include "models/Quote.h"
#include "models/UserSession.h"
#include "models/WebACL.h"

log_define("component.NewQuoteController")

class NewQuoteController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<NewQuoteController> factory("NewQuoteController");

unsigned NewQuoteController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );
    TNT_SESSION_SHARED_VAR( BibleManager,             s_bibleManager, () );

    TNT_REQUEST_SHARED_VAR( Quote,                    s_quoteData, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_bibleserverComURL, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );
    TNT_REQUEST_SHARED_VAR( std::vector<Edition>,     s_editionList, () );

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    // define the query parameters
    unsigned long  arg_edition_id =
        qparam.arg<unsigned long>("arg_edition_id");
    std::string  arg_book_title =
        qparam.arg<std::string>("arg_book_title");
    unsigned int arg_chapter_begin =
        qparam.arg<unsigned int>("arg_chapter_begin");
    unsigned int arg_sentence_begin =
        qparam.arg<unsigned int>("arg_sentence_begin");
    unsigned int arg_chapter_end =
        qparam.arg<unsigned int>("arg_chapter_end");
    unsigned int arg_sentence_end =
        qparam.arg<unsigned int>("arg_sentence_end");
    std::string arg_quote_text =
        qparam.arg<std::string>("arg_quote_text");
    std::string arg_keywords =
        qparam.arg<std::string>("arg_keywords");
    std::string arg_note =
        qparam.arg<std::string>("arg_note");
    bool arg_is_private_data =
        qparam.arg<bool>("arg_is_private_data");
    bool arg_create_button =
        qparam.arg<bool>("arg_create_button");
    std::string arg_bible_trans =
        qparam.arg<std::string>("arg_bible_trans");
    bool arg_look_up_button =
        qparam.arg<bool>("arg_look_up_button");

    Edition editionData;
    QuoteManager quoteManager;

    if ( arg_look_up_button ) {
        userSession.setPrefersBibleTrans( arg_bible_trans );
        log_debug( "getBibleserverComURL..." );
        s_quoteData.setEditionID( arg_edition_id );
        s_quoteData.setBookTitle( arg_book_title );
        s_quoteData.setChapterBegin( arg_chapter_begin );
        s_quoteData.setSentenceBegin( arg_sentence_begin );
        log_debug( "pass" );
        s_quoteData.setChapterEnd( arg_chapter_end );
        s_quoteData.setSentenceEnd( arg_sentence_end );
        s_quoteData.setQuoteText( arg_quote_text );
        log_debug( "pass" );
        s_quoteData.setKeywords( arg_keywords );
        s_quoteData.setNote( arg_note );
        log_debug( "arg_is_private_data: " <<  arg_is_private_data );
        s_quoteData.setIsPrivateData( arg_is_private_data );
        log_debug( "pass" );
        log_debug( "s_quoteData.getBibleserverComURL(): "
            << s_bibleManager.getBibleserverComURL( arg_bible_trans, s_quoteData) );
        log_debug( "pass" );
//         s_bibleserverComURL = s_bibleManager.getBibleserverComURL(s_quoteData);
        s_bibleserverComURL =
            s_bibleManager.getBibleserverComURL( arg_bible_trans, s_quoteData);
        log_debug( "s_bibleserverComURL: " << s_bibleserverComURL );
    }

    // is button "create" kicked?
    if ( arg_create_button ) {
        log_debug( "arg_edition_id: " << arg_edition_id );
        s_quoteData.setEditionID( arg_edition_id );

        log_debug( "book_titl: e" << arg_book_title );
        s_quoteData.setBookTitle( arg_book_title );

        log_debug( "arg_chapter_begin: " << arg_chapter_begin );
        s_quoteData.setChapterBegin( arg_chapter_begin );

        log_debug( "arg_sentence_begin: " << arg_sentence_begin );
        s_quoteData.setSentenceBegin( arg_sentence_begin );

        log_debug( "arg_chapter_end: " << arg_chapter_end );
        if ( arg_chapter_end == 0 ) {
            s_quoteData.setChapterEnd( arg_chapter_begin );
        } else {
            s_quoteData.setChapterEnd( arg_chapter_end );
        }

        log_debug( "arg_sentence_end: " << arg_sentence_end );
        if ( arg_sentence_end == 0 ) {
            s_quoteData.setSentenceEnd( arg_sentence_begin );
        } else {
            s_quoteData.setSentenceEnd( arg_sentence_end );
        }

        log_debug( "arg_quote_text: " << arg_quote_text );
        s_quoteData.setQuoteText( arg_quote_text );

        log_debug( "arg_keywords: " << arg_keywords );
        s_quoteData.setKeywords( arg_keywords );

        log_debug( "arg_note: " << arg_note );
        s_quoteData.setNote( arg_note );

        log_debug( "arg_is_private_data: " << arg_is_private_data );
        s_quoteData.setIsPrivateData( arg_is_private_data );
        log_debug( "owner id: " << userSession.getUserID() );
        s_quoteData.setOwnerID( userSession.getUserID() );

        quoteManager.saveAsNew(s_quoteData);
        s_feedback = "Der Vers wurde gespeichert!";
    } else {
        log_debug( "userSession.getUserID(): " << userSession.getUserID() );
        EditionManager editionManager;
        s_editionList =  editionManager.getAllEditions( userSession.getUserID() );

    }
    return DECLINED;
}



