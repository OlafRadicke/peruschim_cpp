/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
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

#include <manager/RSSfeedManager.h>
#include <models/RSSfeed.h>
#include <models/Config.h>

#include <tntdb/connect.h>
#include <tntdb/transaction.h>
#include <tntdb/statement.h>
#include <cxxtools/log.h>

log_define("RSSfeedManager")

RSSfeedManager::RSSfeedManager(tntdb::Connection& conn_)
    : conn(conn_)
{ }

RSSfeedManager::RSSfeedManager()
    : conn(tntdb::connectCached( Config::it().dbDriver() ))
{
}


void RSSfeedManager::addNewFeed( RSSfeed newFeed )
{
    tntdb::Transaction trans(conn);

    tntdb::Statement insQuote = conn.prepare(
        "INSERT INTO rss_feeds \
        ( \
            title  \
            linkurl \
            description \
            createtime \
        ) VALUES ( \
            :title  \
            :linkurl \
            :description \
            now \
        )"
    );
    
    insQuote.set( "title", newFeed.m_title )
            .set( "linkurl", newFeed.m_linkurl )
            .set( "description", newFeed.m_description )
            .execute();

    trans.commit();
}


cxxtools::DateTime  RSSfeedManager::getLastUpdate(){
    cxxtools::DateTime init_cxxdt(
        1971,
        7,
        12,
        18,
        0,
        0
    );
    
    RSSfeed feed;
    feed.setCreateTime( init_cxxdt );
    tntdb::Statement st = this->conn.prepare( "SELECT \
                        createtime \
                    FROM rss_feeds \
                    WHERE createtime = (select max(createtime) from rss_feeds)");
    st.execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;

        tntdb::Datetime dbdt = row[0].getDatetime() ;
        cxxtools::DateTime cxxdt(
            dbdt.getYear(),
            dbdt.getMonth(),
            dbdt.getDay(),
            dbdt.getHour(),
            dbdt.getMinute(),
            dbdt.getSecond()
        );
        feed.setCreateTime( cxxdt );
    }

    log_debug("feed.getCreateTime().toIsoString(): " <<  feed.getCreateTime().toIsoString() );
    return feed.getCreateTime();
    
}

std::vector<RSSfeed> RSSfeedManager::getFeeds ( int days ){
    std::vector<RSSfeed> feedList;
    std::string strDays = cxxtools::convert<std::string>( days );
    tntdb::Statement st = this->conn.prepare( "SELECT \
                        id, \
                        title, \
                        linkurl, \
                        description, \
                        createtime \
                    FROM rss_feeds \
                    WHERE createtime >  now() - INTERVAL '" + strDays + " day' \
                    ORDER BY createtime ");
    st.execute();
//     st.set( "days", days ).execute();

    for (tntdb::Statement::const_iterator it = st.begin();
        it != st.end(); ++it
    ) {
        tntdb::Row row = *it;
        RSSfeed feed;

        feed.setID( row[0].getInt() );
        feed.setTitle( row[1].getString() );
        feed.setLinkURL( row[2].getString() );
        feed.setDescription( row[3].getString() );
        cxxtools::DateTime cxxdt;
        row[3].get(cxxdt);        
//         tntdb::Datetime dbdt = row[3].getDatetime() ;
//         cxxtools::DateTime cxxdt(
//             dbdt.getYear(),
//             dbdt.getMonth(),
//             dbdt.getDay(),
//             dbdt.getHour(),
//             dbdt.getMinute(),
//             dbdt.getSecond()
//         );
        feed.setCreateTime( cxxdt );
        feedList.push_back( feed );
    }

    log_debug("feedList.size(): " <<  feedList.size());
    return feedList;
}