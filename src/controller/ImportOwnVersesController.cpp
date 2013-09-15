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


#include <manager/QuoteRegister.h>
#include <manager/WebACL.h>
#include <models/UserSession.h>
#include <models/Quote.h>


log_define("component.ImportOwnVersesController")

class ImportOwnVersesController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};



static tnt::ComponentFactoryImpl<ImportOwnVersesController> factory("ImportOwnVersesController");

unsigned ImportOwnVersesController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );

    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );
    TNT_REQUEST_SHARED_VAR( bool,                     s_clearOldVerses, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_jasonText, () );


    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    // define the query parameters
    std::string  arg_jason_text =
        qparam.arg<std::string>("arg_jason_text");
    bool arg_clear_old_verses =
        qparam.arg<bool>("arg_clear_old_verses");
    bool arg_import_button =
        qparam.arg<bool>("arg_import_button");
    bool arg_affirmation_clear_old_button =
        qparam.arg<bool>("arg_affirmation_clear_old_button");

    s_jasonText = arg_jason_text;
    s_clearOldVerses = arg_clear_old_verses;

    // is button "Importieren" kicked?
    if ( arg_import_button ) {
        log_debug( "arg_jason_text: " << arg_jason_text );
        if ( ! arg_clear_old_verses ) {
            log_debug( "arg_clear_old_verses: " << arg_clear_old_verses );
            QuoteRegister::jsonImport( arg_jason_text, userSession.getUserID() );
            s_feedback = "Der Import ist abgeschloßen.";
        }

    }
    // is button "Importieren" kicked?
    if ( arg_affirmation_clear_old_button ) {
            log_debug( "arg_clear_old_verses: " << arg_clear_old_verses );
            s_feedback = "Die alten Verse wurden gelöscht";
            QuoteRegister::deleteAllQuoteOfUser( userSession.getUserID() );
            QuoteRegister::jsonImport( arg_jason_text, userSession.getUserID() );
            s_feedback += " und der Import erfogrich eingespielt.";
            s_clearOldVerses = false;
    }

    return DECLINED;
}
