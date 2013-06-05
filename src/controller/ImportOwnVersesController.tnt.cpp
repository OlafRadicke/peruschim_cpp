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
    #include "models/QuoteRegister.h"
    #include "models/Quote.h"

    # define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%args>
    std::string feedback;
    std::string jason_text;
    std::string clear_old_verses;
    std::string import_button;
    std::string affirmation_clear_old;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };



    // is button "Importieren" kicked?
    if ( import_button == "pushed" ) {
        DEBUG "jason_text: " << jason_text << std::endl;
        if ( clear_old_verses != "true" ) {
            DEBUG "clear_old_verses: " << clear_old_verses << std::endl;
            QuoteRegister::jsonImport( jason_text, userSession.getUserID() );
            feedback = "Der Import ist abgeschloßen.";
            clear_old_verses = "";
        }
    }
    // is button "Importieren" kicked?
    if ( affirmation_clear_old == "pushed" ) {
            DEBUG "clear_old_verses: " << clear_old_verses << std::endl;
            feedback = "Die alten Verse wurden gelöscht";
            QuoteRegister::deleteAllQuoteOfUser( userSession.getUserID() );
            QuoteRegister::jsonImport( jason_text, userSession.getUserID() );
            feedback += " und der Import erfogrich eingespielt.";
            clear_old_verses = "";
    }




</%cpp>
