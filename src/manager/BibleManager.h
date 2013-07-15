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
#include <models/Quote.h>

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

    std::string getBibleserverComURL(const std::string& bookTitle, unsigned bookChapterBegin) const;
    std::string getBibleserverComURL(const Quote& quote) const
    { return getBibleserverComURL(quote.getBookTitle(), quote.getChapterBegin()); }

private:
    class Impl;
    Impl* impl;
};

#endif // BIBLEMANAGER_H

