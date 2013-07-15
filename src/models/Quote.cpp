
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

#include "Quote.h"
#include "Config.h"

#include <tntdb/transaction.h>
#include <tntdb/connect.h>
#include <tntdb/statement.h>

#include <cxxtools/join.h>
#include <cxxtools/split.h>
#include <cxxtools/trim.h>

#include <functional>
#include <algorithm>
#include <locale>

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

namespace
{
    std::string lowercase ( const std::string& str )
    {
        std::string ret = str;

        std::transform(str.begin(), str.end(), ret.begin(), 
            std::bind2nd(std::ptr_fun(&std::tolower<char>), std::locale("")));

        return ret;
    }

    void removeSpaces(std::string& str)
    {
        std::string::size_type p;
        while ((p = str.find(' ')) != std::string::npos)
            str.erase(p, 1);
    }

}

Quote::Quote()
  : m_isPrivateData(false),
    m_ownerID(0),
    m_bookChapterBegin(0),
    m_bookSentenceBegin(0),
    m_bookChapterEnd(0),
    m_bookSentenceEnd(0)
{
}


std::vector<std::string> Quote::getKeywords() {
    Config config;

    if ( this->m_quoteKeywords.size() < 1 && this->m_ID > 0 ) {

        tntdb::Connection conn = tntdb::connectCached( config.dbDriver() );
        tntdb::Statement st = conn.prepare( "SELECT title \
            FROM quote_keyword \
            WHERE quote_id = :v1 \
            ORDER BY title" );
        st.set("v1", this->m_ID );

        for ( tntdb::Statement::const_iterator it = st.begin(); it != st.end(); ++it )
        {
            tntdb::Row row = *it;
            Quote dataQuote = Quote();
            this->m_quoteKeywords.push_back( row[0].getString() );
        }
    }
    return this->m_quoteKeywords;
}

std::string Quote::getKeywordsAsString()
{
    std::vector<std::string> keywords = getKeywords();
    return cxxtools::join(keywords.begin(), keywords.end(), ',');
}

void Quote::setKeywords( const std::string& keywords )
{
    m_quoteKeywords.clear();

    std::string k = lowercase(cxxtools::trim(keywords));
    cxxtools::split(cxxtools::Regex("[ \t]*,[ \t]*"), keywords, std::back_inserter(m_quoteKeywords));
}

