/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 */

#ifndef QUOTEMANAGER_H
#define QUOTEMANAGER_H

#include <tntdb/connection.h>

class Quote;

class QuoteManager
{
public:
    /**
     * Initialize QuoteManager with a existing database connection.
     */
    explicit QuoteManager(tntdb::Connection& conn_);

    /**
     * Initialize QuoteManager with a new database connection.
     */
    QuoteManager();

    /**
     * Save Quote as new data set in database.
     **/
    void saveAsNew(Quote& quote);

    /**
     * Update Quote in database.
     **/
    void update(const Quote& quote);

private:
    tntdb::Connection conn;
};

#endif // QUOTEMANAGER_H

