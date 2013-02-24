
#include "SeekerManager.h"



std::vector<SeekerData> getAllSeekers ( std::vector<TeamDataBase> dataBaseList ) {
    
    std::vector<SeekerData> seekersList;
    vector< vector<string> > sqlResult;
    
    for ( unsigned int i=0; i<dataBaseList.size(); i++ ) {
        DatabaseProxy database_proxy ( dataBaseList[i] );
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet 
        ( 
                "SELECT \
                    seeker_no, \
                    seeker_id, \
                    name, \
                    street, \
                    housenumber, \
                    zip_code, \
                    city, \
                    birthday, \
                    salutation, \
                    joining, \
                    priority, \
                    note, \
                    address_addition \
                FROM a23_seeker;"
        );

        for ( unsigned int i=0; i<sqlResult.size(); i++ ) {
            DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
            SeekerData seekerData;
            seekerData.setTeamDataBase ( dataBaseList[i] );
            seekerData.setSeeker_no ( sqlResult[i][0] );
            seekerData.setSeeker_id ( sqlResult[i][1] );
            seekerData.setName ( sqlResult[i][2] );
            seekerData.setStreet ( sqlResult[i][3] );
            seekerData.setHousenumber ( sqlResult[i][4] );
            seekerData.setZip_code ( sqlResult[i][5] );
            seekerData.setCity ( sqlResult[i][6] );
            seekerData.setBirthday ( sqlResult[i][7] );
            seekerData.setSalutation ( sqlResult[i][8] );
            seekerData.setJoining ( sqlResult[i][9] );
            seekerData.setPriority ( sqlResult[i][10] );
            seekerData.setNote ( sqlResult[i][11] );
            seekerData.setAddress_addition (  sqlResult[i][12] );
            
            seekersList.push_back ( seekerData );
        }          
        
    }
    
    return seekersList;    
}