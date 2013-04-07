
#ifndef EDITIONMANAGER_H
#define EDITIONMANAGERL_H 

#include <vector>
#include <string>
#include <iostream>

#include <cxxtools/log.h>
#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>

#include "Edition.h"
#include "Config.h"

class EditionManager {
    
public: 
    


    /**
     * Get back all editions data.
     * @return list of all edition datas.
     **/     
    static std::vector<Edition> getAllEditions ( void );

    
private:

};

#endif 

