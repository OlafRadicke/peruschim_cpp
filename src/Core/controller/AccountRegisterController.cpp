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

#include <Core/manager/QuoteRegister.h>
#include <Core/manager/WebACL.h>
#include <Core/models/UserSession.h>
#include <Core/models/Quote.h>
#include <Core/models/OString.h>
#include <iostream>
#include <cxxtools/log.h>

log_define("component.AccountRegisterController")

class AccountRegisterController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<AccountRegisterController> factory("AccountRegisterController");

unsigned AccountRegisterController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{

    // shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_affirmation, () );
//     TNT_REQUEST_SHARED_VAR( AccountData,              s_accountData, () );
    TNT_REQUEST_SHARED_VAR( std::vector<AccountData>, s_accountList, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );


    // ACL Check
    if ( userSession.isInRole ( "admin" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };


    // URL arguments

//     unsigned long arg_edit_account_id =
//         qparam.arg<unsigned long>("arg_edit_account_id");
//     bool arg_edit_account_button =
//         qparam.arg<bool>("arg_edit_account_button");

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



    // is button delete account pushed?
    if ( arg_delete_account_button ) {
        s_affirmation = "";
        s_feedback = "";
        AccountData accountData =  WebACL::getAccountsWithID ( arg_delete_account_id );
        log_debug( "accountData.getLogin_name(): " <<
            accountData.getLogin_name() );
        s_affirmation = "Account \""+ accountData.getLogin_name() +" (ID " + \
            cxxtools::convert<std::string>( arg_delete_account_id ) \
            + ")\" und allen zugehörigen Daten wirklich löschen?";

    };

    // if delete affirmation clicked.
    if ( arg_affirmation_delete_button ) {
        AccountData accountData;
        s_affirmation = "";
        s_feedback = "";
        log_debug( "will löschen: " << arg_affirmation_delete_account_id );
        accountData.setID( arg_affirmation_delete_account_id );
        accountData.deleteAllData( userSession.getUserID() );
        s_feedback = "Der Account mit der Id " + \
            cxxtools::convert<std::string>( arg_affirmation_delete_account_id ) \
            + " wurde gelöscht!";
        s_accountList = WebACL::getAllAccounts();
    };
    return DECLINED;
}
