#ifndef SEEKERMANAGER_H
#define SEEKERMANAGER_H 


#include <iostream>
#include <string>

#include "DatabaseProxy.h"
#include "SeekerData.h"
#include "TeamDataBase.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

/**
 * Manage the team data base tasks and informations.
 **/
class SeekerManager {
    
public:
    
    /**
     * Get back data of all seeker.
     * @param dataBaseList a list of data base connaction data.
     * @return list of all seeker datas.
     **/     
    static std::vector<SeekerData> getAllSeekers ( std::vector<TeamDataBase> dataBaseList );
     
    
private:
    

    
};


#endif 