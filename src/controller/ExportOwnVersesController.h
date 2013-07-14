/*
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
*/

#ifndef EXPORTOWNVERSESCONTROLLER_H
#define EXPORTOWNVERSESCONTROLLER_H

#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

/*
#include "models/WebACL.h"
#include "models/UserSession.h"
#include "models/Quote.h"
#include "models/QuoteRegister.h"
*/

class ExportOwnVersesController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

#endif
















<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"
    #include "models/QuoteRegister.h"
    #include "models/Quote.h"

    # define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    std::string feedback;
    std::string jason_text;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    
    jason_text = QuoteRegister::getJsonExport( userSession.getUserID() );
        
    
</%cpp>