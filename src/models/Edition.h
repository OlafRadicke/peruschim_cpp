
#ifndef EDITION_H
#define EDITION_H

#include <string>
#include <vector>
#include <tntdb/statement.h>
#include "Config.h"
#include "DatabaseProxy.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

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
    std::string getID()
    {
        return this->m_id;
    }

    /**
     * Get name.
     **/
    std::string getName()
    {
        return this->m_name;
    }

    /**
    * Get publisher name.
    **/
    std::string getPublisherName( )
    {
        return this->m_publisherName;
    }

    /**
    * Get release date.
    **/
    std::string getReleaseDate( )
    {
        return this->m_releaseDate;
    }

    /**
    * Get release number.
    **/
    std::string  getReleaseNumber( )
    {
        return this->m_releaseNumber;
    }

    /**
    * Get release place.
    **/
    std::string getReleasePlace( )
    {
        return this->m_releasePlace;
    }

    /**
     * Save date as new data set in database.
     **/
    void saveAsNew();

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

