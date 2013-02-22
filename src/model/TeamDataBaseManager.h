#ifndef TEAMDATABASEMANAGER_H
#define TEAMDATABASEMANAGER_H 

#include <iostream>
#include <string>

#include "DatabaseProxy.h"
#include "TeamDataBase.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<

/**
 * Manage the team data base tasks and informations.
 **/
class TeamDataBaseManager {
    
public:
    
    /**
     * Get back all team data base data.
     * @return list of all account datas.
     **/     
    static std::vector<TeamDataBase> getAllTeamDataBases ( void );
    
private:
    

    
};


#endif 