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
    #include "models/KeywordRegister.h"
    #include "models/Quote.h"
    #include "models/QuoteRegister.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
string user_view;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>
    vector<KeywordCount> keywordTitlesCounts;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        keywordTitlesCounts =
            KeywordRegister::getAllPubKeywordTitleAndCound();
    } else {
        DEBUG "Eingelogt" << std::endl;
        DEBUG "user_view: " << user_view << endl;
        if ( user_view == "privateitems" && user_view != "") {
            DEBUG "PRIVATEITEMS: " << PRIVATEITEMS << std::endl;
            userSession.setItemViewMode ( PRIVATEITEMS );
        } else {
            // "allitems"
            DEBUG "ALLITEMS: " << ALLITEMS << std::endl;
            userSession.setItemViewMode( ALLITEMS );
        }
        if (  userSession.getItemViewMode() == PRIVATEITEMS ) {
            keywordTitlesCounts =
                KeywordRegister::getOwnKeywordTitleAndCound( userSession.getUserID( ) );
        } else {
            keywordTitlesCounts =
                KeywordRegister::getAllKeywordTitleAndCound( userSession.getUserID( ) );
        }
    };


</%cpp>
