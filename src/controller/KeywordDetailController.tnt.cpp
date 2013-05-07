<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"
    #include "models/Quote.h"
    #include "models/QuoteRegister.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
string keyword = "";
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>
    DEBUG "keyword: " << keyword << endl;
    bool isLogin = false;
    std::vector<Quote> quoteList;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        quoteList = QuoteRegister::getAllPubQuoteOfKeyword( keyword );
    } else {
        DEBUG "Eingelogt" << std::endl;
        isLogin = true;
        quoteList = QuoteRegister::getAllQuoteOfKeyword(
            keyword,
            userSession.getUserID() );
    };

</%cpp>
