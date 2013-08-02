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
#include "models/Quote.h"
#include "models/QuoteRegister.h"


log_define("component.KeywordDetailController")

class KeywordDetailController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};



static tnt::ComponentFactoryImpl<KeywordDetailController> factory("KeywordDetailController");

unsigned KeywordDetailController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );
    TNT_SESSION_SHARED_VAR( std::vector<Quote>,       s_quoteList, () );
    TNT_SESSION_SHARED_VAR( bool,                     s_isLogin, () );
    TNT_SESSION_SHARED_VAR( std::string,              s_keyword, () );


    // define the query parameters
    std::string  arg_keyword =
        qparam.arg<std::string>("arg_keyword");
    s_keyword = arg_keyword;
        
    log_debug( "arg_keyword: " << arg_keyword );
    
    s_isLogin = false;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        log_debug( "Nicht eingelogt" );
        s_quoteList = QuoteRegister::getAllPubQuoteOfKeyword( arg_keyword );
    } else {
        log_debug( "Eingelogt" );
        s_isLogin = true;
        s_quoteList = QuoteRegister::getAllQuoteOfKeyword(
            arg_keyword,
            userSession.getUserID() );
    };        
        

    return DECLINED;
}


