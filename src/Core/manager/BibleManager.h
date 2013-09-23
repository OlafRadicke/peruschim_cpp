/*
* Copyright (C) 2013 Tommi Maekitalo
*
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

#ifndef BIBLEMANAGER_H
#define BIBLEMANAGER_H

#include <string>
#include <vector>
#include <Core/models/Quote.h>

class BibleManager
{
public:
    BibleManager();

    typedef std::vector<std::string> BibleBooks;
    typedef BibleBooks::const_iterator BibleBooksIterator;

    BibleBooksIterator bibleBooksBegin() const;
    BibleBooksIterator bibleBooksEnd() const;
    unsigned bibleBooksCount() const;
    const std::string& bibleBook(unsigned n) const;

    /**
     * Get back a depth link to http://bibleserver.com
     * @arg bookTitle title of a bible book
     * @arg bookChapterBegin number of a chapter
     * @return link as string
     */
    std::string getBibleserverComURL(
        const std::string& bookTitle,
        unsigned bookChapterBegin
    ) const;

    /**
     * Get back a depth link to http://bibleserver.com
     * @arg bibleTrans type of bible translation.
     * @arg bookTitle title of a bible book
     * @arg bookChapterBegin number of a chapter
     * @return link as string
     */
    std::string getBibleserverComURL(
        const std::string& bibleTrans,
        const std::string& bookTitle,
        unsigned bookChapterBegin
    ) const;


    /**
     * Get back a depth link to http://bibleserver.com
     * @arg bibleTrans type of bible translation.
     * @arg quote a instance of class Quote with information about book and
     * chapter.
     * @return link as string
     */
    std::string getBibleserverComURL(
        const std::string& bibleTrans,
        const Quote& quote) const
    {
        return getBibleserverComURL(
            bibleTrans,
            quote.getBookTitle(),
            quote.getChapterBegin()
        );
    }

private:
    class Impl;
    Impl* impl;
};

#endif // BIBLEMANAGER_H

