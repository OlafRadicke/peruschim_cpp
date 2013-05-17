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
    std::string modified_publishername;
    std::string modified_releasenumber;
    std::string modified_releasedate;
    std::string modified_releaseplace;

    std::string save_modified;
    std::string delete_edition_id;
    std::string new_edition_title;
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

    // edit action
    if ( edit_edition_id != "" ) {
        edition_title = EditionManager::getEditionByID( edit_edition_id ).getName() ;
        editionData = EditionManager::getEditionByID( edit_edition_id ) ;
        session_edition_id = edit_edition_id;
    }

    // save modifications action
    if ( save_modified != "" ) {

        editionData.setID( session_edition_id );
        editionData.setName( modified_title );
        editionData.setOwnerID( userSession.getUserID() );
        editionData.setPublisherName( modified_publishername );
        editionData.setReleaseDate( modified_releasedate );
        editionData.setReleaseNumber( modified_releasenumber );
        editionData.setReleasePlace( modified_releaseplace );

        editionData.saveUpdate();

        feedback = "Die Änderungen  wurde gespeichert!";
    }

    // deleting action
    if ( delete_edition_id != "" ) {
        DEBUG "delete_edition_id: " << delete_edition_id << endl;
        int useCount = EditionManager::isEditionInUse( delete_edition_id );
        if ( useCount > 0 ) {
            feedback = "Die Ausgabe wird noch von anderen Einträgen verwendet \
                und kann deshalb nicht gelöscht werden!";
        } else {
            EditionManager::deleteEditionByID( delete_edition_id );
            feedback = "Die Ausgabe wurde gelöscht!";
        }
    }

    // create new edition action
    if ( new_edition == "pushed" ) {
        DEBUG "new_edition: " << new_edition << endl;

        editionData.setName( new_edition_title );
        editionData.setOwnerID( userSession.getUserID() );
        editionData.saveAsNew();

    }

    editionList =  EditionManager::getAllEditions( userSession.getUserID() );

</%cpp>
