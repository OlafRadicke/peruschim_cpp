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
            QuoteRegister::jsonImport( jason_text );
            feedback = "Der Import ist abgeschloßen.";
        }
    }
    // is button "Importieren" kicked?
    if ( affirmation_clear_old == "pushed" ) {
            DEBUG "clear_old_verses: " << clear_old_verses << std::endl;
            feedback = "Die alten Verse wurden gelöscht";
            QuoteRegister::deleteAllQuoteOfUser( userSession.getUserID() );
            QuoteRegister::jsonImport( jason_text );
            feedback += " und der Import erfogrich eingespielt.";
    }




</%cpp>
