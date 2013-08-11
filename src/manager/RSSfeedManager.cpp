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
#include <tntdb/error.h>
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
    log_debug("addNewFeed"  );

    tntdb::Statement insRSS = conn.prepare(
        "INSERT INTO rss_feeds \
        ( \
            title,  \
            linkurl, \
            description, \
            createtime \
        ) VALUES ( \
            :title,  \
            :linkurl, \
            :description, \
            now() \
        )"
    );
    
    insRSS.set( "title", newFeed.m_title )
            .set( "linkurl", newFeed.m_linkurl )
            .set( "description", newFeed.m_description )
            .execute();

    unsigned long feedID = conn.lastInsertId("rss_feeds_id_seq");

    tntdb::Statement insRSSchannel = conn.prepare(
            "INSERT INTO rss_feeds_channel \
             ( \
                 channel_title, \
                 rss_feeds_id \
             ) VALUES ( \
                 :channel_title, \
                 :rss_feeds_id \
             )"
        );

    log_debug( __LINE__ << " newFeed.channels.size(): " <<  newFeed.channels.size() );
    for (unsigned int i=0; i < newFeed.channels.size(); ++i )
    {
        log_debug( __LINE__ << " newFeed.channels.size(): " <<  newFeed.channels.size() );
        insRSSchannel
        .set( "rss_feeds_id", feedID )
        .set( "channel_title", newFeed.channels[i] )
                       .execute();
    }    
    
    
    log_debug("feed angelegt id: " <<  feedID );
}


std::string  RSSfeedManager::getLastUpdate(){
    cxxtools::DateTime cxxdt;

    tntdb::Statement st = this->conn.prepare( "SELECT \
                        createtime \
                    FROM rss_feeds \
                    WHERE createtime = (select max(createtime) from rss_feeds)");

    try {
        tntdb::Value value = st.selectValue( );
        value.get(cxxdt);
    } catch( tntdb::NotFound nfe )
    {
        cxxtools::DateTime init_cxxdt(
            1971,
            7,
            12,
            18,
            0,
            0
        );
        cxxdt = init_cxxdt;
    }

    log_debug("cxxdt.toIsoString(): " <<  cxxdt.toIsoString() );
    return covertDate( cxxdt );
}

std::string  RSSfeedManager::covertDate( cxxtools::DateTime cxxdt ){

    struct tm timeinfo;
    timeinfo.tm_year = ( cxxdt.year() - 1900 );
    timeinfo.tm_mon = cxxdt.month() - 1;
    timeinfo.tm_mday = cxxdt.day();
    timeinfo.tm_wday = 0;
    timeinfo.tm_hour = cxxdt.hour();
    timeinfo.tm_min = cxxdt.minute();
    timeinfo.tm_sec = cxxdt.second();
    timeinfo.tm_isdst = 0;
    // somewhat strange to use mktime to convert tm to time_t 
    // and localtime_r back to tm but we need the day of week
    time_t t = mktime(&timeinfo);  
    // localtime_r is the thread safe variant of localtime.
    localtime_r(&t, &timeinfo);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y %T %z", &timeinfo);
    
    return std::string(buffer);
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
        row[4].get(cxxdt);
        feed.setCreateTime( cxxdt );
        feedList.push_back( feed );
    }

    log_debug("feedList.size(): " <<  feedList.size());
    return feedList;
}