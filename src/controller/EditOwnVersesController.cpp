#include "controller/EditOwnVersesController.h"
#include "models/Quote.h"
#include "models/QuoteRegister.h"
#include "models/OString.h"

# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<


static tnt::ComponentFactoryImpl<EditOwnVerses> factory("EditOwnVersesController");

unsigned EditOwnVerses::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{

    TNT_SESSION_GLOBAL_VAR( UserSession, userSession, ());
    TNT_SESSION_GLOBAL_VAR( std::vector<Quote>, quoteList, ());

    // text with feedback infomation;
    TNT_SESSION_GLOBAL_VAR( std::string, feedback, ());
    TNT_SESSION_GLOBAL_VAR( std::string, affirmation_question, ());
    // id of selectetet verse.
    TNT_SESSION_GLOBAL_VAR( unsigned long, session_verse_id, (0));
    unsigned long delete_verse_id = 
        qparam.arg<unsigned long>("delete_verse_id");
    unsigned long affirmation_delete_verse_id =   
        qparam.arg<unsigned long>("affirmation_delete_verse_id");

    DEBUG "userSession.getUserName(): " << userSession.getUserName() << std::endl;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        return reply.redirect ( "/access_denied" );
    }
    DEBUG "Eingelogt" << std::endl;
//     quoteList = QuoteRegister::getAllQuoteOfUser( userSession.getUserID() );

    // is button delete pushed?
    if ( delete_verse_id > 0 ) {
        affirmation_question = "";
        feedback = "";
        session_verse_id = delete_verse_id;
        Quote quoteInfo = QuoteRegister::getQuoteWithID( 
            cxxtools::convert<unsigned long>( session_verse_id ) 
        );
        affirmation_question = 
            "Bibelvers mit "+ quoteInfo.getBookTitle() + " " + \
            cxxtools::convert<std::string>( quoteInfo.getChapterBegin() ) + \
            ":" + cxxtools::convert<std::string>( quoteInfo.getSentenceBegin() ) + \
            " (ID: " + cxxtools::convert<std::string>(session_verse_id) \
            + ") wirklich löschen?";
        DEBUG "affirmation_question" << affirmation_question << std::endl;
    }

    // if delete affirmation clicked.
    if ( affirmation_delete_verse_id > 0 ) {
        affirmation_question = "";
        feedback = "";
        DEBUG "will löschen: " << affirmation_delete_verse_id << endl;
        QuoteRegister::deleteQuote( 
            cxxtools::convert<unsigned long>( affirmation_delete_verse_id )        
        );
        feedback = \
            "Der Bibelverse mit der ID " + \
             cxxtools::convert<std::string>( affirmation_delete_verse_id ) + \
             " wurde gelöscht!";
        affirmation_delete_verse_id = 0;
    }
    quoteList = QuoteRegister::getAllQuoteOfUser( userSession.getUserID() );

    return DECLINED;
}
