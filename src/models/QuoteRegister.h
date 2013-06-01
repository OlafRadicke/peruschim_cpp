#ifndef QUOTEREGISTER_H
#define QUOTEREGISTER_H

#include <string>
#include <vector>
#include <tntdb/statement.h>
#include "DatabaseProxy.h"
//#include "Edition.h"
#include "EditionManager.h"
#include "Quote.h"

/**
 * Managed quote informations.
 */
class QuoteRegister
{

public:

    /**
     * Get all public makiert quotes of a keyword.
     * @arg keyword The name of a keyword.
     * @return A vector of type Quote with public makiert quotes of a keyword.
     */
    static std::vector<Quote> getAllPubQuoteOfKeyword( const std::string keyword );

    /**
     * Get a export of user quote data in json format.
     * @arg userID Id of a user.
     * @return A json document.
     */
    static std::string getJsonExport( const std::string userID );

    /**
     * Get all quotes of user own quote.
     * @arg userID Id of a user.
     * @return A vector of type Quote.
     */
    static std::vector<Quote> getAllQuoteOfUser( const std::string userID );

    /**
     * Get all quotes of a keyword. If user login he get here own quote to.
     * @arg keyword The name of a keyword.
     * @arg userID Id of a user.
     * @return A vector of type Quote with quote of a public keyword and own.
     */
    static std::vector<Quote> getAllQuoteOfKeyword(
        const std::string keyword,
        const std::string userID );

    /**
     * Get a storaged quotes with a specific id.
     * @arg id the id of quote.
     * @return type of Quote with data from the database.
     */
    static Quote getQuoteWithID( const std::string id );

private:
    /**
     * A basic function for get lists of Quote from database.
     * @arg sqlcode a sql statement.
     */
    static std::vector<Quote> getQuotes ( tntdb::Statement st );

};



#endif
