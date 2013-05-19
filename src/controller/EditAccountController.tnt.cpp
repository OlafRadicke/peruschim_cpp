<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    std::string feedback;
    std::string login_name;
    std::string name;
    std::string mail;
    std::string button_update_account;
    std::string password_a;
    std::string password_b;
    std::string edit_account_id;
    std::string delete_account_id;
</%args>
<%session scope="global">
    UserSession userSession;
</%session>

<%session>
    std::string session_account_id;
</%session>

<%cpp>

    // ACL Check
    if ( userSession.isInRole ( "admin" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    std::vector<AccountData> accountList = WebACL::getAllAccounts();
    AccountData accountData;


    if ( edit_account_id != "") {
        accountData =  WebACL::getAccountsWithID ( edit_account_id );
        session_account_id = edit_account_id;
    }

    // is button account data update pushed?
    if ( button_update_account == "Speichern" ) {

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



