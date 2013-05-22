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
