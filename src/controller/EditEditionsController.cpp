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



static tnt::ComponentFactoryImpl<EditEditionsController> factory("EditEditionsController");

unsigned EditEditionsController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{

    // Global variables
    TNT_SESSION_GLOBAL_VAR( UserSession,              userSession, () );
    TNT_SESSION_GLOBAL_VAR( std::string,              g_feedback, () );
    TNT_SESSION_GLOBAL_VAR( Edition,                  g_editionData, () );
    TNT_SESSION_GLOBAL_VAR( std::string,              g_edition_title, () );
    TNT_SESSION_GLOBAL_VAR( std::vector<Edition>,     g_editionList, () );


    // URL arguments
    std::string arg_new_edition_title =
        qparam.arg<std::string>("arg_new_edition_title");
    long unsigned int arg_edit_edition_id =
        qparam.arg<long unsigned int>("arg_edit_edition_id");
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
    std::string arg_save_modified =
        qparam.arg<std::string>("arg_save_modified");
    long unsigned int arg_delete_edition_id =
        qparam.arg<long unsigned int>("arg_delete_edition_id");
    bool arg_new_edition =
        qparam.arg<bool>("arg_new_edition");
        
    long unsigned int session_edition_id = 0;

    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    log_debug( "pass" );

    // edit action
    EditionManager editionManager;
    if ( arg_edit_edition_id > 0 ) {
        g_edition_title = editionManager.getEditionByID( arg_edit_edition_id )
            .getName() ;
        g_editionData = editionManager.getEditionByID( arg_edit_edition_id ) ;
        session_edition_id = arg_edit_edition_id;
    };
    log_debug("pass" );

    // save modifications action
    if ( arg_save_modified != "" ) {

        g_editionData.setID( session_edition_id );
        g_editionData.setName( arg_modified_title );
        g_editionData.setOwnerID( userSession.getUserID() );
        g_editionData.setPublisherName( arg_modified_publishername );
        g_editionData.setReleaseDate( arg_modified_releasedate );
        g_editionData.setReleaseNumber( arg_modified_releasenumber );
        g_editionData.setReleasePlace( arg_modified_releaseplace );

        editionManager.saveUpdate(g_editionData);

        g_feedback = "Die Änderungen wurden gespeichert!";
    }

    // deleting action
    if ( arg_delete_edition_id > 0 ) {
        log_debug( "arg_delete_edition_id: " << arg_delete_edition_id );
        int useCount = editionManager.isEditionInUse( arg_delete_edition_id );
        if ( useCount > 0 ) {
            g_feedback = "Die Ausgabe wird noch von anderen Einträgen verwendet \
                und kann deshalb nicht gelöscht werden!";
        } else {
            editionManager.deleteEditionByID( arg_delete_edition_id );
            g_feedback = "Die Ausgabe wurde gelöscht.";
        }
    }

    // create new edition action
    if ( arg_new_edition ) {
        log_debug( "arg_new_edition: " << arg_new_edition );

        g_editionData.setName( arg_new_edition_title );
        g_editionData.setOwnerID( userSession.getUserID() );
        editionManager.saveAsNew(g_editionData);

    }

    g_editionList =  editionManager.getAllEditions( userSession.getUserID() );

    return DECLINED;
}

