
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


#include <Core/manager/WebACL.h>
#include <Core/models/UserSession.h>


log_define("component.SwitchToHandheldVersionController")

class SwitchToHandheldVersionController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<SwitchToHandheldVersionController> factory("SwitchToHandheldVersionController");

unsigned SwitchToHandheldVersionController::operator()
    (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );

//     TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );


    // define the query parameters
    bool  arg_okay_button =
        qparam.arg<bool>("arg_okay_button");
    bool  arg_abort_button =
        qparam.arg<bool>("arg_abort_button");

    userSession.isHandheldVersion(true);
    if ( arg_okay_button ) {
        log_debug("switsch to the handheld version");
        userSession.isHandheldVersion(true);
        return reply.redirect ( "/home" );
    }
    if ( arg_abort_button ) {
        log_debug("switsch NOT to the handheld version");
        userSession.isHandheldVersion(false);
        return reply.redirect ( "/home" );
    }


    return DECLINED;
}



