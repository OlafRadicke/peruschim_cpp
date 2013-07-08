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
#include <cxxtools/jsondeserializer.h>
#include <cxxtools/mutex.h>
#include <cxxtools/fileinfo.h>
#include <cxxtools/log.h>
#include <fstream>

void ConfigImpl::read(const std::string& filename)
{
    std::ifstream in(filename.c_str());
    if (!in)
        throw std::runtime_error("failed to open configuration file \"" + filename + '"');

    cxxtools::JsonDeserializer deserializer(in);
    deserializer.deserialize(*this);

    cxxtools::SerializationInfo* psi = deserializer.si()->findMember("logging");
    if (psi)
      log_init(*psi);
}


/**
* define how to deserialize the cinfig file
* @arg si serialization info
* @arg config config class
*/
void operator>>= (const cxxtools::SerializationInfo& si, ConfigImpl& config )
{
    si.getMember("appIp")           >>= config.m_appIp;
    si.getMember("appPort")         >>= config.m_appPort;
    si.getMember("dbDriver")        >>= config.m_dbDriver;
    si.getMember("sessionRuntime")  >>= config.m_sessionTimeout;
    si.getMember("smtpServer")      >>= config.m_smtpServer;
    si.getMember("mailFromAddress") >>= config.m_mailFromAddress;
}


