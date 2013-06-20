#include "controller/EditOwnVersesController.h"

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
    TNT_SESSION_GLOBAL_VAR( std::string, session_verse_id, ());
    TNT_SESSION_GLOBAL_VAR( std::string, delete_verse_id, ());
    TNT_SESSION_GLOBAL_VAR( std::string, affirmation_delete_verse_id, ());

    DEBUG "userSession.getUserName(): " << userSession.getUserName() << std::endl;
    // ACL Check
    if ( userSession.isInRole ( "user" ) == false ) {
        DEBUG "Nicht eingelogt" << std::endl;
        return reply.redirect ( "/access_denied" );
    }
    DEBUG "Eingelogt" << std::endl;
    quoteList = QuoteRegister::getAllQuoteOfUser( userSession.getUserID() );

    // is button delete pushed?
    if ( delete_verse_id != "" ) {
        affirmation_question = "";
        feedback = "";
        session_verse_id = delete_verse_id;
        affirmation_question = "Bibelvers mit ID " + session_verse_id + " wirklich löschen?";

    }

    // if delete affirmation clicked.
    if ( affirmation_delete_verse_id != "" ) {
        affirmation_question = "";
        feedback = "";
        DEBUG "will löschen: " << affirmation_delete_verse_id << endl;
//         AccountData accountData;
//         accountData.setID( affirmation_delete_verse_id );
//         accountData.deleteAllData();
        feedback = "Der Bibelverse mit der Id " + affirmation_delete_verse_id + " wurde gelöscht!";
        affirmation_delete_verse_id = "";
    }

    DEBUG "quoteList.size(): " << quoteList.size() << std::endl;
    return DECLINED;
}

