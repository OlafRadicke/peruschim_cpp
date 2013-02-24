
#include "TeamDataBaseManager.h"


std::vector<TeamDataBase> TeamDataBaseManager::getAllTeamDataBases ( void ) {
    
    DatabaseProxy database_proxy;
    vector< vector<string> > sqlResult;
    vector<TeamDataBase> dataBaseList;
    
    DEBUG std::endl;
    sqlResult = database_proxy.sqlGet 
    ( 
            "SELECT \
                account_id, \
                account_name, \
                server_name, \
                database_name, \
                port_no, \
                db_encoding, \
                db_user, \
                db_password, \
                db_sslmode, \
                owner_id  \
            FROM db_account;"
    );

    for ( unsigned int i=0; i<sqlResult.size(); i++) {
        DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
        TeamDataBase tDataBase;
        tDataBase.setAccount_id ( sqlResult[i][0] );
        tDataBase.setAccount_name ( sqlResult[i][1] );
        tDataBase.setServer_name ( sqlResult[i][2] );
        tDataBase.setDatabase_name ( sqlResult[i][3] );
        tDataBase.setPort_no ( sqlResult[i][4] );
        tDataBase.setDB_encoding ( sqlResult[i][5] );
        tDataBase.setDB_user ( sqlResult[i][6] );
        tDataBase.setDB_password ( sqlResult[i][7] );
        tDataBase.setDB_sslmode ( sqlResult[i][8] );
        tDataBase.setOwner_id ( sqlResult[i][9] );

        dataBaseList.push_back ( tDataBase );
    }  
    return dataBaseList;
}


std::vector<TeamDataBase> TeamDataBaseManager::getAllTeamDataBases (  std::string account_name  ) {
    
    DatabaseProxy database_proxy;
    vector< vector<string> > sqlResult;
    vector<TeamDataBase> dataBaseList;
    
    DEBUG std::endl;
    
    string sqlCommand =  "SELECT \
                account_id, \
                account_name, \
                server_name, \
                database_name, \
                port_no, \
                db_encoding, \
                db_user, \
                db_password, \
                db_sslmode, \
                owner_id  \
            FROM db_account \
            WHERE owner_id=( \
                SELECT id FROM a23t_account \
                WHERE login_name='" + DatabaseProxy::replace( account_name ) + "' \
                );";
        
    
    DEBUG "sqlCommand: "  << sqlCommand << std::endl;            
    sqlResult = database_proxy.sqlGet ( sqlCommand );

    for ( unsigned int i=0; i<sqlResult.size(); i++) {
        DEBUG "push_back (" <<  i << "): " << sqlResult[i][0] << std::endl;
        TeamDataBase tDataBase;
        tDataBase.setAccount_id ( sqlResult[i][0] );
        tDataBase.setAccount_name ( sqlResult[i][1] );
        tDataBase.setServer_name ( sqlResult[i][2] );
        tDataBase.setDatabase_name ( sqlResult[i][3] );
        tDataBase.setPort_no ( sqlResult[i][4] );
        tDataBase.setDB_encoding ( sqlResult[i][5] );
        tDataBase.setDB_user ( sqlResult[i][6] );
        tDataBase.setDB_password ( sqlResult[i][7] );
        tDataBase.setDB_sslmode ( sqlResult[i][8] );
        tDataBase.setOwner_id ( sqlResult[i][9] );

        dataBaseList.push_back ( tDataBase );
    }  
    return dataBaseList;
}