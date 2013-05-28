<%pre>
    #include "models/EditionManager.h"
    #include "models/WebACL.h"
    #include "models/UserSession.h"
    #include "models/Edition.h"
    #include "models/Quote.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    // define the query parameters
    std::string edition_id = "";
    std::string book_title = "";
    int chapter_begin = 0;
    int sentence_begin = 0;
    int chapter_end = 0;
    int sentence_end = 0;
    std::string quote_text = "";
    std::string keywords = "";
    std::string note = "";
    std::string is_private_data = "false";
    std::string save_button;
    std::string create_button;
    std::string look_up_button;
</%args>

<%session>
    std::string bibleserverComURL = "";
</%session>

<%session scope="global">
    UserSession userSession;
</%session>

<%cpp>
    std::vector<Edition> editionList;
    std::string feedback = "";
    Edition editionData;
    Quote quoteData;

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    std::string userName  = userSession.getUserName();


    DEBUG "save_button: " << save_button << std::endl;
    DEBUG "create_button: " << create_button << std::endl;
    DEBUG "look_up_button: " << look_up_button << std::endl;

    if ( look_up_button == "clicked" ) {
        DEBUG "getBibleserverComURL..." << std::endl;
        quoteData.setEditionID( edition_id );
        quoteData.setBookTitle( book_title );
        quoteData.setChapterBegin( chapter_begin );
        quoteData.setSentenceBegin( sentence_begin );
        DEBUG std::endl;
        quoteData.setChapterEnd( chapter_end );
        quoteData.setSentenceEnd( sentence_end );
        quoteData.setQuoteText( quote_text );
        DEBUG std::endl;
        quoteData.setKeywords( keywords );
        quoteData.setNote( note );
        DEBUG "is_private_data: " <<  is_private_data << std::endl;
        if ( is_private_data == "true" ) {
            quoteData.setIsPrivateData( true );
        } else {
            quoteData.setIsPrivateData( false );
        }
        DEBUG std::endl;
        DEBUG "quoteData.getBibleserverComURL(): " << quoteData.getBibleserverComURL() << std::endl;
        DEBUG std::endl;
        bibleserverComURL = quoteData.getBibleserverComURL();
        DEBUG "bibleserverComURL: " << bibleserverComURL << std::endl;
    }

    // is button "create" kicked?
    if ( create_button == "Speichern" ) {
        DEBUG "edition_id: " << edition_id << std::endl;
        quoteData.setEditionID( edition_id );

        DEBUG "book_titl: e" << book_title << std::endl;
        quoteData.setBookTitle( book_title );

        DEBUG "chapter_begin: " << chapter_begin << std::endl;
        quoteData.setChapterBegin( chapter_begin );

        DEBUG "sentence_begin: " << sentence_begin << std::endl;
        quoteData.setSentenceBegin( sentence_begin );

        DEBUG "chapter_end: " << chapter_end << std::endl;
        quoteData.setChapterEnd( chapter_end );

        DEBUG "sentence_end: " << sentence_end << std::endl;
        quoteData.setSentenceEnd( sentence_end );

        DEBUG "quote_text: " << quote_text << std::endl;
        quoteData.setQuoteText( quote_text );

        DEBUG "keywords: " << keywords << std::endl;
        quoteData.setKeywords( keywords );

        DEBUG "note: " << note << std::endl;
        quoteData.setNote( note );

        DEBUG "is_private_data: " << is_private_data << std::endl;
        if ( is_private_data == "true" ) {
            quoteData.setIsPrivateData( true );
        } else {
            quoteData.setIsPrivateData( false );
        }

        DEBUG "owner id: " << userSession.getUserID() << std::endl;
        quoteData.setOwnerID( userSession.getUserID() );

        quoteData.saveAsNew( );
        feedback = "Der Verse wurde gespeichert!";
    } else {
        editionList =  EditionManager::getAllEditions( userSession.getUserID() );

    }

</%cpp>
