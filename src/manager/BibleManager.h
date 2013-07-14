/*
 * Copyright (C) 2013 Tommi Maekitalo
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * is provided AS IS, WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, and
 * NON-INFRINGEMENT.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
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

