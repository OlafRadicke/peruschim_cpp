/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or later
* version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "models/WebACL.h"
#include "models/UserSession.h"
#include "models/Edition.h"
#include "manager/EditionManager.h"
#include <iostream>
#include <cxxtools/log.h>
#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

log_define("component.EditEditionsController")

class EditEditionsController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<EditEditionsController> factory("component.EditEditionsController");

unsigned EditEditionsController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // Shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );

    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );
    TNT_REQUEST_SHARED_VAR( std::vector<Edition>,     s_editionList, () );
    TNT_REQUEST_SHARED_VAR( bool,                     s_isEditionEdit, () );
    TNT_REQUEST_SHARED_VAR( unsigned long,            s_editionID, () );

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    log_debug( "pass" );

    // URL arguments
    // create new edition
    std::string arg_new_edition_title =
        qparam.arg<std::string>("arg_new_edition_title");
    bool arg_new_edition =
        qparam.arg<bool>("arg_new_edition_button");

    // save modified edition
    std::string arg_modified_title =
        qparam.arg<std::string>("arg_modified_title");
    std::string arg_modified_publishername =
        qparam.arg<std::string>("arg_modified_publishername");
    std::string arg_modified_releasenumber =
        qparam.arg<std::string>("arg_modified_releasenumber");
    std::string arg_modified_releasedate =
        qparam.arg<std::string>("arg_modified_releasedate");
    std::string arg_modified_releaseplace =
        qparam.arg<std::string>("arg_modified_releaseplace");
    long unsigned int arg_modified_id =
        qparam.arg<long unsigned int>("arg_modified_id");
    bool arg_save_modified_button =
        qparam.arg<bool>("arg_save_modified_button");

    // open edition modifieding
    long unsigned int arg_edit_edition_id =
        qparam.arg<long unsigned int>("arg_edit_edition_id");
    bool arg_edition_edition_button =
        qparam.arg<bool>("arg_edition_edition_button");

    // delete edition
    long unsigned int arg_delete_edition_id =
        qparam.arg<long unsigned int>("arg_delete_edition_id");
    bool arg_delete_edition_button =
        qparam.arg<bool>("arg_delete_edition_button");

    log_debug( "arg_edition_edition_button: " << arg_edition_edition_button );
    s_isEditionEdit = arg_edition_edition_button;
    if ( s_isEditionEdit ) {
        log_debug( "arg_edit_edition_id: " << arg_edit_edition_id );
        s_editionID = arg_edit_edition_id;
    }

    if ( arg_delete_edition_button ) {
        s_editionID = arg_delete_edition_id;
    }

    // edit action
    EditionManager editionManager;
    if ( s_isEditionEdit ) {
//         pass;
    };
    log_debug("pass" );

    // save modifications action
    if ( arg_save_modified_button ) {
        Edition editionData;

        editionData.setID( arg_modified_id );
        editionData.setName( arg_modified_title );
        editionData.setOwnerID( userSession.getUserID() );
        editionData.setPublisherName( arg_modified_publishername );
        editionData.setReleaseDate( arg_modified_releasedate );
        editionData.setReleaseNumber( arg_modified_releasenumber );
        editionData.setReleasePlace( arg_modified_releaseplace );

        editionManager.saveUpdate(editionData);

        s_feedback = "Die Änderungen wurden gespeichert!";
    }

    // deleting action
    if ( arg_delete_edition_button ) {
        log_debug( "arg_delete_edition_id: " << arg_delete_edition_id );
        int useCount = editionManager.isEditionInUse( arg_delete_edition_id );
        if ( useCount > 0 ) {
            s_feedback = "Die Ausgabe wird noch von anderen Einträgen verwendet \
                und kann deshalb nicht gelöscht werden!";
        } else {
            editionManager.deleteEditionByID( arg_delete_edition_id );
            s_feedback = "Die Ausgabe wurde gelöscht.";
        }
    }

    // create new edition action
    if ( arg_new_edition ) {
        log_debug( "arg_new_edition: " << arg_new_edition );
        Edition editionData;

        editionData.setName( arg_new_edition_title );
        editionData.setOwnerID( userSession.getUserID() );
        editionManager.saveAsNew(editionData);

    }

    s_editionList =  editionManager.getAllEditions( userSession.getUserID() );

    return DECLINED;
}

