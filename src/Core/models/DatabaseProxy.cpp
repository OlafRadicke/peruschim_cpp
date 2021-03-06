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
#include <cxxtools/log.h>

#include <Core/models/DatabaseProxy.h>
#include <Core/models/Config.h>

log_define("models.DatabaseProxy")

std::vector< std::vector<std::string> > DatabaseProxy::sqlGet ( std::string sqlcommand )
{
    std::vector< std::vector<std::string> >  list_2d;
    unsigned int     col_count;
    tntdb::Result result;

    tntdb::Connection conn =
        tntdb::connectCached( Config::it().dbDriver() );

    result = conn.select( sqlcommand );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        std::vector<std::string>  list_1d;
        tntdb::Row row = *it;
        for ( col_count = 0; col_count != row.size(); col_count++ ) {
            std::string value;
            row[col_count].get(value);
            std::string copy_value = value;
            list_1d.push_back( copy_value );
        }
        list_2d.push_back( list_1d );
    }
    conn.close();
    return list_2d;
}

std::string DatabaseProxy::sqlGetSingle ( std::string sqlcommand )
{
    unsigned int     col_count;
    tntdb::Result result;

    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    result = conn.select( sqlcommand );
    for (tntdb::Result::const_iterator it = result.begin();
        it != result.end(); ++it
    ) {
        tntdb::Row row = *it;
        for ( col_count = 0; col_count != row.size(); col_count++ ) {

            std::string value;
            row[col_count].get(value);
            log_debug("value=" << value);
            return value;
        }
    }
    return "";
}

void DatabaseProxy::sqlSet ( std::string sqlcommand )
{
    tntdb::Connection conn = tntdb::connectCached( Config::it().dbDriver() );
    log_debug("sqlcommand: " << sqlcommand);
    conn.execute( sqlcommand );
}


std::string DatabaseProxy::replace (  std::string s ){
    if ( s == "" ) {
        return "";
    }
    return DatabaseProxy::replace ( s, "'", "''" );
}

std::string DatabaseProxy::replace (
    std::string s,
    const std::string& k,
    const std::string& r
){
    if ( s.length() == 0 ) {
        return s;
    }
    std::string::size_type p = 0;
    p = s.find(k, p);
    while ( p != std::string::npos) {
        s.replace(p, k.length(), r);
        p += r.length();
        p = s.find(k, p);
    }
    return s;
}


