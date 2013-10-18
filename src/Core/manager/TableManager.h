/*
* Copyright (C) 2013 Olaf Radicke
*
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

#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <tntdb/connect.h>

/**
 * Thes class manages the tabe strcture in the data base.
 */
class TableManager
{
public:
    TableManager();

    /**
     * It's return the version of the table.
     */
    std::string getTabeVersion();
    
    /**
     * Check the table version an do a update if
     * this required.
     * @return If this successful it is get back "true".
     */
    bool update();
    
private:
    /**
     * this take a table update no. 2
     * @return If this successful it is get back "true".
     */ 
    bool setUpdate2();    
    
    
    tntdb::Connection m_conn;
};

#endif 

