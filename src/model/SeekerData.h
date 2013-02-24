#ifndef SEEKERDATA_H
#define SEEKERDATA_H 

#include <string>
#include "TeamDataBase.h"



/**
* This class represent a data set of the tabe a23t_account (system data base).
**/
class SeekerData {
    
public:
    
    /**
     * Constructor init strings.
     **/
    SeekerData () : 
        m_team_database (),
        m_seeker_no ( "" ),
        m_seeker_id ( "" ),
        m_name ( "" ),
        m_street ( "" ),
        m_housenumber ( "" ),
        m_zip_code ( "" ),
        m_city ( "" ),
        m_birthday ( "" ),
        m_salutation ( "" ),
        m_joining ( "" ),
        m_priority ( "" ),
        m_note ( "" ),
        m_address_addition ( "" )          
    {};
    
//     void saveSeekerData ( void );
    
    void setTeamDataBase ( TeamDataBase team_database ) { m_team_database = team_database; };
    TeamDataBase  getTeamDataBase ( void ) { return m_team_database; };
    
    void setSeeker_no ( std::string seeker_no ) { m_seeker_no = seeker_no; };
    std::string getSeeker_no ( void ) { return m_seeker_no; };
    
    void setSeeker_id ( std::string seeker_id ) { m_seeker_id = seeker_id; };
    std::string getSeeker_id ( void ) { return m_seeker_id; };

    void setName ( std::string name ) { m_name = name; };
    std::string getName ( void ) { return m_name; };
    
    void setStreet ( std::string street ) { m_street = street; };
    std::string getStreet ( void ) { return m_street; };

    void setHousenumber ( std::string housenumber ) { m_housenumber = housenumber; };
    std::string getHousenumber ( void ) { return m_housenumber; };
    
    void setZip_code ( std::string zip_code ) { m_zip_code = zip_code; };
    std::string getZip_code ( void ) { return m_zip_code; };
    
    void setCity ( std::string city ) { m_city = city; };
    std::string getCity ( void ) { return m_city; };
    
    void setBirthday ( std::string birthday ) { m_birthday = birthday; };
    std::string getBirthday ( void ) { return m_birthday; };

    void setSalutation ( std::string salutation ) { m_salutation = salutation; };
    std::string getSalutation ( void ) { return m_salutation; };

    void setJoining ( std::string joining ) { m_joining = joining; };
    std::string getJoining ( void ) { return m_joining; };

    void setPriority ( std::string priority ) { m_priority = priority; };
    std::string getPriority ( void ) { return m_priority; };

    void setNote ( std::string note ) { m_note = note; };
    std::string getNote ( void ) { return m_note; };

    void setAddress_addition ( std::string address_addition ) { m_address_addition = address_addition; };
    std::string getAddress_addition ( void ) { return m_address_addition; }; 
    

private:

    /**
     * team data base where the seeker data is store.
     **/
    TeamDataBase m_team_database ;
    
    /**
     * Ist eine interne, frei wählbare Verwaltungsnummer.
     * Könnte sich mal ändern (z. B. wegen Umzug oder
     * Abteilungswechsel).
     **/
    std::string m_seeker_no           ;
    
    /**
     * Eindeutige ID-Nummer, die statisch verwendet werden soll
     **/
    std::string m_seeker_id           ;
    
    /**
     * Name des Suchers. Nach- und Vorname sollte Komma-getrennt sein. 
     * Nachname zuerst
     **/
    std::string m_name                ;
    
    /**
     * Straße der Postanschrift
     **/
    std::string m_street              ;
    
    /**
     * Hausnummer der Postanschrift
     **/
    std::string m_housenumber         ;
    
    /**
     * Postleitzahl der Postanschrift
     **/
    std::string m_zip_code            ;
    
    /**
     * Ort der Postanschrift
     **/
    std::string m_city                ;
    
    /**
     * Geburtsdatum des Suchers
     **/
    std::string m_birthday            ;
    
    /**
     * Anrede des Suchers: Herr, Frau, Firma, Familie usw.
     **/
    std::string m_salutation          ;
    
    /**
     * Meint Erfassungsdatum am...
     **/
    std::string m_joining             ;
    
    /**
     * Ob der Sucher bei der Suche bevorzugt werden soll,
     * um z. B. mehr beworben zu werden.
     **/
    std::string m_priority            ;
    
    /**
     * Sonstige Anmerkungen....
     **/
    std::string m_note                ;
    
    /**
     * Adresszusätze wie etwa Land
     **/
    std::string m_address_addition    ;   
    
    
};


#endif 