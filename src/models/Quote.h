/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright
* Copyright (C) 2013  Olaf Radicke <briefkasten@olaf-rdicke.de>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or later
* version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <vector>

#include "Edition.h"



class Quote
{
    friend class QuoteManager;

public:
    /**
     * Constructor.
     **/
    Quote();

    /**
     * Get title of book.
     **/
    const std::string& getBookTitle() const
    {
        return this->m_bookTitle;
    }

    /**
     * Get number of chapter begin.
     **/
    unsigned getChapterBegin() const
    {
        return this->m_bookChapterBegin;
    }

    /**
     * Get number of chapter end.
     **/
    unsigned getChapterEnd() const
    {
        return this->m_bookChapterEnd;
    }

    /**
     * Get id of edition.
     **/
    unsigned long getEditionID() const
    {
        return this->m_editionID;
    }

    /**
     * Get id of this quote.
     **/
    unsigned long getID( ) const {
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
    const std::string& getNote() const
    {
        return this->m_note;
    }

    /**
     * get id of the owner.
     **/
    unsigned long  getOwnerID()
    {
        return this->m_ownerID;
    }

    /**
     * Get quote text.
     **/
    const std::string& getQuoteText() const
    {
        return this->m_quoteText;
    }

    /**
     * Get number of sentence begin.
     **/
    unsigned getSentenceBegin() const
    {
        return this->m_bookSentenceBegin;
    }

    /**
     * Get number of sentence end.
     **/
    unsigned getSentenceEnd() const
    {
        return this->m_bookSentenceEnd;
    }

    /**
     * Set data of edition.
     **/
    const Edition& getTmpEditionData() const
    {
        return this->tmpEditionData;
    }

    /**
     * get visible policy.
     **/
    bool isPrivateData() const
    {
        return this->m_isPrivateData;
    }

    // sets ====================================================

    /**
     * Set title of book.
     **/
    void setBookTitle(const std::string& title )
    {
        this->m_bookTitle = title;
    }

    /**
     * Set number of chapter begin.
     **/
    void setChapterBegin( unsigned number )
    {
        this->m_bookChapterBegin = number;
    }

    /**
     * Set number of chapter end.
     **/
    void setChapterEnd( unsigned number )
    {
        this->m_bookChapterEnd = number;
    }

    /**
     * Set data of edition.
     **/
    void setTmpEditionData( Edition editionData )
    {
        this->tmpEditionData = editionData;
    }

    /**
     * Set id of edition.
     **/
    void setEditionID( unsigned long id )
    {
        this->m_editionID = id;
    }

    /**
     * Set id of this quote.
     **/
    void setID( unsigned long id ) {
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
     * @param keywords string with comma separated label values
     **/
    void setKeywords( const std::string& keywords ) ;

    /**
     * Set keywords.
     * @param keywordList list of keywors
     **/
    void setKeywords( const std::vector<std::string>& keywordList ) {
        m_quoteKeywords = keywordList;
    };

    /**
     * Set Note.
     **/
    void setNote( const std::string& note )
    {
        this->m_note = note;
    }

    /**
     * Set id of the owner.
     **/
    void setOwnerID( unsigned long id )
    {
        this->m_ownerID = id;
    }

    /**
     * Set quote text.
     * @param text new value.
     **/
    void setQuoteText( const std::string& text )
    {
        this->m_quoteText = text;
    }

    /**
     * Set number of sentence begin.
     **/
    void setSentenceBegin ( unsigned number )
    {
        this->m_bookSentenceBegin  = number;
    }

    /**
     * Set number of sentence end.
     **/
    void setSentenceEnd ( unsigned number )
    {
        this->m_bookSentenceEnd  = number;
    }

    /**
     * Set series text.
     * @param text new value.
     **/
    void setSeries( const std::string& text )
    {
        this->m_bookSeries = text;
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
    unsigned m_bookChapterBegin;

    /**
     *  book sentence quote begin.
     * Example: "27"
     **/
    unsigned m_bookSentenceBegin;

    /**
     * book chapter quote end
     * Example: "5"
     **/
    unsigned m_bookChapterEnd;

    /**
     *  book sentence quote end
     * Example: "27"
     **/
    unsigned m_bookSentenceEnd;

    /**
     * The edition id.
     **/
    unsigned long  m_editionID;

    /**
     * The id of this quote.
     **/
    unsigned long m_ID;

    /**
     * quote keywords.
     * Example: "Umkehr, Zöllner, Nachfolge"
     **/
    std::vector<std::string> m_quoteKeywords;

    /**
     * Id of the owner of thes quote.
     * Example: "27"
     **/
    unsigned long m_ownerID;

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
     * Buffer for edition data. Is use only by JSON-deserializeing.
     */
    Edition tmpEditionData;

};




#endif
