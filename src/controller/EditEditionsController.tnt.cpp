<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"
    #include "models/Edition.h"
    #include "models/EditionManager.h"

    # define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
    # define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
</%pre>

<%config>
</%config>

<%args>
    std::string edit_edition_id;
    std::string modified_title;
    std::string save_modified;
    std::string delete_edition_id;
    std::string new_edition;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%session>
    std::string session_edition_id;
</%session>

<%cpp>
    std::vector<Edition> editionList;
    std::string feedback = "";
    Edition editionData;
    std::string edition_title = "";

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    DEBUG "session_edition_id: " << session_edition_id << endl;


    if ( edit_edition_id != "" ) {
        DEBUG "edit_edition_id: " << edit_edition_id << endl;
        edition_title = EditionManager::getEditionByID( edit_edition_id ).getName() ;
        editionData = EditionManager::getEditionByID( edit_edition_id ) ;
        session_edition_id = edit_edition_id;
        feedback = "Eintrag ändern...";
    }

    if ( save_modified != "" ) {
        DEBUG "save_modified: " << save_modified << endl;
        DEBUG "modified_title: " << modified_title << endl;
        DEBUG "session_edition_id: " <<   session_edition_id;

        feedback = "Die Änderungen  wurde gespeichert!";
    }

    if ( delete_edition_id != "" ) {
        DEBUG "delete_edition_id: " << delete_edition_id << endl;

        feedback = "Die Ausgabe wurde gelöscht!";
        feedback = "Die Ausgabe wird noch von anderen Einträgen verwendet und \
            kann deshalb nicht gelöscht werden!";
    }

    if ( new_edition == "pushed" ) {
        DEBUG "new_edition: " << new_edition << endl;
        feedback = "Der Verse wurde gespeichert!";
    }

    editionList =  EditionManager::getAllEditions( userSession.getUserID() );

</%cpp>
