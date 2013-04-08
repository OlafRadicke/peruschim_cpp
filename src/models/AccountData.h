#ifndef ACCOUNTDATA_H
#define ACCOUNTDATA_H 

#include <string>



/**
* This class represent a data set of the tabe a23t_account (system data base).
**/
class AccountData {
    
public:
    
    /**
     * Constructor init strings.
     **/
    AccountData () : 
        m_id ( "" ),
        m_login_name ( "" ),
        m_real_name ( "" ),
        m_password_hash ( "" ),
        m_password_salt ( "" ),
        m_email ( "" ),
        m_account_disable ( false )
    {};
    
//     void saveAccountData ( void );
    
    void setID ( std::string id ) { m_id = id; };
    std::string getID ( void ) { return m_id; };
    
    void setLogin_name ( std::string login_name ) { m_login_name = login_name; };
    std::string getLogin_name ( void ) { return m_login_name; };
    
    void setReal_name ( std::string real_name ) { m_real_name = real_name; };
    std::string getReal_name ( void ) { return m_real_name; };
    
    void setPassword_hash ( std::string password_hash ) { m_password_hash = password_hash; };
    std::string getPassword_hash ( void ) { return m_password_hash; };
    
    void setPassword_salt ( std::string password_salt ) { m_password_salt = password_salt; };
    std::string getPassword_salt ( void ) { return m_password_salt; };
    
    void setEmail ( std::string email ) { m_email = email; };
    std::string getEmail ( void ) { return m_email; };
    
    void setAccount_disable ( bool account_disable ) { m_account_disable = account_disable; };
    bool getAccount_disable ( void ) { return m_account_disable; };
    
private:

    
    std::string m_id;
    std::string m_login_name;
    std::string m_real_name;
    std::string m_password_hash;
    std::string m_password_salt;
    std::string m_email;
    bool        m_account_disable;   
    
    
};


#endif 