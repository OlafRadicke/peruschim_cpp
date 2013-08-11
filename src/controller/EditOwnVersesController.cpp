/*
Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or later
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include "models/WebACL.h"
#include "models/UserSession.h"
#include "models/Quote.h"
#include "models/QuoteRegister.h"
#include "models/OString.h"
#include <iostream>
#include <cxxtools/log.h>


log_define("component.EditOwnVersesController")

class EditOwnVersesController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};



static tnt::ComponentFactoryImpl<EditOwnVersesController> factory("EditOwnVersesController");

unsigned EditOwnVersesController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{

    TNT_SESSION_GLOBAL_VAR( UserSession,                  userSession, ());
    
    TNT_REQUEST_GLOBAL_VAR( std::vector<Quote>,           s_quoteList, ());
    TNT_REQUEST_GLOBAL_VAR( std::string,                   s_feedback, ());
    TNT_REQUEST_GLOBAL_VAR( std::string,       s_affirmation_question, ());
    TNT_REQUEST_GLOBAL_VAR( unsigned long,                s_quote_id, (0));

    

    unsigned long arg_quote_id =
        qparam.arg<unsigned long>("arg_quote_id");
    bool arg_delete_verse_button =
        qparam.arg<bool>("arg_delete_verse_button");
    bool arg_affirmation_delete_button =
        qparam.arg<bool>("arg_affirmation_delete_button");

    log_debug( "userSession.getUserName(): " << userSession.getUserName() );
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        log_debug( "Nicht eingeloggt" );
        return reply.redirect ( "/access_denied" );
    }
    log_debug( __LINE__ << " Eingeloggt" );
    log_debug( __LINE__ << " arg_quote_id" << arg_quote_id);
    log_debug( __LINE__ << " arg_delete_verse_button" << arg_delete_verse_button);
    log_debug( __LINE__ << " arg_affirmation_delete_button" << arg_affirmation_delete_button);

    // is button delete pushed?
    if ( arg_delete_verse_button ) {
        log_debug( "arg_delete_verse_button" );
        s_quote_id = arg_quote_id;
        Quote quoteInfo = QuoteRegister::getQuoteWithID( s_quote_id ) ;
        s_affirmation_question =
            "Bibelvers mit "+ quoteInfo.getBookTitle() + " " + \
            cxxtools::convert<std::string>( quoteInfo.getChapterBegin() ) + \
            ":" + cxxtools::convert<std::string>( quoteInfo.getSentenceBegin() ) + \
            " (ID: " + cxxtools::convert<std::string>(s_quote_id) \
            + ") wirklich löschen?";
        log_debug( "s_affirmation_question" << s_affirmation_question );
    }

    // if delete affirmation clicked.
    if ( arg_affirmation_delete_button ) {
        log_debug( "arg_affirmation_delete_button" );
        
        log_debug( "will löschen: " << arg_quote_id );
        QuoteRegister::deleteQuote(
            cxxtools::convert<unsigned long>( arg_quote_id )
        );
        s_feedback = \
            "Der Bibelverse mit der ID " + \
             cxxtools::convert<std::string>( arg_quote_id ) + \
             " wurde gelöscht!";
    }
    s_quoteList = QuoteRegister::getAllQuoteOfUser( userSession.getUserID() );

    return DECLINED;
}

