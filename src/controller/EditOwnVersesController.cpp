#include "controller/EditOwnVersesController.h"

# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<


static tnt::ComponentFactoryImpl<EditOwnVerses> factory("EditOwnVersesController");

unsigned EditOwnVerses::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
    TNT_SESSION_GLOBAL_VAR( UserSession, userSession, ()); 
    TNT_SESSION_GLOBAL_VAR( std::vector<Quote>, quoteList, ());

    DEBUG "userSession.getUserName(): " << userSession.getUserName() << std::endl;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        return reply.redirect ( "/access_denied" );
    }
    DEBUG "Eingelogt" << std::endl;
    quoteList = QuoteRegister::getAllQuoteOfUser( userSession.getUserID() );

    DEBUG "quoteList.size(): " << quoteList.size() << std::endl;
    return DECLINED;
}

