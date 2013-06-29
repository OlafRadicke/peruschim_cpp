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

    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    std::string feedback;
    std::string password_a;
    std::string password_b;
    std::string button_update_account;
</%args>
<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    AccountData accountData;

    // is button account data update pushed?
    if ( button_update_account == "Speichern" ) {
        feedback = "";

        // check if new password set.
        if (password_a != "" ) {
            DEBUG "password_a" << password_a << std::endl;
            // check equal of new password.
            if ( password_a != password_b ) {
                feedback = "Das Passwort ist nicht gleich!";
            } else {
                accountData.setID( userSession.getUserID() );
                accountData.setNewPassword( password_a );
                feedback = "Die Daten wurden gespeichert und das Passwort neu gesetzt!";
            };
        } else {
            feedback = "Es wurde kein Passwort gesetzt";
        };
    }
</%cpp>
