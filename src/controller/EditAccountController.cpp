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

#include "models/WebACL.h"
#include "models/UserSession.h"
#include "models/Quote.h"
#include "models/QuoteRegister.h"
#include "models/OString.h"
#include <iostream>
#include <cxxtools/log.h>

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
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );

    TNT_REQUEST_SHARED_VAR( std::string,              s_affirmation, () );
    TNT_REQUEST_SHARED_VAR( std::vector<AccountData>, s_accountList, () );
    TNT_REQUEST_SHARED_VAR( AccountData,              s_accountData, () );
    TNT_REQUEST_SHARED_VAR( std::vector<std::string>, s_userRolls, () );
    TNT_REQUEST_SHARED_VAR( std::vector<std::string>, s_allRolls, () );
    TNT_REQUEST_SHARED_VAR( bool,                     s_isEditAccount, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );


    // ACL Check
    if ( userSession.isInRole ( "admin" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };


    // URL arguments
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
    unsigned long arg_update_account_id =
        qparam.arg<unsigned long>("arg_update_account_id");
    bool arg_update_account_button =
        qparam.arg<bool>("arg_update_account_button");


    unsigned long arg_edit_account_id =
        qparam.arg<unsigned long>("arg_edit_account_id");
    bool arg_edit_account_button =
        qparam.arg<bool>("arg_edit_account_button");
    s_isEditAccount = arg_edit_account_button;

    unsigned long arg_delete_account_id =
        qparam.arg<unsigned long>("arg_delete_account_id");
    bool arg_delete_account_button =
        qparam.arg<bool>("arg_delete_account_button");

    unsigned long arg_affirmation_delete_account_id =
        qparam.arg<unsigned long>("arg_affirmation_delete_account_id");
    bool arg_affirmation_delete_button =
        qparam.arg<bool>("arg_affirmation_delete_button");


    s_accountList = WebACL::getAllAccounts();
    log_debug( "s_accountList.size(): " << s_accountList.size()  );

    // if a account selected for editing?
    log_debug( "arg_edit_account_id: " << arg_edit_account_id );
    if ( arg_edit_account_button ) {
        s_affirmation = "";
        s_feedback = "";
        s_accountData =  WebACL::getAccountsWithID ( arg_edit_account_id );
        log_debug( "s_accountData.getLogin_name(): " <<
            s_accountData.getLogin_name()  );
        log_debug( "s_accountData.getID(): " <<
            s_accountData.getID () );
        s_userRolls = WebACL::getRoll ( s_accountData.getLogin_name() );
        s_allRolls = WebACL::getAllRolls();
        log_debug( "s_accountData.getAccount_disable(): " <<
            s_accountData.getAccount_disable() );

    }

    // is button account data update pushed?
    if ( arg_update_account_button ) {
        s_affirmation = "";
        s_feedback = "";
        log_debug( "Speichern" );
        log_debug( "arg_update_account_id: " << arg_update_account_id );
        s_accountData.setID( arg_update_account_id );
        log_debug( "arg_login_name: " << arg_login_name );
        s_accountData.setLogin_name( arg_login_name );
        log_debug( "arg_name: " << arg_name );
        s_accountData.setReal_name( arg_name );
        log_debug( "arg_mail: " << arg_mail );
        s_accountData.setEmail( arg_mail );
        log_debug( "arg_is_inactive: " << arg_is_inactive );
        s_accountData.setAccount_disable( arg_is_inactive );

        log_debug( "args_userroles.size(): " << args_userroles.size() );
        WebACL::reSetUserRolls( arg_update_account_id, args_userroles);
        s_accountData.saveUpdate();

        // check if new password set.
        if (arg_password_a != "" ) {
            log_debug( "arg_password_a" << arg_password_a );
            // check equal of new password.
            if ( arg_password_a != arg_password_b ) {
                s_feedback = "Das Passwort ist nicht gleich!";
            } else {
                // check is password empty.
                s_accountData.setNewPassword( arg_password_a );
                arg_update_account_id = 0;
                s_feedback = "Die Daten wurden gespeichert und das Passwort neu gesetzt!";
            };
        } else {
            arg_update_account_id = 0;
            s_feedback = "Die Daten wurden gespeichert!";
        };
        s_accountList = WebACL::getAllAccounts();
    }

    // is button delete account pushed?
    if ( arg_delete_account_button ) {
        s_affirmation = "";
        s_feedback = "";
        s_accountData =  WebACL::getAccountsWithID ( arg_delete_account_id );
        log_debug( "s_accountData.getLogin_name(): " <<
            s_accountData.getLogin_name() );
        s_affirmation = "Account \""+ s_accountData.getLogin_name() +" (ID " + \
            cxxtools::convert<std::string>( arg_delete_account_id ) \
            + ")\" und allen zugehörigen Daten wirklich löschen?";

    }

    // if delete affirmation clicked.
    if ( arg_affirmation_delete_button ) {
        s_affirmation = "";
        s_feedback = "";
        log_debug( "will löschen: " << arg_affirmation_delete_account_id );
        s_accountData.setID( arg_affirmation_delete_account_id );
        s_accountData.deleteAllData();
        s_feedback = "Der Account mit der Id " + \
            cxxtools::convert<std::string>( arg_affirmation_delete_account_id ) \
            + " wurde gelöscht!";
        s_accountList = WebACL::getAllAccounts();
    }
    return DECLINED;
}
