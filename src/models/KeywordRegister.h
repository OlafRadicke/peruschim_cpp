#ifndef KEYWORDREGISTER_H
#define KEYWORDREGISTER_H 

#include <string>
#include <vector>

#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>

using namespace std; 

/**
 * A helper class for store keyword name and count.
 **/
class KeywordCount {
    
public:
    /**
    * Name of keyword.
    **/    
    string Name;
    
    /**
    * Count of keyword.
    **/    
    string Count;
    
    KeywordCount () {
        this->Name = "";
        this->Count = "";
    }
};


/**
 * The class has methods for keyword operations.
 **/
class KeywordRegister {
    
public:
    
    /**
    * Get all used keywords.
    **/        
    static vector<string> getAllKeywordTitles( void );
    
    /**
    * Get all used keywords with cound.
    **/       
    static vector<KeywordCount> getAllKeywordTitleAndCound( void );
private:
    

};

#endif 