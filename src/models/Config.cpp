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

#include "Config.h"
#include <cxxtools/serializationinfo.h>
#include <cxxtools/propertiesdeserializer.h>
#include <cxxtools/mutex.h>
#include <cxxtools/fileinfo.h>
#include <cxxtools/log.h>
#include <fstream>

////////////////////////////////////////////////////////////////////////
// ConfigImpl
//
class ConfigImpl
{
    friend void operator>>= (const cxxtools::SerializationInfo& si, ConfigImpl& config);

public:
    ConfigImpl()
    { }

    void read(const std::string& fname);

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

void operator>>= (const cxxtools::SerializationInfo& si, ConfigImpl& config)
{
    si.getMember("APP-IP")             >>= config.m_appIp;
    si.getMember("APP-PORT")           >>= config.m_appPort;
    si.getMember("DB-DRIVER")          >>= config.m_dbDriver;
    si.getMember("SESSION-RUNTIME")    >>= config.m_sessionTimeout;
    si.getMember("SMTP-SERVER")        >>= config.m_smtpServer;
    si.getMember("MAIL-FROM-ADDRESS")  >>= config.m_mailFromAddress;
    config.m_si = si;
}

void ConfigImpl::read(const std::string& fname)
{
    std::ifstream in(fname.c_str());
    cxxtools::PropertiesDeserializer deserializer(in);
    deserializer.deserialize(*this);

    log_init(*deserializer.si());
}

namespace
{
    bool configRead = false;
    ConfigImpl theImpl;
    cxxtools::Mutex mutex;
}

////////////////////////////////////////////////////////////////////////
// Config
//
const std::string& Config::appIp() const
{
    return impl->appIp();
}

unsigned short Config::appPort() const
{
    return impl->appPort();
}

const std::string& Config::dbDriver() const
{
    return impl->dbDriver();
}

unsigned Config::sessionTimeout() const
{
    return impl->sessionTimeout();
}

const std::string& Config::smtpServer() const
{
    return impl->smtpServer();
}

const std::string& Config::mailFromAddress() const
{
    return impl->mailFromAddress();
}

std::string Config::get(const std::string& var) const
{
    return impl->get(var);
}

Config::Config ()
    : impl(0)
{
    cxxtools::MutexLock lock(mutex);
    if (!configRead)
    {
        std::string fname;

        if (cxxtools::FileInfo::exists("peruschim_cpp.conf"))
        {
            fname = "peruschim_cpp.conf";
        }
        else
        {
            fname = "/etc/peruschim_cpp.conf";
        }

        theImpl.read(fname);
        configRead = true;
    }

    impl = &theImpl;
}

