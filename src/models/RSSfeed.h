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

#ifndef RSSFEED_H
#define RSSFEED_H

#include <string>
#include <tntdb/datetime.h>
#include <tntdb/cxxtools/datetime.h>

class RSSfeed
{

    friend class RSSfeedManager;

public:
    
    /**
     * Constructor.
     **/
    RSSfeed(){};

    /**
     * Get title of feed.
     **/
    const std::string& getTitle() const
    {
        return this->m_title;
    }

    /**
     * Get ID of feed.
     **/
    const unsigned long getID() const
    {
        return this->m_id;
    }

    /**
     * Get link url.
     **/
    const std::string& getLinkURL() const
    {
        return this->m_linkurl;
    }    

    /**
     * Get description.
     **/
    const std::string& getDescription() const
    {
        return this->m_description;
    }

    /**
     * Get create time.
     **/
    const cxxtools::DateTime& getCreateTime() const
    {
        return this->m_createtime;
    }
//     const tntdb::Datetime& getCreateTime() const
//     {
//         return this->m_createtime;
//     }

    
    // sets ====================================================

  
    /**
     * Set id of rss feed.
     **/
    void setID( unsigned id )
    {
        this->m_id = id;
    }
    
    /**
     * Set title of rss feed.
     **/
    void setTitle(const std::string& title )
    {
        this->m_title = title;
    }
    
    /**
     * Set link url of rss feed.
     **/
    void setLinkURL(const std::string& linkurl )
    {
        this->m_linkurl = linkurl;
    }
      
    /**
     * Set sescription of rss feed.
     **/
    void setDescription(const std::string& description )
    {
        this->m_description = description;
    }  

       
    /**
     * Set create time of rss feed.
     **/   
    void setCreateTime(const cxxtools::DateTime& createtime )
    {
        this->m_createtime = createtime;
    }
//     void setCreateTime(const tntdb::Datetime& createtime )
//     {
//         this->m_createtime = createtime;
//     }
    

private:
    
    unsigned long      m_id;
    std::string        m_title;
    std::string        m_linkurl;
    std::string        m_description;
    cxxtools::DateTime m_createtime;
//     tntdb::Datetime m_createtime;

};

#endif
