<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"

    # define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
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
            DEBUG "password_a" << password_a << endl;
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
