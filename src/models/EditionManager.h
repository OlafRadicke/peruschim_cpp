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

#ifndef EDITIONMANAGER_H
#define EDITIONMANAGER_H

#include <vector>
#include <string>
#include <iostream>

#include <cxxtools/log.h>
#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>

#include "Edition.h"
#include "Config.h"

class EditionManager {

public:


    /**
     * Delete a edition data with a specifed id.
     * @arg id a edition.
     **/
    static void deleteEditionByID ( const unsigned long id );

    /**
     * Get back all editions data of a user.
     * @arg user_id usr id
     * @return list of all edition datas.
     **/
    static std::vector<Edition> getAllEditions ( const unsigned long user_id );

    /**
     * Get back a edition data with a specifed id.
     * @arg id a edition.
     **/
    static Edition getEditionByID ( const unsigned long id );

    /**
     * Cecked if this edition in use of any quote.
     * @arg id a edition.
     * @return get back a number of quote that this edition us.
     **/
    static int isEditionInUse ( const unsigned long id );

private:

};

#endif

