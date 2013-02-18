#ifndef TEAMDATABASE_H
#define TEAMDATABASE_H 

#include <iostream>
#include <string>

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
    
    void saveConnection ( void );
    
    void setAccount_id ( std::string id ) { m_account_id = id; };
    void setAccount_name ( std::string account_name ) { m_account_name = account_name; };
    void setServer_name ( std::string server_name ) { m_server_name = server_name; };
    void setDatabase_name ( std::string database_name ) { m_database_name = database_name; };
    void setPort_no ( std::string port_no ) { m_port_no = port_no; };
    void setDB_encoding ( std::string db_encoding ) { m_db_encoding = db_encoding; };
    void setDB_user ( std::string db_user ) { m_db_user = db_user; };
    void setDB_password ( std::string db_password ) { m_db_password = db_password; };
    void setDB_sslmode ( std::string db_sslmode ) { m_db_sslmode = db_sslmode; };
    void setOwner_id ( std::string owner_id ) { m_owner_id = owner_id; };
    
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