#include "controller/EditOwnVerses.h"

# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<

namespace controller
{
  unsigned EditOwnVerses::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
  {
    TNT_REQUEST_GLOBAL_VAR( UserSession, userSession, ());

    std::vector<Quote> quoteList;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        return reply.redirect ( "/access_denied" );
    }
    DEBUG "Eingelogt" << std::endl;
    quoteList = QuoteRegister::getAllQuoteOfUser( userSession.getUserID() );
    
    return DECLINED;
  }
  
}