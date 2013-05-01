#ifndef QUOTEREGISTER_H
#define QUOTEREGISTER_H

#include <string>
#include <vector>
#include <tntdb/statement.h>
#include "DatabaseProxy.h"
//#include "Edition.h"
#include "Quote.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


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
     * Get all quotes of a keyword. If user login he get here own quote to.
     * @arg keyword The name of a keyword.
     * @arg userID Id of a user.
     * @return A vector of type Quote with quote of a public keyword and own.
     */
    static std::vector<Quote> getAllQuoteOfKeyword(
        const std::string keyword,
        const std::string userID );

private:
    /**
     * A basic function for get lists of Quote from database.
     * @arg sqlcode a sql statement.
     */
    static std::vector<Quote> getQuotes ( tntdb::Statement st );

};

#endif
