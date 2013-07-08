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

class ConfigImpl;

/**
* @class Config This class read a configuration file.
* The form of date in the configuration file is:
* key = value
*/
class Config {

public:
    Config();

    const std::string& appIp() const;
    unsigned short     appPort() const;
    const std::string& dbDriver() const;
    unsigned           sessionTimeout() const;
    const std::string& smtpServer() const;
    const std::string& mailFromAddress() const;

private:
    ConfigImpl* impl;
};

#endif
