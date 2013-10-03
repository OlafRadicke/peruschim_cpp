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


log_define("component.NewAccountController")

class NewAccountController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<NewAccountController> factory("NewAccountController");

unsigned NewAccountController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_login_name, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_real_name, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_mail, () );

    // No ACL Check. User can create a account self.

    // define the query parameters
    bool  arg_create_button =
        qparam.arg<bool>("arg_create_button");
    std::string  arg_login_name =
        qparam.arg<std::string>("arg_login_name");
    std::string  arg_real_name =
        qparam.arg<std::string>("arg_real_name");
    std::string  arg_password_a =
        qparam.arg<std::string>("arg_password_a");
    std::string  arg_password_b =
        qparam.arg<std::string>("arg_password_b");
    std::string  arg_mail =
        qparam.arg<std::string>("arg_mail");

    s_login_name = arg_login_name;
    s_real_name = arg_real_name;
    s_mail = arg_mail;

    // is button "create" Speichern?
    if ( arg_create_button ) {

        // check equal of new password.
        if ( arg_password_a != arg_password_b ) {
            s_feedback = "Das Passwort ist nicht gleich!";
        } else {
            // check is password empty.
            if ( arg_password_b == "" ) {
                s_feedback = "Kein Passwort gesetzt!";
            } else {
                // chech ist account all reade exist.
                if ( WebACL::isUserExist( arg_login_name ) ) {
                    s_feedback = "Es existiert schon ein Account mit diesem Namen!";
                } else {
                    // create ne account...
                    try {
                        WebACL::createAccount(
                            arg_login_name,
                            arg_password_a,
                            arg_real_name,
                            arg_mail,
                            "user"
                        );
                    } catch ( char * errstr ) {
                        log_error( "Exception raised: " << errstr );
                        s_feedback = "Es trat ein Problem auf: "
                            + std::string ( errstr ) ;
                    }
                    s_feedback = "Der Account wurde angelegt!";
                }
            }
        };
    }

    return DECLINED;
}




