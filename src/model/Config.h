
#ifndef CONFIG_H
#define CONFIG_H 
 
#include <fstream>
#include <iostream>
#include <list>
#include <string>

using namespace std;
/** 
* @class Config This class read a configuration file.
* The form of date in the configuration file is:
* key = value
*/
class Config {
    
public:
    Config();
    ~Config(){};
    
    /** 
     * get a value of configuration.
     * @arg key is the key of value
     */
    string get( string key );
    
    /** 
     * get back a list of configuration values.
     * @arg key is the key of value
     */    
    list<string> getList( string key );

    /** read the config file */
    void readConfigFile ();
    
    
    /** 
     * set path of config file
     * @arg path the path value 
     */
    void setConfFile ( string path );
    
    /** Get back the used config file
     */
    string getConfFile ( );

private:
    static list <string> m_configStrings;
    static string m_confFilePath;
};

#endif 