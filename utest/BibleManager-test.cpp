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

#include "cxxtools/unit/testsuite.h"
#include "cxxtools/unit/registertest.h"
#include <manager/BibleManager.h>

class BibleManagerTest : public cxxtools::unit::TestSuite
{
public:
    BibleManagerTest()
        : cxxtools::unit::TestSuite("BibleManager")
    {
        registerMethod("bibleBooks", *this, &BibleManagerTest::bibleBooks);
        registerMethod("bibleserverComURL", *this, &BibleManagerTest::bibleserverComURL);
    }

    void bibleBooks()
    {
        BibleManager bibleManager;
        CXXTOOLS_UNIT_ASSERT_EQUALS(bibleManager.bibleBooksCount(), 78);
        CXXTOOLS_UNIT_ASSERT_EQUALS(bibleManager.bibleBook(0), "1. Mose");
        CXXTOOLS_UNIT_ASSERT_EQUALS(bibleManager.bibleBook(77), "Offenbarung");
    }

    void bibleserverComURL()
    {
        BibleManager bibleManager;
        CXXTOOLS_UNIT_ASSERT_EQUALS(
            bibleManager.getBibleserverComURL("EU", "2. Mose", 2),
            "http://www.bibleserver.com/text/EU/2.Mose/2"
        );
    CXXTOOLS_UNIT_ASSERT_EQUALS(
        bibleManager.getBibleserverComURL("ELB", "Ijob", 5),
        "http://www.bibleserver.com/text/ELB/Hiob/5");
    }
};

cxxtools::unit::RegisterTest<BibleManagerTest> register_BibleManagerTest;
