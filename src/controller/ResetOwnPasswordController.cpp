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


log_define("component.ResetOwnPasswordController")

class ResetOwnPasswordController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};



static tnt::ComponentFactoryImpl<ResetOwnPasswordController> factory("ResetOwnPasswordController");

unsigned ResetOwnPasswordController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );

    s_feedback = "Test";
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    // define the query parameters
    std::string  arg_password_a =
        qparam.arg<std::string>("arg_password_a");
    std::string  arg_password_b =
        qparam.arg<std::string>("arg_password_b");
    bool arg_update_account_button =
        qparam.arg<bool>("arg_update_account_button");


    // is button account data update pushed?
    if ( arg_update_account_button ) {
        s_feedback = "";

        // check if new password set.
        if ( arg_password_a != "" ) {
            log_debug( "password_a" << arg_password_a );
            // check equal of new password.
            if ( arg_password_a != arg_password_b ) {
                log_debug( "Das Passwort ist nicht gleich!" );
                s_feedback = "Das Passwort ist nicht gleich!";
            } else {
                AccountData accountData;
                accountData.setID( userSession.getUserID() );
                accountData.setNewPassword( arg_password_a );
                log_debug( "Die Daten wurden gespeichert und das Passwort neu gesetzt!" );
                s_feedback = "Die Daten wurden gespeichert und das Passwort neu gesetzt!";
            };
        } else {
            log_debug( "Es wurde kein neues Passwort gesetzt" );
            s_feedback = "Es wurde kein neues Passwort gesetzt";
        };
    }
    log_debug( "CHECK s_feedback:" << s_feedback);
    return DECLINED;
}


