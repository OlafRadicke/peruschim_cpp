<#
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
#>

<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"

    # define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    // define the query parameters
    std::string feedback = "";
    std::string login_name = "";
    std::string name = "";
    std::string mail = "";
    std::string create;
    std::string password_a = "";
    std::string password_b = "";
</%args>
<%session scope="global">
    // define your session scope variables here
    // std::string mySessionState;
    // userSession;
    UserSession userSession;
</%session>


<%cpp>

    // ACL Check
    if ( userSession.isInRole ( "admin" ) == false ) {
        DEBUG "Nicht autorisiert!!" << std::endl;
        return reply.redirect ( "/access_denied" );
    };
    DEBUG "Autorisiert!!" << std::endl;

    // is button "create" Speichern?
    if ( create == "Speichern" ) {

        // check equal of new password.
        if ( password_a != password_b ) {
            feedback = "Das Passwort ist nicht gleich!";
        } else {
            // check is password empty.
            if ( password_b == "" ) {
                feedback = "Kein Passwort gesetzt!";
            } else {
                // chech ist account all reade exist.
                if ( WebACL::isUserExist (login_name) ) {
                    feedback = "Es existiert schon ein Account mit diesem Namen!";
                } else {
                    // create ne account...
                    try {
                        WebACL::createAccount ( login_name, password_a, name, mail, "user" );
                    } catch ( char * errstr ) {
                        ERROR "Exception raised: " << errstr << '\n';
                        feedback = "Es trat ein Problem auf: " + std::string ( errstr ) ;
                    }
                    feedback = "Der Account wurde angelegt!";
                }
            }
        };
    }
</%cpp>



