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

#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <iostream>
#include <cxxtools/log.h>

#include <Core/manager/QuoteRegister.h>
#include <Core/manager/WebACL.h>
#include <Core/models/UserSession.h>
#include <Core/models/Quote.h>
#include <Core/models/OString.h>

log_define("component.EditAccountController")

class EditAccountController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<EditAccountController> factory("EditAccountController");

unsigned EditAccountController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    // shared variables

    log_debug( __FILE__ << "request.getUrl(): " << request.getUrl() );
    log_debug( __FILE__ << "request.getPathInfo(): " << request.getPathInfo() );
    log_debug( __FILE__ << "request.getHost(): " << request.getHost() );
    log_debug( __FILE__ << "request.getVirtualHost(): " << request.getVirtualHost() );
    log_debug( __FILE__ << "request.isMethodGET(): " << request.isMethodGET() );
    log_debug( __FILE__ << "request.isMethodPOST(): " << request.isMethodPOST() );


    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );
    // the ID of account where open for open for user operations.
    TNT_SESSION_SHARED_VAR( unsigned long,            open_account_id, () );

    TNT_REQUEST_SHARED_VAR( std::string,              s_affirmation, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_affirmation_typ, () );
    TNT_REQUEST_SHARED_VAR( AccountData,              s_accountData, () );
    TNT_REQUEST_SHARED_VAR( std::vector<std::string>, s_userRolls, () );
    TNT_REQUEST_SHARED_VAR( std::vector<std::string>, s_allRolls, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );


    std::cout << __FILE__ << __LINE__ << std::endl;
    // ACL Check
    if ( userSession.isInRole ( "admin" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    std::cout << __FILE__ << __LINE__ << std::endl;


    // URL arguments
    unsigned long arg_edit_account_id =
        qparam.arg<unsigned long>("arg_edit_account_id");
    bool arg_edit_account_button =
        qparam.arg<bool>("arg_edit_account_button");

    std::string arg_login_name =
        qparam.arg<std::string>("arg_login_name");
    std::string arg_name =
        qparam.arg<std::string>("arg_name");
    std::string arg_mail =
        qparam.arg<std::string>("arg_mail");
    std::string arg_password_a =
        qparam.arg<std::string>("arg_password_a");
    std::string arg_password_b =
        qparam.arg<std::string>("arg_password_b");
    std::vector<std::string>  args_userroles =
        qparam.args<std::string>("args_userroles");
    bool arg_is_inactive =
        qparam.arg<bool>("arg_is_inactive");
    bool arg_revoke_trust_button =
        qparam.arg<bool>("arg_revoke_trust_button");
    bool arg_update_account_button =
        qparam.arg<bool>("arg_update_account_button");


    std::string arg_affirmation_typ =
        qparam.arg<std::string>("arg_affirmation_typ");
    bool arg_affirmation_ok_button =
        qparam.arg<bool>("arg_affirmation_ok_button");


    // if a account first time selected for editing?
    if ( arg_edit_account_button ) {
        open_account_id = arg_edit_account_id;
        s_accountData =  WebACL::getAccountsWithID ( open_account_id );
        s_userRolls = WebACL::getRoll ( s_accountData.getLogin_name() );
        s_allRolls = WebACL::getAllRolls();

    }


    // is button account data update pushed?
    if ( arg_update_account_button ) {
        s_affirmation = "";
        s_feedback = "";
        s_accountData.setID( open_account_id );
        s_accountData.setLogin_name( arg_login_name );
        s_accountData.setReal_name( arg_name );
        s_accountData.setEmail( arg_mail );
        s_accountData.setAccount_disable( arg_is_inactive );
        WebACL::reSetUserRolls( open_account_id, args_userroles);
        s_accountData.saveUpdate();
        s_userRolls = WebACL::getRoll ( s_accountData.getLogin_name() );
        s_allRolls = WebACL::getAllRolls();

        // check if new password set.
        if (arg_password_a != "" ) {
            // check equal of new password.
            if ( arg_password_a != arg_password_b ) {
                s_feedback = "Das Passwort ist nicht gleich!";
            } else {
                // check is password empty.
                s_accountData.setNewPassword( arg_password_a );
                s_feedback = "Die Daten wurden gespeichert und das Passwort neu gesetzt!";
            };
        } else {
            s_feedback = "Die Daten wurden gespeichert!";
        };
    }

    if ( arg_revoke_trust_button ) {
        AccountData accountData(open_account_id);
        int guarantorCount = accountData.getGuarantorCount( );
        if ( guarantorCount == 0 ) {
            s_feedback = "Der Account/Benutzer besitzt kein Vertrauen was man ihm \
                entziehen könne.";
        } else {
            s_affirmation_typ = "revoke trust";
            s_affirmation = "Achtung, der Prozess ist unumkehrbar! \
                Wenn das Vertrauen der Bürgen gelöscht wird müsste jeder einzelne \
                Bürge sein Vertrauen noch ein mal aussprechen um den Zustand \
                wieder herzustellen. Das beträfe in diesem Fall " +
                cxxtools::convert<std::string>( guarantorCount ) + " Bürgen.";
        }
    }

    // if delete affirmation clicked.
    if ( arg_affirmation_typ == "revoke trust" ) {
        log_debug( __LINE__ + "start...");
        if ( arg_affirmation_ok_button ) {
            AccountData accountData;
            accountData.setID( open_account_id );
            int guarantorCount = accountData.getGuarantorCount( );
            log_debug( __LINE__ );
            std::vector<unsigned long> accountIDs =
                accountData.revokeTrust( userSession.getUserID() );
            s_feedback = "Es wurde sämtliches Vertrauen entfernt. Das betraf "
                + OString::IntToStr( guarantorCount ) + " Bürgen.";
            log_debug( __LINE__ );
            if ( accountIDs.size() > 0 ){
                log_debug( __LINE__ );
                s_feedback += " Als Folge davon wurden den weiteren Benutzern \
                (zum Teil) das Vertrauen entzogen:";
                log_debug( "accountIDs.size()" << accountIDs.size() );
                for ( unsigned int i=0; i<accountIDs.size(); i++) {
                    log_debug( __LINE__ << " i:"  << i);
                    if( i > 0 )  s_feedback += ", ";
//                     s_feedback += accountIDs[i] ;
                    s_feedback += OString::IntToStr( accountIDs[i] );
//                     log_debug( __LINE__ );
                }
            }

        }
    }
    return DECLINED;
}
