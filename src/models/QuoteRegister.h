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

#ifndef QUOTEREGISTER_H
#define QUOTEREGISTER_H

#include <string>
#include <vector>
#include <tntdb/statement.h>
#include "DatabaseProxy.h"
//#include "Edition.h"
// #include "EditionManager.h"
#include "Quote.h"

/**
 * Managed quote informations.
 */
class QuoteRegister
{

public:


    /**
     * Delete all of user own quote.
     * @arg userID Id of a user.
     * @return A vector of type Quote.
     */
    static void deleteAllQuoteOfUser( const std::string userID );

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

    /**
     * Make a JSON-Import of user quotes.
     * @arg jsonText test in json fomat with user verses/quotes.
     * @arg owner_id owner of imported data.
     */
    static void jsonImport( const std::string jsonText, std::string owner_id );

private:
    /**
     * A basic function for get lists of Quote from database.
     * @arg sqlcode a sql statement.
     */
    static std::vector<Quote> getQuotes ( tntdb::Statement st );

};



#endif
