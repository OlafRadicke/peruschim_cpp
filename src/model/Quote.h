#ifndef QUOTE_H
#define QUOTE_H 

#include <string>
#include <vector>
#include "DatabaseProxy.h"
#include "Edition.h"

# define DEBUG std::cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR std::cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


class Quote
{
    
public:
    /**
     * Constructor init strings.
     **/
    Quote():
//         m_ID(""),
//         m_editionID(""),
//         m_bookSeries(""),
//         m_bookTitle(""),
//         m_bookChapterBegin(0),
//         m_bookSentenceBegin(0),
//         m_bookChapterEnd(0),
//         m_bookSentenceEnd(0),
//         m_quoteKeywords(),
//         m_note(""),
//         m_ownerID("")
        allBibleBooks()
    {
        allBibleBooks.push_back("1. Mose");
        allBibleBooks.push_back("2. Mose");
        allBibleBooks.push_back("3. Mose");
        allBibleBooks.push_back("4. Mose");
        allBibleBooks.push_back("5. Mose");
        allBibleBooks.push_back("Josua");
        allBibleBooks.push_back("Richter");
        allBibleBooks.push_back("Rut");
        allBibleBooks.push_back("1. Samuel");
        allBibleBooks.push_back("2. Samuel");
        allBibleBooks.push_back("1. Könige");
        allBibleBooks.push_back("2. Könige");
        allBibleBooks.push_back("1. Chronik");
        allBibleBooks.push_back("2. Chronik");
        allBibleBooks.push_back("Esra");
        allBibleBooks.push_back("Nehemia");
        allBibleBooks.push_back("Tobit");
        allBibleBooks.push_back("Judit");
        allBibleBooks.push_back("Ester");
        allBibleBooks.push_back("1. Makkabäer");
        allBibleBooks.push_back("2. Makkabäer");
        allBibleBooks.push_back("3. Makkabäer");
        allBibleBooks.push_back("4. Makkabäer");
        allBibleBooks.push_back("Ijob");
        allBibleBooks.push_back("Psalmen");
        allBibleBooks.push_back("Sprichwörter");
        allBibleBooks.push_back("Kohelet");
        allBibleBooks.push_back("Hoheslied");
        allBibleBooks.push_back("Weisheit");
        allBibleBooks.push_back("Jesus Sirach");
        allBibleBooks.push_back("Gebet des Manasse");
        allBibleBooks.push_back("Psalmen Salomos");
        allBibleBooks.push_back("Klagelieder Jeremias");
        allBibleBooks.push_back("Jesaja");
        allBibleBooks.push_back("Jeremia");
        allBibleBooks.push_back("Ezechiel");
        allBibleBooks.push_back("Baruch");
        allBibleBooks.push_back("Brief des Jeremia");
        allBibleBooks.push_back("Daniel");
        allBibleBooks.push_back("Hosea");
        allBibleBooks.push_back("Joel");
        allBibleBooks.push_back("Amos");
        allBibleBooks.push_back("Obadja");
        allBibleBooks.push_back("Jona");
        allBibleBooks.push_back("Micha");
        allBibleBooks.push_back("Nahum");
        allBibleBooks.push_back("Habakuk");
        allBibleBooks.push_back("Zefanja");
        allBibleBooks.push_back("Haggai");
        allBibleBooks.push_back("Sacharja");
        allBibleBooks.push_back("Maleachi");
        allBibleBooks.push_back("Matthäus");
        allBibleBooks.push_back("Markus");
        allBibleBooks.push_back("Lukas");
        allBibleBooks.push_back("Johannes");
        allBibleBooks.push_back("Apostelgeschichte");
        allBibleBooks.push_back("Römer");
        allBibleBooks.push_back("1. Korinther");
        allBibleBooks.push_back("2. Korinther");
        allBibleBooks.push_back("Galater");
        allBibleBooks.push_back("Epheser");
        allBibleBooks.push_back("Philipper");
        allBibleBooks.push_back("Kolosser");
        allBibleBooks.push_back("1. Thessalonicher");
        allBibleBooks.push_back("2. Thessalonicher");
        allBibleBooks.push_back("1. Timotheus");
        allBibleBooks.push_back("2. Timotheus");
        allBibleBooks.push_back("Titus");
        allBibleBooks.push_back("Philemon");
        allBibleBooks.push_back("Hebräer");
        allBibleBooks.push_back("Jakobus");
        allBibleBooks.push_back("1. Petrus");
        allBibleBooks.push_back("2. Petrus");
        allBibleBooks.push_back("1. Johannes");
        allBibleBooks.push_back("2. Johannes");
        allBibleBooks.push_back("3. Johannes");
        allBibleBooks.push_back("Judas");
        allBibleBooks.push_back("Offenbarung");
        
    };
        
    vector<std::string> allBibleBooks;
    
    /**
     * Get id of edition.
     **/
    std::string getEditionID()
    {
        return this->m_editionID;
    }
    
    /**
     * Get title of book.
     **/
    std::string getBookTitle()
    {
        return this->m_bookTitle;
    }
       
    /**
     * Get number of chapter begin.
     **/
    int getChapterBegin()
    {
        return this->m_bookChapterBegin;
    }    
    
    /**
     * Set id of the owner.
     **/
    std::string getOwnerID()
    {
        return this->m_ownerID;
    }    
    
    /**
     * get visible policy.
     **/
    bool isPrivateData( )
    {
        return this->m_isPrivateData;
    }      
    
    /**
     * Get number of sentence begin.
     **/
    int setSentenceBegin ( )
    {
        return this->m_bookSentenceBegin;
    } 
    
    /**
     * Get number of chapter end.
     **/
    int getChapterEnd()
    {
        return this->m_bookChapterEnd;
    } 
    
    
    /**
     * Get id of this quote.
     **/    
    std::string setID( ) {
        return this->m_ID;
    }       
    
    /**
     * Set Note.
     **/
    std::string getNote( )
    {
        return this->m_note;
    }
    
    /**
     * Get number of sentence end.
     **/
    int getSentenceEnd ( )
    {
        return this->m_bookSentenceEnd;
    } 
    
    /**
     * Get quote text.
     **/
    std::string getQuoteText()
    {
        return this->m_quoteText;
    }
    
    /**
     * Save date as new data set in database.
     **/
    void saveAsNew();
    
    
    /**
     * Save date update in in database..
     **/
    void saveUpdate() {}    
    
    // sets ====================================================
    
    /**
     * Set id of edition.
     **/
    void setEditionID( std::string id )
    {
        this->m_editionID = id;
    } 
    
    /**
     * Set id of the owner.
     **/
    void setOwnerID( std::string id )
    {
        this->m_ownerID = id;
    }
    
    /**
     * Set visible policy.
     **/
    void setIsPrivateData( bool visible )
    {
        this->m_isPrivateData = visible;
    }   
    
    /**
     * Set title of book.
     **/
    void setBookTitle( std::string title )
    {
        this->m_bookTitle = title;
    } 
    
    /**
     * Set keywords.
     * @param keywords strin with comma separated label values
     **/
    void setKeywords( std::string keywords ) ;
    
    /**
     * Set number of chapter begin.
     **/
    void setChapterBegin( int number )
    {
        this->m_bookChapterBegin = number;
    }
    
    /**
     * Set number of sentence begin.
     **/
    void setSentenceBegin ( int number )
    {
        this->m_bookSentenceBegin  = number;
    }
    
    /**
     * Set number of chapter end.
     **/
    void setChapterEnd( int number )
    {
        this->m_bookChapterEnd = number;
    }
    
    /**
     * Set id of this quote.
     **/    
    void setID( string id ) {
        this->m_ID= id;
    }
    
    /**
     * Set Note.
     **/
    void setNote( std::string note )
    {
        this->m_note = note;
    } 
    
    /**
     * Set number of sentence end.
     **/
    void setSentenceEnd ( int number )
    {
        this->m_bookSentenceEnd  = number;
    } 
    
    /**
     * Set quote text.
     * @param text new value.
     **/
    void setQuoteText( std::string text )
    {
        this->m_quoteText = text;
    }    

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
     * quote keywords. Separated by commas.
     * Example: "Umkehr, Zöllner, Nachfolge"
     **/
    std::vector<std::string> m_quoteKeywords;

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



};

#endif 