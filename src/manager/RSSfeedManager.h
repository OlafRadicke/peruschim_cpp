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

#ifndef RSSFEEDMANAGER_H
#define RSSFEEDMANAGER_H

#include "models/RSSfeed.h"
#include <vector>
#include <tntdb/connection.h>
#include <tntdb/cxxtools/datetime.h>

class RSSfeedManager {

public:
    RSSfeedManager();

    explicit RSSfeedManager(tntdb::Connection& conn);
    
    /**
     * Covert cxxtools::DateTime to RFC 822 format.
     * @arg cxxdt the datetime.
     * @retourn a date sting in RFC 822 format.
     **/
    std::string  covertDate( cxxtools::DateTime cxxdt );
    
    /**
     * Get back all feed younger than x days.
     * @arg days how many days go back.
     **/
    std::vector<RSSfeed> getFeeds( int days );
    

    /**
     * Get back the date of the last feed.
     * Target date format is RFC 822.
     * Exampel: Mon, 06 Sep 2009 16:20:00 +0000
     **/
    std::string getLastUpdate( );    
    
    /**
     * Save a new feed.
     * @arg newFeed feed data.
     **/    
    void addNewFeed( RSSfeed newFeed );


private:

    tntdb::Connection conn;

};

#endif

