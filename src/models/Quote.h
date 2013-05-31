#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <vector>
#include <map>
#include <sstream>

#include <tntdb/statement.h>
#include <cxxtools/jsonserializer.h>
#include <cxxtools/serializationinfo.h>

#include "DatabaseProxy.h"
#include "Edition.h"



class Quote
{

public:
    /**
     * Constructor init strings.
     **/
    Quote();

    vector<std::string> allBibleBooks;

    /**
     * Try to build the Bibleserver.com url.
     */
    const std::string getBibleserverComURL();
    
    /**
     * Get title of book.
     **/
    const std::string getBookTitle() const 
    {
        return this->m_bookTitle;
    }

    /**
     * Get number of chapter begin.
     **/
    const int getChapterBegin() const
    {
        return this->m_bookChapterBegin;
    }

    /**
     * Get number of chapter end.
     **/
    const int getChapterEnd() const
    {
        return this->m_bookChapterEnd;
    }

    /**
     * Get id of edition.
     **/
    const std::string getEditionID() const
    {
        return this->m_editionID;
    }

    /**
     * Get id of this quote.
     **/
    std::string getID( ) {
        return this->m_ID;
    }

    /**
     * Get back the keyword list.
     **/
    std::vector<std::string> getKeywords();

    /**
     * Get back the keyword list as string like: "rot,blau,weis" .
     **/
    std::string getKeywordsAsString();

    /**
     * Get Note.
     **/
    const std::string getNote() const 
    {
        return this->m_note;
    }

    /**
     * get id of the owner.
     **/
    std::string getOwnerID()
    {
        return this->m_ownerID;
    }

    /**
     * Get quote text.
     **/
    const std::string getQuoteText() const
    {
        return this->m_quoteText;
    }

    /**
     * Get number of sentence begin.
     **/
    const int getSentenceBegin() const
    {
        return this->m_bookSentenceBegin;
    }

    /**
     * Get number of sentence end.
     **/
    const int getSentenceEnd() const 
    {
        return this->m_bookSentenceEnd;
    }

    /**
     * get visible policy.
     **/
    const bool isPrivateData() const
    {
        return this->m_isPrivateData;
    }

    /**
     * Save date as new data set in database.
     **/
    void saveAsNew();

    /**
     * Save date update in in database..
     **/
    void saveUpdate();

    // sets ====================================================

    /**
     * Set title of book.
     **/
    void setBookTitle( std::string title )
    {
        this->m_bookTitle = title;
    }

    /**
     * Set number of chapter begin.
     **/
    void setChapterBegin( int number )
    {
        this->m_bookChapterBegin = number;
    }

    /**
     * Set number of chapter end.
     **/
    void setChapterEnd( int number )
    {
        this->m_bookChapterEnd = number;
    }

    /**
     * Set id of edition.
     **/
    void setEditionID( std::string id )
    {
        this->m_editionID = id;
    }

    /**
     * Set id of this quote.
     **/
    void setID( string id ) {
        this->m_ID= id;
    }

    /**
     * Set visible policy.
     **/
    void setIsPrivateData( bool visible )
    {
        this->m_isPrivateData = visible;
    }

    /**
     * Set keywords.
     * @param keywords strin with comma separated label values
     **/
    void setKeywords( std::string keywords ) ;

    /**
     * Set Note.
     **/
    void setNote( std::string note )
    {
        this->m_note = note;
    }

    /**
     * Set id of the owner.
     **/
    void setOwnerID( std::string id )
    {
        this->m_ownerID = id;
    }

    /**
     * Set quote text.
     * @param text new value.
     **/
    void setQuoteText( std::string text )
    {
        this->m_quoteText = text;
    }

    /**
     * Set number of sentence begin.
     **/
    void setSentenceBegin ( int number )
    {
        this->m_bookSentenceBegin  = number;
    }

    /**
     * Set number of sentence end.
     **/
    void setSentenceEnd ( int number )
    {
        this->m_bookSentenceEnd  = number;
    }

    /**
     * Set series text.
     * @param text new value.
     **/
    void setSeries( std::string text )
    {
        this->m_bookSeries = text;
    }


    /**
     * quote keywords. Separated by commas.
     * Example: "Umkehr, Zöllner, Nachfolge"
     **/
    std::vector<std::string> m_quoteKeywords;    
    
    
private:


    /**
     * book series name
     * Example: "Bibel"
     **/
    std::string m_bookSeries;

    /**
     * book name
     * Example: "Lukas"
     **/
    std::string m_bookTitle;

    /**
     * book chapter quote begin.
     * Example: "5"
     **/
    int m_bookChapterBegin;

    /**
     *  book sentence quote begin.
     * Example: "27"
     **/
    int m_bookSentenceBegin;

    /**
     * book chapter quote end
     * Example: "5"
     **/
    int m_bookChapterEnd;

    /**
     *  book sentence quote end
     * Example: "27"
     **/
    int m_bookSentenceEnd;

    /**
     * The edition id.
     **/
    std::string m_editionID;


    /**
     * The id of this quote.
     **/
    std::string m_ID;

    /**
     * Id of the owner of thes quote.
     * Example: "27"
     **/
    std::string m_ownerID;

    /**
     * If this value "true" then it's not visible for other user.
     **/
    bool m_isPrivateData;

    /**
     * quote note.
     * Example: "Eine kurze Notiz."
     **/
    std::string m_note;


    /**
     * quote text.
     * Example: "Und nach diesem ging er hinaus und sah einen Zöllner, mit
     * Namen Levi, [...]".
     **/
    std::string m_quoteText;

    /**
     * Search and replace function.
     * @param rep search string
     * @param rep replace string
     * @param rep original string
     * @return string with replacements
     **/
    string strReplace (string rep, string wit, string in);

    /**
     * Return a copy of the string with all the cased characters converted to
     * lowercase.
     **/
    string lowercase ( string keywords );
    
    
    /**
     * Mapping bible books name of bibleserver.com
     */
    map<string, string> BibleserverComNames;
};




#endif
