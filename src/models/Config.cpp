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

#include <stdio.h>
#include <string>

#include "Config.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

using namespace std;

list <string> Config::m_configStrings;
string Config::m_confFilePath = "";

Config::Config () {
//     Config config;

    // checked is user config exist
    string homedir_conf =  "./peruschim_cpp.conf" ;
    ifstream fin ( homedir_conf.c_str() );
    if (fin)  // if yes than use...
    {
        setConfFile ( homedir_conf );
    } else { // if not, use globale conf
        setConfFile ( "/etc/peruschim_cpp.conf" );
    }
    fin.close();
    readConfigFile ();

}

string Config::get( string key ) {
    size_t found;
    list<string>::iterator i;
    key = key + "=";
//     DEBUG "key: " << key << endl;
//     DEBUG "values: " << m_configStrings.size() << endl;
    for( i=m_configStrings.begin(); i != m_configStrings.end(); ++i) {
//         DEBUG "round: " << *i << endl;
        found = (*i).find ( key );
        if (found!=string::npos) {
//             DEBUG "found at: " << int(found) << endl;
            if ( int(found) > 0 ) {
                continue;
            } else {
                return (*i).substr ( key.size(), ((*i).size() - key.size()) );
            }
        } else {
//             DEBUG "...no found" << endl;
        }
    }
    return "";
}

list<string> Config::getList( string key ) {
    list<string> resultList;
    size_t found;
    list<string>::iterator i;
    key = key + "=";
//     DEBUG "key: " << key << endl;
//     DEBUG "values: " << m_configStrings.size() << endl;
    for( i=m_configStrings.begin(); i != m_configStrings.end(); ++i) {
//         DEBUG "round: " << *i << endl;
        found = (*i).find ( key );
        if (found!=string::npos) {
//             DEBUG "found at: " << int(found) << endl;
            if ( int(found) > 0 ) {
                continue;
            } else {
                resultList.push_back ( (*i).substr ( key.size(), ((*i).size() - key.size()) ) );
            }
        } else {
//             DEBUG "...no found" << endl;
        }
    }
    return resultList;
}

string Config::getConfFile ( ){
    return m_confFilePath ;
}


void Config::readConfigFile ( ){
    string completString = "";
    string line = "";
//     DEBUG "open: " << Config::m_confFilePath << endl;
    // open fiele to read....
    ifstream config_file ( Config::m_confFilePath.c_str ()  );
    if ( config_file.is_open () ) {
        while ( config_file.good () ) {
            getline ( config_file, line );
//             DEBUG line << endl;
            m_configStrings.push_back ( line );
        }
    }else{
        cerr << "[201111062048] couldn't open \"" << m_confFilePath \
            << "\" for reading\n" << endl;
        throw;
    }
    config_file.close ();
}


void Config::setConfFile ( string path ) {
    m_confFilePath = path;
}
