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


#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>

#include <Core/manager/KeywordRegister.h>
#include <Core/models/Config.h>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<



vector<string> KeywordRegister::getAllKeywordTitles( void ){
    DEBUG std::endl;
    vector<string> keywordList;
    tntdb::Result result;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    result = conn.select( "SELECT DISTINCT title title FROM quote_keyword ORDER BY title" );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        std::string title;
        row[0].get(title);
        keywordList.push_back( title );
    }
    return keywordList;
}



vector<KeywordCount> KeywordRegister::getAllKeywordTitleAndCound( const unsigned long owner_id ){
    DEBUG std::endl;
    vector< KeywordCount > keywordList;
    tntdb::Result result;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );

//     tntdb::Statement st = conn.prepare(
//                             "SELECT title, \
//                                 COUNT(title) As Anzahl \
//                             FROM quote_keyword \
//                             WHERE quote_id in \
//                                 ( SELECT id \
//                                   FROM quote \
//                                   WHERE privatedata = FALSE \
//                                   OR owner_id = :v1 \
//                                 ) \
//                             GROUP BY title \
//                             ORDER BY title"
//     );


    tntdb::Statement st = conn.prepare(
                            "SELECT title, \
                                COUNT(title) As Anzahl \
                            FROM quote_keyword \
                            WHERE quote_id IN \
                                ( SELECT id \
                                  FROM quote \
                                  WHERE privatedata = FALSE \
                                  OR owner_id = :v1 \
                                ) \
                            AND quote_id IN \
                                ( SELECT id \
                                  FROM quote \
                                  WHERE owner_id IN \
                                      ( SELECT trusted_account_id \
                                        FROM account_trust \
                                      ) \
                                  OR owner_id = :v1 \
                                ) \
                            GROUP BY title \
                            ORDER BY title"
    );

    st.set( "v1", owner_id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        KeywordCount dataSet = KeywordCount();
        std::string title;
        dataSet.Name =  row[0].getString();
        dataSet.Count = row[1].getString();
        keywordList.push_back( dataSet );
    }
    return keywordList;
}

vector<KeywordCount> KeywordRegister::getAllPubKeywordTitleAndCound( void ) {
    DEBUG std::endl;
    vector< KeywordCount > keywordList;
    tntdb::Result result;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
//     result = conn.select(  "SELECT title, \
//                                 COUNT(title) As Anzahl \
//                             FROM quote_keyword \
//                             WHERE quote_id in ( SELECT id \
//                                     FROM quote \
//                                     WHERE privatedata = FALSE ) \
//                             GROUP BY title \
//                             ORDER BY title" );
    result = conn.select(  "SELECT title, \
                                COUNT(title) As Anzahl \
                            FROM quote_keyword \
                            WHERE quote_id in ( SELECT id \
                                    FROM quote \
                                    WHERE privatedata = FALSE ) \
                            AND quote_id IN \
                                ( SELECT id \
                                  FROM quote \
                                  WHERE owner_id IN \
                                      ( SELECT trusted_account_id \
                                        FROM account_trust \
                                      ) \
                                ) \
                            GROUP BY title \
                            ORDER BY title" );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        KeywordCount dataSet = KeywordCount();
        std::string title;
        dataSet.Name =  row[0].getString();
        dataSet.Count = row[1].getString();
        keywordList.push_back( dataSet );
    }
    return keywordList;

}


vector<KeywordCount> KeywordRegister::getOwnKeywordTitleAndCound( const unsigned long owner_id ){
    DEBUG "owner_id" <<  owner_id << std::endl;

    vector< KeywordCount > keywordList;
    tntdb::Result result;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );

    tntdb::Statement st = conn.prepare(
                            "SELECT title, \
                                COUNT(title) As Anzahl \
                            FROM quote_keyword \
                            WHERE quote_id in \
                                ( SELECT id \
                                  FROM quote \
                                  WHERE owner_id = :v1 \
                                ) \
                            GROUP BY title \
                            ORDER BY title" );

    st.set( "v1", owner_id ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        KeywordCount dataSet = KeywordCount();
        std::string title;
        dataSet.Name =  row[0].getString();
        dataSet.Count = row[1].getString();
        keywordList.push_back( dataSet );
    }
    return keywordList;

}
