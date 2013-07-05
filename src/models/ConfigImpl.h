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

#ifndef CONFIGIMPL_H
#define CONFIGIMPL_H

#include <string>
#include <cxxtools/serializationinfo.h>
#include <cxxtools/propertiesdeserializer.h>
// #include <cxxtools/mutex.h>
// #include <cxxtools/fileinfo.h>
// #include <cxxtools/log.h>
// #include <fstream>

/**
* @class ConfigImpl 
*/
class ConfigImpl
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, ConfigImpl& config);
//     friend void operator<<= (const cxxtools::SerializationInfo& si, ConfigImpl& config);

public:
    
    ConfigImpl():
        m_appIp("0.0.0.0"),
        m_appPort(8008),
        m_dbDriver("postgresql:dbname=peruschim"),
        m_sessionTimeout( 1000 ),
        m_smtpServer( "localhost" ),
        m_mailFromAddress( "peruschim_cpp.conf@localhost" )
    { }

    /**
     * Function is generating a config file example.
     * @arg filename Function is writting in a file with tis name.
     */
    void generatingConfigExample( const std::string& filename );
    
    void read(const std::string& filename);

    const std::string& appIp() const
    { return m_appIp; }

    unsigned short     appPort() const
    { return m_appPort; }

    const std::string& dbDriver() const
    { return m_dbDriver; }

    unsigned           sessionTimeout() const
    { return m_sessionTimeout; }

    const std::string& smtpServer() const
    { return m_smtpServer; }

    const std::string& mailFromAddress() const
    { return m_mailFromAddress; }

    std::string get(const std::string& var) const
    {
        std::string value;
        m_si.getMember(var) >>= value;
        return value;
    }
    
    
private:
    cxxtools::SerializationInfo m_si;

    std::string m_appIp;
    unsigned short m_appPort;
    std::string m_dbDriver;
    unsigned m_sessionTimeout;
    std::string m_smtpServer;
    std::string m_mailFromAddress;
};

#endif
