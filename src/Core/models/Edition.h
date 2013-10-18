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

class Edition
{
    friend class EditionManager;

public:
    /**
     * Constructor init strings.
     **/
    Edition():
        m_ID(0),
        m_ownerID(0)
    {}


    /**
     * Get ID.
     **/
    unsigned long getID() const
    {
        return this->m_ID;
    }

    /**
     * Get name.
     **/
    const std::string& getName() const
    {
        return this->m_name;
    }

    /**
     * Get owner ID.
     **/
    unsigned long getOwnerID() const
    {
        return this->m_ownerID;
    }

    /**
    * Get publisher name.
    **/
    const std::string& getPublisherName( ) const
    {
        return this->m_publisherName;
    }

    /**
    * Get release date.
    * TODO use cxxtools::Date
    **/
    const std::string& getReleaseDate( ) const
    {
        return this->m_releaseDate;
    }

    /**
    * Get release number.
    **/
    const std::string& getReleaseNumber( ) const
    {
        return this->m_releaseNumber;
    }

    /**
    * Get release place.
    **/
    const std::string& getReleasePlace( ) const
    {
        return this->m_releasePlace;
    }

    // sets ==================================
    /**
     * Set name.
     * @param name new name.
     **/
    void setID( unsigned long id )
    {
        this->m_ID = id;
    }

    /**
     * Set name.
     * @param name new name.
     **/
    void setName( const std::string& name )
    {
        this->m_name = name;
    }

    /**
     * Set id of owner.
     * @param user_id id of owner.
     **/
    void setOwnerID( unsigned long user_id ){
        this->m_ownerID = user_id;
    }

    /**
    * Set publisher name.
    * @param name new name.
    **/
    void setPublisherName( const std::string& name )
    {
        this->m_publisherName = name;
    }

    /**
    * Set release date.
    * TODO use cxxtools::Date
    **/
    void setReleaseDate( const std::string& releaseDate )
    {
        this->m_releaseDate = releaseDate;
    }

    /**
    * Set release number.
    * @param number new number.
    **/
    void setReleaseNumber( const std::string& number )
    {
        this->m_releaseNumber = number;
    }

    /**
    * Set release place.
    * @param place new place.
    **/
    void setReleasePlace( const std::string& place )
    {
        this->m_releasePlace = place;
    }

private:

    /**
     *  edition id
     * Example: "35333"
     **/
    unsigned long m_ID;

    /**
     *  edition name
     * Example: "Elberfelder"
     **/
    std::string m_name;

    /**
     *  ID of owner.
     **/
    unsigned long m_ownerID;

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
     * TODO use cxxtools::Date
     **/
    std::string m_releaseDate;

    /**
     *  edition place
     * Example: "Berlin/Hamburg"
     **/
    std::string m_releasePlace;


};

#endif

