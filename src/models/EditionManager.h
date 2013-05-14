
#ifndef EDITIONMANAGER_H
#define EDITIONMANAGERL_H

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
     * Get back all editions data of a user.
     * @arg user_id usr id
     * @return list of all edition datas.
     **/
    static std::vector<Edition> getAllEditions ( const string user_id );

    /**
     * Get back a edition data with a specifed id.
     * @arg id a edition.
     **/
    static Edition getEditionByID ( const string id );


private:

};

#endif

