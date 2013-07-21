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



# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<

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

    // Global variables
    TNT_SESSION_GLOBAL_VAR( UserSession,              userSession, () );
    TNT_SESSION_GLOBAL_VAR( std::string,              g_feedback, () );
    TNT_SESSION_GLOBAL_VAR( unsigned long,            g_session_account_id, () );
    TNT_SESSION_GLOBAL_VAR( std::string,              g_affirmation, () );
    TNT_SESSION_GLOBAL_VAR( std::vector<AccountData>, g_accountList, () );
    TNT_SESSION_GLOBAL_VAR( AccountData,              g_accountData, () );
    TNT_SESSION_GLOBAL_VAR( std::vector<std::string>, g_userRolls, () );
    TNT_SESSION_GLOBAL_VAR( std::vector<std::string>, g_allRolls, () );
    TNT_SESSION_SHARED_VAR( bool,                     s_isEditAccount, () );

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


    g_accountList = WebACL::getAllAccounts();
    log_debug( "g_accountList.size(): " << g_accountList.size()  );

    // if a account selected for editing?
    log_debug( "arg_edit_account_id: " << arg_edit_account_id );
    if ( arg_edit_account_button ) {
        g_affirmation = "";
        g_feedback = "";
        g_accountData =  WebACL::getAccountsWithID ( arg_edit_account_id );
        log_debug( "g_accountData.getLogin_name(): " <<
            g_accountData.getLogin_name()  );
        g_userRolls = WebACL::getRoll ( g_accountData.getLogin_name() );
        g_allRolls = WebACL::getAllRolls();
        g_session_account_id = arg_edit_account_id;
        log_debug( "g_accountData.getAccount_disable(): " <<
            g_accountData.getAccount_disable() );

    }

    // is button account data update pushed?
    if ( arg_update_account_button ) {
        g_affirmation = "";
        g_feedback = "";
        log_debug( "Speichern" );
        log_debug( "g_session_account_id: " << g_session_account_id );
        g_accountData.setID( g_session_account_id );
        log_debug( "arg_login_name: " << arg_login_name );
        g_accountData.setLogin_name( arg_login_name );
        log_debug( "arg_name: " << arg_name );
        g_accountData.setReal_name( arg_name );
        log_debug( "arg_mail: " << arg_mail );
        g_accountData.setEmail( arg_mail );
        log_debug( "arg_is_inactive: " << arg_is_inactive );
        g_accountData.setAccount_disable( arg_is_inactive );

        log_debug( "args_userroles.size(): " << args_userroles.size() );
        WebACL::reSetUserRolls( g_session_account_id, args_userroles);
        g_accountData.saveUpdate();

        // check if new password set.
        if (arg_password_a != "" ) {
            log_debug( "arg_password_a" << arg_password_a );
            // check equal of new password.
            if ( arg_password_a != arg_password_b ) {
                g_feedback = "Das Passwort ist nicht gleich!";
            } else {
                // check is password empty.
                g_accountData.setNewPassword( arg_password_a );
                g_session_account_id = 0;
                g_feedback = "Die Daten wurden gespeichert und das Passwort neu gesetzt!";
            };
        } else {
            g_session_account_id = 0;
            g_feedback = "Die Daten wurden gespeichert!";
        };
        g_accountList = WebACL::getAllAccounts();
    }

    // is button delete account pushed?
    if ( arg_delete_account_button ) {
        g_affirmation = "";
        g_feedback = "";
        g_session_account_id = arg_delete_account_id;
        g_accountData =  WebACL::getAccountsWithID ( g_session_account_id );
        log_debug( "g_accountData.getLogin_name(): " <<
            g_accountData.getLogin_name() );
        g_affirmation = "Account \""+ g_accountData.getLogin_name() +" (ID " + \
            cxxtools::convert<std::string>( g_session_account_id ) \
            + ")\" und allen zugehörigen Daten wirklich löschen?";

    }

    // if delete affirmation clicked.
    if ( arg_affirmation_delete_button ) {
        g_affirmation = "";
        g_feedback = "";
        log_debug( "will löschen: " << arg_affirmation_delete_account_id );
        g_accountData.setID( arg_affirmation_delete_account_id );
        g_accountData.deleteAllData();
        g_feedback = "Der Account mit der Id " + \
            cxxtools::convert<std::string>( arg_affirmation_delete_account_id ) \
            + " wurde gelöscht!";
        g_accountList = WebACL::getAllAccounts();
    }
    return DECLINED;
}
