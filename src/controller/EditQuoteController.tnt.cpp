<#
Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or later
version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
#>


<%pre>
    #include "manager/EditionManager.h"
    #include "manager/QuoteManager.h"
    #include "models/WebACL.h"
    #include "models/UserSession.h"
    #include "models/Edition.h"
    #include "models/Quote.h"
    #include "models/QuoteRegister.h"
    #include "manager/BibleManager.h"
    #include <iostream>

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    // define the query parameters
    unsigned long  quote_id = 0;
    unsigned long  edition_id = 0;
    std::string book_title = "";
    unsigned    chapter_begin = 0;
    unsigned    sentence_begin = 0;
    unsigned    chapter_end = 0;
    unsigned    sentence_end = 0;
    std::string quote_text = "";
    std::string keywords = "";
    std::string note = "";
    std::string is_private_data = "false";
    bool update_button;
    bool rest_button;
    bool look_up_button;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>


<%session>
    unsigned long session_quote_id;
    std::string bibleserverComURL;
</%session>

<%cpp>
    std::vector<Edition> editionList;
    std::string feedback = "";
    Edition editionData;
    Quote quoteData;
    BibleManager bibleManager;

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };

    std::string userName  = userSession.getUserName();
    DEBUG "quote_id: " << quote_id << std::endl;
    DEBUG "session_quote_id: " << session_quote_id << std::endl;

    EditionManager editionManager;
    editionList = editionManager.getAllEditions( userSession.getUserID() );

    if ( quote_id > 0 ) {
        session_quote_id = quote_id;
        quoteData = QuoteRegister::getQuoteWithID( quote_id );
    }


    if ( look_up_button ) {
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
        quoteData.setIsPrivateData(is_private_data == "true" );
        DEBUG std::endl;
        DEBUG "quoteData.getBibleserverComURL(): " << bibleManager.getBibleserverComURL(quoteData) << std::endl;
        DEBUG std::endl;
        bibleserverComURL = bibleManager.getBibleserverComURL(quoteData);
        DEBUG "bibleserverComURL: " << bibleserverComURL << std::endl;
    }


    DEBUG "create_button: " << update_button << std::endl;
    // is button "create" kicked?
    if ( update_button ) {

        DEBUG "session_quote_id" <<  session_quote_id << std::endl;
        quoteData.setID( session_quote_id );

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
        if ( is_private_data == "false" ) {
            quoteData.setIsPrivateData( false );
        } else {
            quoteData.setIsPrivateData( true );
        }

        DEBUG "owner id: " << userSession.getUserID() << std::endl;
        quoteData.setOwnerID( userSession.getUserID() );

        QuoteManager quoteManager;
        quoteManager.update(quoteData);
        feedback = "Der Vers wurde gespeichert!";
    }

    if ( rest_button ) {
        editionList =  editionManager.getAllEditions( userSession.getUserID() );
        quoteData = QuoteRegister::getQuoteWithID( session_quote_id );
    }

</%cpp>
