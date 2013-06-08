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

#ifndef EDITION_H
#define EDITION_H

#include <string>
#include <vector>
#include <tntdb/statement.h>
#include "Config.h"
#include "DatabaseProxy.h"


class Edition
{

public:
    /**
     * Constructor init strings.
     **/
    Edition():
        m_id(""),
        m_name(""),
        m_publisherName(""),
        m_releaseNumber(""),
        m_releaseDate(""),
        m_releasePlace("")
    {}


    /**
     * Get ID.
     **/
    const std::string getID() const
    {
        return this->m_id;
    }

    /**
     * Get name.
     **/
    const std::string getName() const
    {
        return this->m_name;
    }

    /**
    * Get publisher name.
    **/
    const std::string getPublisherName( ) const
    {
        return this->m_publisherName;
    }

    /**
    * Get release date.
    **/
    const std::string getReleaseDate( ) const
    {
        return this->m_releaseDate;
    }

    /**
    * Get release number.
    **/
    const std::string  getReleaseNumber( ) const
    {
        return this->m_releaseNumber;
    }

    /**
    * Get release place.
    **/
    const std::string getReleasePlace( ) const
    {
        return this->m_releasePlace;
    }

    /**
     * Save date as new data set in database.
     **/
    void saveAsNew();


    /**
     * Save date as new data set in database if data does not exist in data base.
     * @return Return ID of Edition, new or old.
     **/
    std::string saveAsNewIfNotExist();

    /**
     * Save date update in in database..
     **/
    void saveUpdate();

    // sets ==================================
    /**
     * Set name.
     * @param name new name.
     **/
    void setID( std::string id )
    {
        this->m_id = id;
    }

    /**
     * Set name.
     * @param name new name.
     **/
    void setName( std::string name )
    {
        this->m_name = name;
    }

    /**
     * Set id of owner.
     * @param user_id id of owner.
     **/
    void setOwnerID( const std::string user_id ){
        this->m_owner_id = user_id;
    }

    /**
    * Set publisher name.
    * @param name new name.
    **/
    void setPublisherName( std::string name )
    {
        this->m_publisherName = name;
    }

    /**
    * Set release date.
    **/
    void setReleaseDate( const std::string releaseDate )
    {
        this->m_releaseDate = releaseDate;
    }

    /**
    * Set release number.
    * @param number new number.
    **/
    void setReleaseNumber( std::string number )
    {
        this->m_releaseNumber = number;
    }

    /**
    * Set release place.
    * @param place new place.
    **/
    void setReleasePlace( std::string place )
    {
        this->m_releasePlace = place;
    }

private:

    /**
     *  edition id
     * Example: "35333"
     **/
    std::string m_id;

    /**
     *  edition name
     * Example: "Elberfelder"
     **/
    std::string m_name;

    /**
     *  ID of owner.
     **/
    std::string m_owner_id;

    /**
     *  edition publisher
     * Example: "Brunnenverlag"
     **/
    std::string m_publisherName;

    /**
     *  edition number
     * Example: "3.2a"
     **/
    std::string m_releaseNumber;

    /**
     *  edition date
     * Example: "2008-03-22"
     **/
    std::string m_releaseDate;

    /**
     *  edition place
     * Example: "Berlin/Hamburg"
     **/
    std::string m_releasePlace;


};

#endif

