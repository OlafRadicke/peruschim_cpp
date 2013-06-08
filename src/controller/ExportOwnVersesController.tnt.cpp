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