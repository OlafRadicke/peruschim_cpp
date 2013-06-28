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
    unsigned long edit_edition_id;
    std::string modified_title;
    std::string modified_publishername;
    std::string modified_releasenumber;
    std::string modified_releasedate;
    std::string modified_releaseplace;

    std::string save_modified;
    unsigned long  delete_edition_id;
    std::string new_edition_title;
    std::string new_edition;
</%args>

<%session scope="global">
    UserSession userSession;
</%session>

<%session>
    unsigned long session_edition_id;
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
    if ( edit_edition_id > 0 ) {
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

        feedback = "Die Änderungen wurden gespeichert!";
    }

    // deleting action
    if ( delete_edition_id > 0 ) {
        DEBUG "delete_edition_id: " << delete_edition_id << std::endl;
        int useCount = EditionManager::isEditionInUse( delete_edition_id );
        if ( useCount > 0 ) {
            feedback = "Die Ausgabe wird noch von anderen Einträgen verwendet \
                und kann deshalb nicht gelöscht werden!";
        } else {
            EditionManager::deleteEditionByID( delete_edition_id );
            feedback = "Die Ausgabe wurde gelöscht.";
        }
    }

    // create new edition action
    if ( new_edition == "pushed" ) {
        DEBUG "new_edition: " << new_edition << std::endl;

        editionData.setName( new_edition_title );
        editionData.setOwnerID( userSession.getUserID() );
        editionData.saveAsNew();

    }

    editionList =  EditionManager::getAllEditions( userSession.getUserID() );

</%cpp>
