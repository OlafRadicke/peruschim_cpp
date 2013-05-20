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
    std::string login_name;
    std::string name;
    std::string mail;
    std::string password_a;
    std::string password_b;
    bool is_inactive;
    std::string button_update_account;

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

    // if a account selected for editing?
    if ( edit_account_id != "") {
        accountData =  WebACL::getAccountsWithID ( edit_account_id );
        session_account_id = edit_account_id;
    }

    // is button account data update pushed?
    if ( button_update_account == "Speichern" ) {
        DEBUG "Speichern" << endl;
        DEBUG "session_account_id: " << session_account_id << endl;
        accountData.setID( session_account_id );
        DEBUG "login_name: " << login_name << endl;
        accountData.setLogin_name( login_name );
        DEBUG "name: " << name << endl;
        accountData.setReal_name( name );
        DEBUG "mail: " << mail << endl;
        accountData.setEmail( mail );
        DEBUG "is_inactive: " << is_inactive << endl;
        accountData.setAccount_disable( is_inactive );
        accountData.saveUpdate();

        // check if new password set.
        if (password_a != "" ) {
            DEBUG "password_a" << password_a << endl;
            // check equal of new password.
            if ( password_a != password_b ) {
                feedback = "Das Passwort ist nicht gleich!";
            } else {
                // check is password empty.
                accountData.setNewPassword( password_a );
            };
        };

    }
</%cpp>



