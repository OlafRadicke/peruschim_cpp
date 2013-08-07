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



#include "models/QuoteRegister.h"
#include "models/UserSession.h"

#include <cxxtools/log.h>
#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>


log_define("component.ExportOwnVersesController")

class ExportOwnVersesController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<ExportOwnVersesController> factory("ExportOwnVersesController");

unsigned ExportOwnVersesController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{

    TNT_SESSION_GLOBAL_VAR( UserSession,              userSession, ());
    
    TNT_REQUEST_GLOBAL_VAR( std::string,              s_jason_text, ());
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );

    log_debug("userSession.getUserName(): " << userSession.getUserName() );
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    s_jason_text = QuoteRegister::getJsonExport( userSession.getUserID() );

    return DECLINED;
}

