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


#include <Core/manager/KeywordRegister.h>
#include <Core/manager/QuoteRegister.h>
#include <Core/manager/WebACL.h>
#include <Core/models/UserSession.h>
#include <Core/models/Quote.h>


log_define("component.KeywordRegisterController")

class KeywordRegisterController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};



static tnt::ComponentFactoryImpl<KeywordRegisterController> factory("KeywordRegisterController");

unsigned KeywordRegisterController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );

//     TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );
    TNT_REQUEST_SHARED_VAR( vector<KeywordCount>,     s_keywordTitlesCounts, ());


    // define the query parameters
    std::string  arg_user_view =
        qparam.arg<std::string>("arg_user_view");
    bool arg_view_change_button =
        qparam.arg<bool>("arg_view_change_button");


    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        log_debug( "Nicht eingeloggt" );
        s_keywordTitlesCounts =
            KeywordRegister::getAllPubKeywordTitleAndCound();
    } else {
        log_debug( "Eingeloggt" );
        log_debug( "arg_user_view: " << arg_user_view );
        if ( arg_view_change_button ) {
            if ( arg_user_view == "privateitems" ) {
                log_debug( "PRIVATEITEMS: " << PRIVATEITEMS );
                userSession.setItemViewMode ( PRIVATEITEMS );
            } else {
                // "allitems"
                log_debug( "ALLITEMS: " << ALLITEMS );
                userSession.setItemViewMode( ALLITEMS );
            }
        }
        if (  userSession.getItemViewMode() == PRIVATEITEMS ) {
            s_keywordTitlesCounts =
                KeywordRegister::getOwnKeywordTitleAndCound( userSession.getUserID( ) );
        } else {
            s_keywordTitlesCounts =
                KeywordRegister::getAllKeywordTitleAndCound( userSession.getUserID( ) );
        }
    };
    return DECLINED;
}
