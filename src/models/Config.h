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

#include <list>
#include <string>

/**
* @class Config This class read a configuration file.
* The form of date in the configuration file is:
* key = value
*/
class Config {

public:
    Config();
    ~Config(){};

    /**
     * get a value of configuration.
     * @arg key is the key of value
     */
    std::string get( std::string key );

    /**
     * get back a list of configuration values.
     * @arg key is the key of value
     */
    std::list<std::string> getList( std::string key );

    /** read the config file */
    void readConfigFile ();


    /**
     * set path of config file
     * @arg path the path value
     */
    void setConfFile ( std::string path );

    /** Get back the used config file
     */
    std::string getConfFile ( );

private:
    static std::list <std::string> m_configStrings;
    static std::string m_confFilePath;
};

#endif
