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
        m_edition();
        m_bookSeries(""),
        m_bookTitle(""),
        m_bookChapterBegin(0),
        m_bookSentenceBegin(0),
        m_bookChapterEnd(0),
        m_bookSentenceEnd(0),
        m_quoteLabels(),
        m_note(""),
        allBibleBooks
        ( 
            "1. Mose",
            "2. Mose",
            "3. Mose",
            "4. Mose",
            "5. Mose",
            "Josua",
            "Richter",
            "Rut",
            "1. Samuel",
            "2. Samuel",
            "1. Könige",
            "2. Könige",
            "1. Chronik",
            "2. Chronik",
            "Esra",
            "Nehemia",
            "Tobit",
            "Judit",
            "Ester",
            "1. Makkabäer",
            "2. Makkabäer",
            "3. Makkabäer",
            "4. Makkabäer",
            "Ijob",
            "Psalmen",
            "Sprichwörter",
            "Kohelet",
            "Hoheslied",
            "Weisheit",
            "Jesus Sirach",
            "Gebet des Manasse",
            "Psalmen Salomos",
            "Klagelieder Jeremias",
            "Jesaja",
            "Jeremia",
            "Ezechiel",
            "Baruch",
            "Brief des Jeremia",
            "Daniel",
            "Hosea",
            "Joel",
            "Amos",
            "Obadja",
            "Jona",
            "Micha",
            "Nahum",
            "Habakuk",
            "Zefanja",
            "Haggai",
            "Sacharja",
            "Maleachi",
            "Matthäus",
            "Markus",
            "Lukas",
            "Johannes",
            "Apostelgeschichte",
            "Römer",
            "1. Korinther",
            "2. Korinther",
            "Galater",
            "Epheser",
            "Philipper",
            "Kolosser",
            "1. Thessalonicher",
            "2. Thessalonicher",
            "1. Timotheus",
            "2. Timotheus",
            "Titus",
            "Philemon",
            "Hebräer",
            "Jakobus",
            "1. Petrus",
            "2. Petrus",
            "1. Johannes",
            "2. Johannes",
            "3. Johannes",
            "Judas",
            "Offenbarung"
        )
    {};
        
    vector<std::string> allBibleBooks;
    
    /**
     * Get id of edition.
     **/
    long getEditionID()
    {
        return this->m_editionID;
    }
    
    /**
     * Get title of book.
     **/
    long getBookTitle()
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
     * Get number of sentence end.
     **/
    int setSentenceEnd ( )
    {
        return this->m_bookSentenceEnd;
    } 
    
    /**
     * Get quote text.
     **/
    std::string getQuoteText()
    {
        return this->quoteText;
    }
    
    /**
     * Save date in database..
     **/
    void save() {}
    
    // sets ====================================================
    
    /**
     * Set id of edition.
     **/
    void setEditionID( long id )
    {
        this->m_editionID = id;
    }
    
    /**
     * Set title of book.
     **/
    long getBookTitle( std::string title )
    {
        this->m_bookTitle = title;
    }
    
    /**
     * Set labels.
     * @param labels strin with comma separated values
     **/
    void setBookTitle( std::string labels )
    {
        m_quoteLabels.clear();
        int found;
        found = labels.find_first_of(separator);
        while(found != string::npos){
            if(found > 0){
                m_quoteLabels.push_back(labels.substr(0,found));
            }
            labels = labels.substr(found+1);
            found = labels.find_first_of(separator);
        }
        if(labels.length() > 0){
            m_quoteLabels.push_back(labels);
        }
    }     
    
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
        this->quoteText = $text;
    }    

private:    
    
    /**
     * The edition id.
     **/
    long m_editionID;
    
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
     * quote labels. Separated by commas.
     * Example: "Umkehr, Zöllner, Nachfolge"
     **/
    std::vector<std::string> m_quoteLabels;

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



}

#endif 