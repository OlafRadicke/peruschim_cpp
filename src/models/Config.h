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

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <cxxtools/serializationinfo.h>

/**
* @class Config This class read a configuration file.
* The form of date in the configuration file is json.
*/
class Config {

    friend void operator>>= (const cxxtools::SerializationInfo& si, Config& config );



public:
    static Config& it();

    void read(const std::string& filename = "");

    const cxxtools::SerializationInfo& logging() const
    { return m_logging; }

    const std::string& appIp() const
    { return m_appIp; }

    unsigned short appPort() const
    { return m_appPort; }

    const std::string& dbDriver() const
    { return m_dbDriver; }

    const std::string& domainName() const
    { return m_domainName; }

    unsigned sessionTimeout() const
    { return m_sessionTimeout; }

    const std::string& smtpServer() const
    { return m_smtpServer; }

    const std::string& mailFromAddress() const
    { return m_mailFromAddress; }

private:
    bool                        configRead;
    cxxtools::SerializationInfo m_logging;
    std::string                 m_appIp;
    unsigned short              m_appPort;
    std::string                 m_dbDriver;
    std::string                 m_domainName;
    unsigned                    m_sessionTimeout;
    std::string                 m_smtpServer;
    std::string                 m_mailFromAddress;


public:

    Config()
      : configRead(false),
        m_appIp(""),
        m_appPort(8008),
        m_dbDriver("postgresql:dbname=peruschim"),
        m_sessionTimeout( 1000 ),
        m_smtpServer( "localhost" ),
        m_mailFromAddress( "peruschim_cpp.conf@localhost" ),
        m_domainName( "peruschim.domain" )
    { }

};

#endif
