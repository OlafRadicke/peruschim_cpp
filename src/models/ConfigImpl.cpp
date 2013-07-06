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

#include "ConfigImpl.h"
#include <cxxtools/serializationinfo.h>
#include <cxxtools/propertiesdeserializer.h>
#include <cxxtools/jsonserializer.h>
#include <cxxtools/mutex.h>
#include <cxxtools/fileinfo.h>
#include <cxxtools/log.h>
#include <fstream>

/*
void ConfigImpl::generatingConfigExample( const std::string& filename ) 
{
    try
    {
        std::ofstream conffile;
        conffile.open ( filename.c_str() );
        cxxtools::JsonSerializer serializer( conffile );
        // this makes it just nice to read
        serializer.beautify(true);
        serializer.serialize( *this ).finish();
        conffile.close();        
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
*/



void ConfigImpl::read(const std::string& filename)
{
    std::ifstream in(filename.c_str());
    if (!in)
        throw std::runtime_error("failed to open configuration file \"" + filename + '"');

    cxxtools::PropertiesDeserializer deserializer(in);
    deserializer.deserialize(*this);

    log_init(*deserializer.si());
}


/**
* define how to serialize a defould config.
* @arg si serialization info
* @arg config config class.
*/
/*
void operator<<= ( const cxxtools::SerializationInfo& si, ConfigImpl& config )
{
    config.m_si = si;
    si.addMember("APP-IP")              <<= config.m_appIp;
    si.addMember("APP-PORT")            <<= config.m_appPort;
    si.addMember("DB-DRIVER")           <<= config.m_dbDriver;
    si.addMember("SESSION-RUNTIME")     <<= config.m_sessionTimeout;
    si.addMember("SMTP-SERVER")         <<= config.m_smtpServer;
    si.addMember("MAIL-FROM-ADDRESS")   <<= config.m_mailFromAddress;
}
*/

/**
* define how to deserialize the cinfig file
* @arg si serialization info
* @arg config config class
*/
void operator>>= (const cxxtools::SerializationInfo& si, ConfigImpl& config )
{
    si.getMember("APP-IP")             >>= config.m_appIp;
    si.getMember("APP-PORT")           >>= config.m_appPort;
    si.getMember("DB-DRIVER")          >>= config.m_dbDriver;
    si.getMember("SESSION-RUNTIME")    >>= config.m_sessionTimeout;
    si.getMember("SMTP-SERVER")        >>= config.m_smtpServer;
    si.getMember("MAIL-FROM-ADDRESS")  >>= config.m_mailFromAddress;
    config.m_si = si;
}


