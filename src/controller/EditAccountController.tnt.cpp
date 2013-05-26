<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"

    # define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    std::string login_name;
    std::string name;
    std::string mail;
    std::string password_a;
    std::string password_b;
    std::string userrolls[];
    bool is_inactive;
    std::string button_update_account;

    std::string edit_account_id;
    std::string delete_account_id;
    std::string affirmation_delete_account_id;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%session>
    std::string feedback;
    std::string session_account_id;
    std::string affirmation;
</%session>

<%cpp>

    // ACL Check
    if ( userSession.isInRole ( "admin" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    std::vector<AccountData> accountList = WebACL::getAllAccounts();
    AccountData accountData;
    std::vector<std::string> userRolls;
    std::vector<std::string> allRolls;


    // if a account selected for editing?
    DEBUG "edit_account_id: " << edit_account_id << endl;
    if ( edit_account_id != "") {
        affirmation = "";
        feedback = "";
        accountData =  WebACL::getAccountsWithID ( edit_account_id );
        std::vector<std::string> userRolls = WebACL::getRoll ( accountData.getLogin_name() );
        allRolls = WebACL::getAllRolls();
        session_account_id = edit_account_id;
        DEBUG "accountData.getAccount_disable(): " << accountData.getAccount_disable() << endl;

    }

    // is button account data update pushed?
    if ( button_update_account == "Speichern" ) {
        affirmation = "";
        feedback = "";
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

        WebACL::reSetUserRolls( session_account_id, userrolls);
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
                session_account_id = "";
                feedback = "Die Daten wurden gespeichert und das Passwort neu gesetzt!";
            };
        } else {
            session_account_id = "";
            feedback = "Die Daten wurden gespeichert!";
        };
        accountList = WebACL::getAllAccounts();
    }

    // is button delete account pushed?
    if ( delete_account_id != "" ) {
        affirmation = "";
        feedback = "";
        session_account_id = delete_account_id;
        affirmation = "Account mit ID " + session_account_id + " und allen \
             zugehörigen Daten wirklich löschen?";

    }

    // if delete affirmation clicked.
    if ( affirmation_delete_account_id != "" ) {
        affirmation = "";
        feedback = "";
        DEBUG "will löschen: " << affirmation_delete_account_id << endl;
        feedback = "Der Account mit der Id " + affirmation_delete_account_id + " wurde gelöscht!";
        accountList = WebACL::getAllAccounts();
    }

</%cpp>



