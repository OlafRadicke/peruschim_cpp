
#ifndef EDITIONMANAGER_H
#define EDITIONMANAGERL_H 
 
#include <vector>
#include <string>
#include <iostream>

#include "Edition.h"

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

