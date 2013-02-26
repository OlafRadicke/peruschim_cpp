
#include "SeekerData.h"


std::vector<std::string> SeekerData::getQualitys ( void ) {

    std::vector< std::string > seekersQualitysList;
    std::vector< std::vector < std::string > > sqlResult;
    DEBUG std::endl;
    DatabaseProxy database_proxy ( m_team_database );
    DEBUG std::endl;
    sqlResult = database_proxy.sqlGet 
    ( 
            "SELECT quality_type \
            FROM a23_quality  \
            WHERE quality_id IN  ( \
                SELECT DISTINCT(quality_id)   \
                FROM a23_seeker_link_to_quality \
                WHERE seeker_id=" + m_seeker_id + " \
            );"
    );
    DEBUG "sqlResult.size(): " << sqlResult.size() << endl;
    for ( unsigned int i=0; i<sqlResult.size(); i++ ) {
        DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
        seekersQualitysList.push_back ( sqlResult[i][0] );
        DEBUG std::endl;
    }      
    return seekersQualitysList;
}