#ifndef TEAMDATABASE_H
#define TEAMDATABASE_H 

#include <iostream>
#include <string>


/**
* This class represent a data set of the tabe db_account (system data base).
**/
class TeamDataBase {
    
public:
    
    /**
     * Constructor init strings.
     **/
    TeamDataBase () : 
        m_account_id ( "" ),
        m_account_name ( "" ),
        m_server_name ( "" ),
        m_database_name ( "" ),
        m_port_no ( "" ),
        m_db_encoding ( "" ),
        m_db_user ( "" ),
        m_db_password ( "" ),
        m_db_sslmode ( "" ),
        m_owner_id ( "" )
    {};
    
    
    /**
     * Delete data set in the data base (by id).
     **/ 
    void deleteConnection ( void );    
    
    void setAccount_id ( std::string id ) { m_account_id = id; };
    std::string getAccount_id ( void ) { return m_account_id; };
    
    void setAccount_name ( std::string account_name ) { m_account_name = account_name; };
    std::string getAccount_name ( void ) { return m_account_name; };
    
    void setServer_name ( std::string server_name ) { m_server_name = server_name; };
    std::string getServer_name ( void ) { return m_server_name; };
    
    void setDatabase_name ( std::string database_name ) { m_database_name = database_name; };
    std::string getDatabase_name ( void ) { return m_database_name; };
    
    void setPort_no ( std::string port_no ) { m_port_no = port_no; };
    std::string getPort_no ( void ) { return m_port_no; };
    
    void setDB_encoding ( std::string db_encoding ) { m_db_encoding = db_encoding; };
    std::string getDB_encoding ( void ) { return m_db_encoding; };
    
    void setDB_user ( std::string db_user ) { m_db_user = db_user; };
    std::string getDB_user ( void ) { return m_db_user; };
    
    void setDB_password ( std::string db_password ) { m_db_password = db_password; };
    std::string getDB_password ( void ) { return m_db_password; };
    
    void setDB_sslmode ( std::string db_sslmode ) { m_db_sslmode = db_sslmode; };
    std::string getDB_sslmode ( void ) { return m_db_sslmode; };
    
    void setOwner_id ( std::string owner_id ) { m_owner_id = owner_id; };
    std::string getOwner_id ( void ) { return m_owner_id; };
    

    /**
     * Save data set as new record in the data base.
     **/ 
    void saveConnection ( void );     
    
    /**
     * Make a update from the data set record in the data base.
     **/ 
    void saveChanges ( void );   
    
private:
    
    std::string m_account_id;
    std::string m_account_name;
    std::string m_server_name;
    std::string m_database_name;
    std::string m_port_no;
    std::string m_db_encoding;
    std::string m_db_user;
    std::string m_db_password;
    std::string m_db_sslmode;
    std::string m_owner_id;
    
};


#endif 