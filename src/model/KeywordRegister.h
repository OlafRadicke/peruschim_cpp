#ifndef KEYWORDREGISTER_H
#define KEYWORDREGISTER_H 

#include <string>
#include <vector>

#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>

using namespace std; 

/**
 * The class has methods for keyword operations.
 **/
class KeywordRegister {
    
public:
    static vector<string> getAllKeywordTitles( void );
    
private:
    

};

#endif 