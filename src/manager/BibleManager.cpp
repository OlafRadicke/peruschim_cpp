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

#include <manager/BibleManager.h>
#include <cxxtools/mutex.h>

////////////////////////////////////////////////////////////////////////
// BibleManager::Impl
//
class BibleManager::Impl
{
public:
    static Impl& getInstance();

    BibleBooksIterator bibleBooksBegin() const
    {
        return bibleBooks.begin();
    }

    BibleBooksIterator bibleBooksEnd() const
    {
        return bibleBooks.end();
    }

    unsigned bibleBooksCount() const
    {
        return bibleBooks.size();
    }

    const std::string& bibleBook(unsigned n) const
    {
        return bibleBooks.at(n);
    }

private:
    Impl()
    { }

    Impl(const Impl&);
    Impl& operator= (const Impl&);

    BibleManager::BibleBooks bibleBooks;
};

BibleManager::Impl& BibleManager::Impl::getInstance()
{
    static Impl impl;
    static bool initialized;
    static cxxtools::Mutex mutex;

    cxxtools::MutexLock lock(mutex);
    if (!initialized)
    {
        static const char* allBibleBooks[] = {
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
          "Offenbarung" };

        impl.bibleBooks.insert(impl.bibleBooks.end(), allBibleBooks, allBibleBooks + sizeof(allBibleBooks) / sizeof(const char*));
    }

    return impl;
}

////////////////////////////////////////////////////////////////////////
// methods of BibleManager
//
BibleManager::BibleManager()
    : impl(&Impl::getInstance())
{
}

BibleManager::BibleBooksIterator BibleManager::bibleBooksBegin() const
{
    return impl->bibleBooksBegin();
}

BibleManager::BibleBooksIterator BibleManager::bibleBooksEnd() const
{
    return impl->bibleBooksEnd();
}

unsigned BibleManager::bibleBooksCount() const
{
    return impl->bibleBooksCount();
}

const std::string& BibleManager::bibleBook(unsigned n) const
{
    return impl->bibleBook(n);
}

