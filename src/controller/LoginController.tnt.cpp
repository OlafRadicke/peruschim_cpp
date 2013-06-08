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
    #include "../models/WebACL.h"
    #include "../models/UserSession.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%args>
    std::string name = "";
    std::string password = "";
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>
    DEBUG endl;
    DEBUG endl;
    if ( WebACL::authUser ( name, password ) == true ) {
        DEBUG endl;
        userSession.setUserName ( name );
        userSession.addRoll (  WebACL::getRoll ( name ) );
        return reply.redirect ( "/home" );
    } else {
        DEBUG endl;
        // pass
    };
</%cpp>
