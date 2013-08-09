/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
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

#include "models/Edition.h"
#include <vector>
#include <tntdb/connection.h>

class EditionManager {

public:
    EditionManager();

    explicit EditionManager(tntdb::Connection& conn);

    /**
     * Delete a edition data with a specifed id.
     * @arg id a edition.
     **/
    void deleteEditionByID ( unsigned long id );

    /**
     * Get back all editions data of a user.
     * @arg user_id usr id
     * @return list of all edition datas.
     **/
    std::vector<Edition> getAllEditions ( unsigned long user_id );

    /**
     * Get back a edition data with a specifed id.
     * @arg id a edition.
     **/
    Edition getEditionByID ( unsigned long id );

    /**
     * Cecked if this edition in use of any quote.
     * @arg id a edition.
     * @return get back a number of quote that this edition us.
     **/
    bool isEditionInUse ( unsigned long id );

    /**
     * Save date as new data set in database.
     **/
    void saveAsNew(Edition& edition);

    /**
     * Save date as new data set in database if data does not exist in data base.
     * @return Return ID of Edition, new or old.
     **/
    unsigned long saveAsNewIfNotExist(Edition& edition);

    /**
     * Save date update in in database..
     **/
    void saveUpdate(const Edition& edition);

private:

    tntdb::Connection m_conn;

};

#endif

