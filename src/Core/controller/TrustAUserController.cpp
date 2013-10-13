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

#include <iostream>

#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <cxxtools/log.h>

#include <Core/manager/QuoteRegister.h>
#include <Core/manager/WebACL.h>
#include <Core/models/UserSession.h>
#include <Core/models/Quote.h>
#include <Core/models/OString.h>

log_define("component.TrustAUserController")

class TrustAUserController : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

static tnt::ComponentFactoryImpl<TrustAUserController> factory("TrustAUserController");

unsigned TrustAUserController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    log_debug( __LINE__ << "pass" );
    // shared variables
    TNT_SESSION_SHARED_VAR( UserSession,              userSession, () );

    TNT_REQUEST_SHARED_VAR( std::vector<AccountData>, s_trustedAccountList, () );
    TNT_REQUEST_SHARED_VAR( std::vector<AccountData>, s_searchAccountList, () );
    TNT_REQUEST_SHARED_VAR( std::string,              s_feedback, () );


    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };


    unsigned long arg_account_id =
        qparam.arg<unsigned long>("arg_account_id");
    bool arg_revoke_trust_button =
        qparam.arg<bool>("arg_revoke_trust_button");

    std::string arg_serach_string =
        qparam.arg<std::string>("arg_serach_string");
    bool arg_serch_user_button =
        qparam.arg<bool>("arg_serch_user_button");
    bool arg_get_all_user_button =
        qparam.arg<bool>("arg_get_all_user_button");

    bool arg_trust_user_button =
        qparam.arg<bool>("arg_trust_user_button");

    AccountData accountData( userSession.getUserID() );
    if ( accountData.isTrustedAccount() ) {
        s_feedback = "Derzeit gibt es nehmenden der dir vertraut! \
            Das bedeutet, das du niemanden deinerseits das Vertrauen \
            aussprechen kannst. Solange wie du nicht das Vertrauen eines \
            anderen Benutzer bekommen hast (dem wiederum von anderen \
            vertraut wird) sind deine Beiträge für andere nicht sichtbar.";
    } else {


        if( arg_serch_user_button ) {
            if( arg_serach_string != "" ) {
                s_searchAccountList = WebACL::getSearchAccounts( arg_serach_string );
            } else {
                s_feedback = "Suchstring ist leer!";
            }
        }

        if( arg_get_all_user_button ) {
            s_searchAccountList = WebACL::getAllAccounts( );
        }

        if( arg_revoke_trust_button ) {
            AccountData accountData;
            accountData.setID( arg_account_id );
            accountData.revokeTrust( userSession.getUserID() );
        }

        if( arg_trust_user_button ) {
            if ( arg_account_id == userSession.getUserID() ) {
                s_feedback = "Es ist nicht möglich sich selbst das Vertrauen auszusprechen!";
            } else {
                AccountData accountData( arg_account_id );
//                 accountData.setID( arg_account_id );
                accountData.trustedByGuarantor( userSession.getUserID() );
//                 WebACL::setTrustAccounts(
//                     arg_account_id,
//                     userSession.getUserID()
//                 );
            }
        }

        AccountData ownAccountData;
        ownAccountData.setID( userSession.getUserID() );
        s_trustedAccountList = ownAccountData.getTrustAccounts();
    }

    return DECLINED;
}
