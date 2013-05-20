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



