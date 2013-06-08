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

#ifndef DATABASEPROXY_H
#define DATABASEPROXY_H

#include <vector>
#include <string>
#include <iostream>

#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>

#include "Config.h"

using namespace std;

class DatabaseProxy {

public:

    string m_dbbackent;

     /**
     * Convert int to string.
     * @param sqlcommand a sql command.
     **/
    static std::string convertIntToStr( int number );

     /**
     * Do a SQL command without result.
     * @param sqlcommand a sql command.
     **/
    void sqlSet( string sqlcommand );

     /**
     * get back a SQL result as 3d vector.
     * @param sqlcommand a sql command.
     * @return If nothing found, it is get back a empty string.
     **/
    vector< vector<string> >  sqlGet( string sqlcommand );

    /**
     * get back the first fund of result.
     * @param sqlcommand a sql command.
     * @return If nothing found, it is get back a empty string.
     **/
    string  sqlGetSingle ( string sqlcommand );

    /**
     * Replace a char with a string.
     * @param s origin string
     * @return a string with the replaceings.
     */
    static std::string replace ( std::string s );

    /**
     * Replace a char with a string.
     * @param s origin string
     * @param K searching char
     * @param r replace string
     * @return a string with the replaceings.
     */
    static std::string replace (
        std::string s,
        const std::string& k,
        const std::string& r
    );



private:


    /** PostreSQL database name */
//     string           m_pg_db_name;
    /** PostreSQL database host */
//     string           m_pg_db_host;
    /** PostreSQL database user */
//     string           m_pg_db_user;
    /** PostreSQL database password */
//     string           m_pg_db_passwd;
    /** PostreSQL database port */
//     string           m_pg_db_port;




};

#endif
