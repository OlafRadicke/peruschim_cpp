<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"
    #include "models/KeywordRegister.h"
    #include "models/Quote.h"
    #include "models/QuoteRegister.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
string user_view;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>
    vector<KeywordCount> keywordTitlesCounts;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        keywordTitlesCounts =
            KeywordRegister::getAllPubKeywordTitleAndCound();
    } else {
        DEBUG "Eingelogt" << std::endl;
        DEBUG "user_view: " << user_view << endl;
        if ( user_view == "privateitems" && user_view != "") {
            DEBUG "PRIVATEITEMS: " << PRIVATEITEMS << std::endl;
            userSession.setItemViewMode ( PRIVATEITEMS );
        } else {
            // "allitems"
            DEBUG "ALLITEMS: " << ALLITEMS << std::endl;
            userSession.setItemViewMode( ALLITEMS );
        }
        if (  userSession.getItemViewMode() == PRIVATEITEMS ) {
            keywordTitlesCounts =
                KeywordRegister::getOwnKeywordTitleAndCound( userSession.getUserID( ) );
        } else {
            keywordTitlesCounts =
                KeywordRegister::getAllKeywordTitleAndCound( userSession.getUserID( ) );
        }
    };


</%cpp>
