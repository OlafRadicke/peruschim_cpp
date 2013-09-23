/*
* Copyright (C) 2013 Tommi Maekitalo
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

#include <cxxtools/mutex.h>
#include <map>
#include <sstream>

#include <Core/manager/BibleManager.h>

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

    std::string getBibleserverComURL(
        const std::string& bibleTrans,
        const std::string& bookTitle,
        unsigned bookChapterBegin
    ) const;

private:
    Impl()
    { }

    Impl(const Impl&);
    Impl& operator= (const Impl&);

    void initializeBibleBooks();
    void initializeComServer();

    BibleManager::BibleBooks bibleBooks;
    std::map<std::string, std::string> bibleserverComNames;
};

void BibleManager::Impl::initializeBibleBooks()
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

    bibleBooks.insert(bibleBooks.end(), allBibleBooks, allBibleBooks + sizeof(allBibleBooks) / sizeof(const char*));
}

void BibleManager::Impl::initializeComServer()
{
    // the matching with book name of bibleserver.com
    bibleserverComNames["1. Mose"] = "1.Mose";
    bibleserverComNames["2. Mose"] = "2.Mose";
    bibleserverComNames["3. Mose"] = "3.Mose";
    bibleserverComNames["4. Mose"] = "4.Mose";
    bibleserverComNames["5. Mose"] = "5.Mose";
    bibleserverComNames["Josua"] = "Josua";
    bibleserverComNames["Richter"] = "Richter";
    bibleserverComNames["Rut"] = "Rut";
    bibleserverComNames["1. Samuel"] = "1.Samuel";
    bibleserverComNames["2. Samuel"] = "2.Samuel";
    bibleserverComNames["1. Könige"] = "1.Könige";
    bibleserverComNames["2. Könige"] = "2.Könige";
    bibleserverComNames["1. Chronik"] = "1.Chronik";
    bibleserverComNames["2. Chronik"] = "2.Chronik";
    bibleserverComNames["Esra"] = "Esra";
    bibleserverComNames["Nehemia"] = "Nehemia";
    bibleserverComNames["Tobit"] = "Tobit";
    bibleserverComNames["Judit"] = "Judit";
    bibleserverComNames["Ester"] = "Esther";
    bibleserverComNames["1. Makkabäer"] = "1.Makkabäer";
    bibleserverComNames["2. Makkabäer"] = "2.Makkabäer";
    bibleserverComNames["3. Makkabäer"] = "";
    bibleserverComNames["4. Makkabäer"] = "";
    bibleserverComNames["Ijob"] = "Hiob";
    bibleserverComNames["Psalmen"] = "Psalmen";
    bibleserverComNames["Sprichwörter"] = "Sprüche";
    bibleserverComNames["Kohelet"] = "Prediger";
    bibleserverComNames["Hoheslied"] = "Hoheslied";
    bibleserverComNames["Weisheit"] = "Weisheit";
    bibleserverComNames["Jesus Sirach"] = "Jesus Sirach";
    bibleserverComNames["Gebet des Manasse"] = "";
    bibleserverComNames["Psalmen Salomos"] = "";
    bibleserverComNames["Klagelieder Jeremias"] = "Klagelieder";
    bibleserverComNames["Jesaja"] = "Jesaja";
    bibleserverComNames["Jeremia"] = "Jeremia";
    bibleserverComNames["Ezechiel"] = "Hesekiel";
    bibleserverComNames["Baruch"] = "Baruch";
    bibleserverComNames["Brief des Jeremia"] = "";
    bibleserverComNames["Daniel"] = "Daniel";
    bibleserverComNames["Hosea"] = "Hosea";
    bibleserverComNames["Joel"] = "Joel";
    bibleserverComNames["Amos"] = "Amos";
    bibleserverComNames["Obadja"] = "Obadja";
    bibleserverComNames["Jona"] = "Jona";
    bibleserverComNames["Micha"] = "Micha";
    bibleserverComNames["Nahum"] = "Nahum";
    bibleserverComNames["Habakuk"] = "Habakuk";
    bibleserverComNames["Zefanja"] = "Zefanja";
    bibleserverComNames["Haggai"] = "Haggai";
    bibleserverComNames["Sacharja"] = "Sacharja";
    bibleserverComNames["Maleachi"] = "Maleachi";
    bibleserverComNames["Matthäus"] = "Matthäus";
    bibleserverComNames["Markus"] = "Markus";
    bibleserverComNames["Lukas"] = "Lukas";
    bibleserverComNames["Johannes"] = "Johannes";
    bibleserverComNames["Apostelgeschichte"] = "Apostelgeschichte";
    bibleserverComNames["Römer"] = "Römer";
    bibleserverComNames["1. Korinther"] = "1.Korinther";
    bibleserverComNames["2. Korinther"] = "2.Korinther";
    bibleserverComNames["Galater"] = "Galater";
    bibleserverComNames["Epheser"] = "Epheser";
    bibleserverComNames["Philipper"] = "Philipper";
    bibleserverComNames["Kolosser"] = "Kolosser";
    bibleserverComNames["1. Thessalonicher"] = "1.Thessalonicher";
    bibleserverComNames["2. Thessalonicher"] = "2.Thessalonicher";
    bibleserverComNames["1. Timotheus"] = "1.Timotheus";
    bibleserverComNames["2. Timotheus"] = "2.Timotheus";
    bibleserverComNames["Titus"] = "Titus";
    bibleserverComNames["Philemon"] = "Philemon";
    bibleserverComNames["Hebräer"] = "Hebräer";
    bibleserverComNames["Jakobus"] = "Jakobus";
    bibleserverComNames["1. Petrus"] = "1.Petrus";
    bibleserverComNames["2. Petrus"] = "2.Petrus";
    bibleserverComNames["1. Johannes"] = "1.Johannes";
    bibleserverComNames["2. Johannes"] = "2.Johannes";
    bibleserverComNames["3. Johannes"] = "3.Johannes";
    bibleserverComNames["Judas"] = "Judas";
    bibleserverComNames["Offenbarung"] = "Offenbarung";
}

BibleManager::Impl& BibleManager::Impl::getInstance()
{
    static Impl impl;
    static bool initialized;
    static cxxtools::Mutex mutex;

    cxxtools::MutexLock lock(mutex);
    if (!initialized)
    {
        impl.initializeBibleBooks();
        impl.initializeComServer();
        initialized = true;
    }

    return impl;
}

// std::string BibleManager::Impl::getBibleserverComURL(
//     const std::string& bookTitle,
//     unsigned bookChapterBegin) const
// {
//     std::string t = bookTitle;
//     std::map<std::string, std::string>::const_iterator it =
//         bibleserverComNames.find(bookTitle);
//     if (it != bibleserverComNames.end())
//         t = it->second;
//
//     std::ostringstream s;
//     s << "http://www.bibleserver.com/text/EU/"
//       << t
//       << '/'
//       << bookChapterBegin;
//
//     return s.str();
// }

std::string BibleManager::Impl::getBibleserverComURL(
    const std::string& bibleTrans,
    const std::string& bookTitle,
    unsigned bookChapterBegin) const
{
    std::string t = bookTitle;
    std::map<std::string, std::string>::const_iterator it =
        bibleserverComNames.find(bookTitle);
    if (it != bibleserverComNames.end())
        t = it->second;

    std::ostringstream s;
    s << "http://www.bibleserver.com/text/"
      << bibleTrans
      << "/"
      << t
      << '/'
      << bookChapterBegin;

    return s.str();
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

// std::string BibleManager::getBibleserverComURL(
//     const std::string& bookTitle,
//     unsigned bookChapterBegin) const
// {
//     return impl->getBibleserverComURL(
//         bookTitle,
//         bookChapterBegin
//     );
// }

std::string BibleManager::getBibleserverComURL(
    const std::string& bibleTrans,
    const std::string& bookTitle,
    unsigned bookChapterBegin) const
{
    return impl->getBibleserverComURL(
        bibleTrans,
        bookTitle,
        bookChapterBegin
    );
}
