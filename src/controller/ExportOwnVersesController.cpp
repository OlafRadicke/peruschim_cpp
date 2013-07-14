#include "controller/ExportOwnVersesController.h"
#include "models/QuoteRegister.h"
#include "models/UserSession.h"
#include <cxxtools/log.h>
#include <iostream>

log_define("component.ExportOwnVersesController")

static tnt::ComponentFactoryImpl<ExportOwnVersesController> factory("ExportOwnVersesController");

unsigned ExportOwnVersesController::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{

    TNT_SESSION_GLOBAL_VAR( UserSession, userSession, ());
    TNT_SESSION_GLOBAL_VAR( std::string, jason_text, ());
    TNT_SESSION_GLOBAL_VAR( std::string, feedback, ());

    log_debug("userSession.getUserName(): " << userSession.getUserName() );
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        return reply.redirect ( "/access_denied" );
    };
    
    jason_text = QuoteRegister::getJsonExport( userSession.getUserID() );

    return DECLINED;
}

