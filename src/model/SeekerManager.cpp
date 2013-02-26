
#include "SeekerManager.h"

std::vector<std::string> SeekerManager::getAllOfferSeekersStuff ( std::vector<TeamDataBase> dataBaseList ) {
    std::vector<string> seekersOfferList;
    vector< vector<string> > sqlResult;
    
    DEBUG "dataBaseList.size(): " << dataBaseList.size() << endl;
    for ( unsigned int db_i=0; db_i<dataBaseList.size(); db_i++ ) {
        DatabaseProxy database_proxy ( dataBaseList[db_i] );
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet 
        ( 
                "SELECT stuff_type \
                FROM a23_stuff_type  \
                WHERE stuff_id IN  ( \
                    SELECT DISTINCT(stuff_id)   \
                    FROM a23_seeker_link_to_stuff \
                );"
        );

        DEBUG "sqlResult.size(): " << sqlResult.size() << endl;
        for ( unsigned int i=0; i<sqlResult.size(); i++ ) {
            DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
            seekersOfferList.push_back ( sqlResult[i][0] );
            DEBUG std::endl;
        }          
    }
    return seekersOfferList;       
    
}

std::vector<SeekerData> SeekerManager::getStuffSelectedSeekers ( std::vector<TeamDataBase> dataBaseList , std::string stuff_filter )
{
    
    std::vector<SeekerData> seekersList;
    vector< vector<string> > sqlResult;
    
    DEBUG "dataBaseList.size(): " << dataBaseList.size() << endl;
    for ( unsigned int db_i=0; db_i<dataBaseList.size(); db_i++ ) {
        DatabaseProxy database_proxy ( dataBaseList[db_i] );
        DEBUG std::endl;
        sqlResult = database_proxy.sqlGet 
        ( 
                "SELECT \
                    a23_seeker.seeker_no, \
                    a23_seeker.seeker_id, \
                    a23_seeker.name, \
                    a23_seeker.street, \
                    a23_seeker.housenumber, \
                    a23_seeker.zip_code, \
                    a23_seeker.city, \
                    a23_seeker.birthday, \
                    a23_seeker.salutation, \
                    a23_seeker.joining, \
                    a23_seeker.priority, \
                    a23_seeker.note, \
                    a23_seeker.address_addition \
                FROM a23_seeker, a23_seeker_link_to_stuff, a23_stuff_type \
                WHERE a23_seeker.seeker_id=a23_seeker_link_to_stuff.seeker_id \
                AND a23_stuff_type.stuff_id=a23_seeker_link_to_stuff.stuff_id \
                AND a23_stuff_type.stuff_type='" + DatabaseProxy::replace( stuff_filter ) + "';"
        );

        DEBUG "sqlResult.size(): " << sqlResult.size() << endl;
        for ( unsigned int i=0; i<sqlResult.size(); i++ ) {
            DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
            SeekerData seekerData;
            DEBUG std::endl;
            TeamDataBase teamDataBase_copy = dataBaseList[db_i];
            DEBUG std::endl;
            seekerData.setTeamDataBase ( teamDataBase_copy );
            DEBUG "sqlResult[i][0]: " <<  sqlResult[i][0] << std::endl;
            seekerData.setSeeker_no ( sqlResult[i][0] );
            DEBUG "sqlResult[i][1]: " <<  sqlResult[i][1] << std::endl;
            seekerData.setSeeker_id ( sqlResult[i][1] );
            DEBUG "sqlResult[i][2]: " <<  sqlResult[i][2] << std::endl;
            seekerData.setName ( sqlResult[i][2] );
            DEBUG "sqlResult[i][3]: " <<  sqlResult[i][3] << std::endl;
            seekerData.setStreet ( sqlResult[i][3] );
            DEBUG "sqlResult[i][4]: " <<  sqlResult[i][4] << std::endl;
            seekerData.setHousenumber ( sqlResult[i][4] );
            DEBUG "sqlResult[i][5]: " <<  sqlResult[i][5] << std::endl;
            seekerData.setZip_code ( sqlResult[i][5] );
            DEBUG "sqlResult[i][6]: " <<  sqlResult[i][6] << std::endl;
            seekerData.setCity ( sqlResult[i][6] );
            DEBUG "sqlResult[i][7]: " <<  sqlResult[i][7] << std::endl;
            seekerData.setBirthday ( sqlResult[i][7] );
            DEBUG "sqlResult[i][8]: " <<  sqlResult[i][8] << std::endl;
            seekerData.setSalutation ( sqlResult[i][8] );
            DEBUG "sqlResult[i][9]: " <<  sqlResult[i][9] << std::endl;
            seekerData.setJoining ( sqlResult[i][9] );
            DEBUG "sqlResult[i][10]: " <<  sqlResult[i][10] << std::endl;
            seekerData.setPriority ( sqlResult[i][10] );
            DEBUG "sqlResult[i][11]: " <<  sqlResult[i][11] << std::endl;
            seekerData.setNote ( sqlResult[i][11] );
            DEBUG "sqlResult[i][12]: " <<  sqlResult[i][12] << std::endl;
            seekerData.setAddress_addition (  sqlResult[i][12] );
            DEBUG std::endl;
            seekersList.push_back ( seekerData );
            DEBUG std::endl;
        }          
    }
    return seekersList;    
}
    
    
std::vector<SeekerData> SeekerManager::getAllSeekers ( std::vector<TeamDataBase> dataBaseList ) {
    
    std::vector<SeekerData> seekersList;
    vector< vector<string> > sqlResult;
    
    DEBUG "dataBaseList.size(): " << dataBaseList.size() << endl;
    for ( unsigned int db_i=0; db_i<dataBaseList.size(); db_i++ ) {
        DatabaseProxy database_proxy ( dataBaseList[db_i] );
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
                FROM a23_seeker ;"
        );

        DEBUG "sqlResult.size(): " << sqlResult.size() << endl;
        for ( unsigned int i=0; i<sqlResult.size(); i++ ) {
            DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
            SeekerData seekerData;
            DEBUG std::endl;
            TeamDataBase teamDataBase_copy = dataBaseList[db_i];
            DEBUG std::endl;
            seekerData.setTeamDataBase ( teamDataBase_copy );
            DEBUG "sqlResult[i][0]: " <<  sqlResult[i][0] << std::endl;
            seekerData.setSeeker_no ( sqlResult[i][0] );
            DEBUG "sqlResult[i][1]: " <<  sqlResult[i][1] << std::endl;
            seekerData.setSeeker_id ( sqlResult[i][1] );
            DEBUG "sqlResult[i][2]: " <<  sqlResult[i][2] << std::endl;
            seekerData.setName ( sqlResult[i][2] );
            DEBUG "sqlResult[i][3]: " <<  sqlResult[i][3] << std::endl;
            seekerData.setStreet ( sqlResult[i][3] );
            DEBUG "sqlResult[i][4]: " <<  sqlResult[i][4] << std::endl;
            seekerData.setHousenumber ( sqlResult[i][4] );
            DEBUG "sqlResult[i][5]: " <<  sqlResult[i][5] << std::endl;
            seekerData.setZip_code ( sqlResult[i][5] );
            DEBUG "sqlResult[i][6]: " <<  sqlResult[i][6] << std::endl;
            seekerData.setCity ( sqlResult[i][6] );
            DEBUG "sqlResult[i][7]: " <<  sqlResult[i][7] << std::endl;
            seekerData.setBirthday ( sqlResult[i][7] );
            DEBUG "sqlResult[i][8]: " <<  sqlResult[i][8] << std::endl;
            seekerData.setSalutation ( sqlResult[i][8] );
            DEBUG "sqlResult[i][9]: " <<  sqlResult[i][9] << std::endl;
            seekerData.setJoining ( sqlResult[i][9] );
            DEBUG "sqlResult[i][10]: " <<  sqlResult[i][10] << std::endl;
            seekerData.setPriority ( sqlResult[i][10] );
            DEBUG "sqlResult[i][11]: " <<  sqlResult[i][11] << std::endl;
            seekerData.setNote ( sqlResult[i][11] );
            DEBUG "sqlResult[i][12]: " <<  sqlResult[i][12] << std::endl;
            seekerData.setAddress_addition (  sqlResult[i][12] );
            DEBUG std::endl;
            seekersList.push_back ( seekerData );
            DEBUG std::endl;
        }          
    }
    return seekersList;    
}