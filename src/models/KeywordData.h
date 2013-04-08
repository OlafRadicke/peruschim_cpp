#ifndef KEYWORDREGISTER_H
#define KEYWORDREGISTER_H 

#include <string>
#include <vector>


/**
 * This class stor data of a Kexword.
 **/
class KeywordData {
    
public:
    KeywordRegister ():    
        m_id(""),
        m_quote_id(""),
        m_title("") {};
    
private:
    
    /**
     * ID of Keyword.
     **/
    string      m_id;
    
    /**
     * ID of quote where the keyword is linked.
     **/    
    string      m_quote_id;
    
    /**
     * The title or name from the keyword.
     **/      
    string      m_title; 
}

#endif 