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

#ifndef KEYWORDREGISTER_H
#define KEYWORDREGISTER_H

#include <string>
#include <vector>


/**
 * This class stor data of a Kexword.
 **/
class KeywordData {

public:
    KeywordRegister ():
        m_id(""),
        m_quote_id(""),
        m_title("") {};

private:

    /**
     * ID of Keyword.
     **/
    string      m_id;

    /**
     * ID of quote where the keyword is linked.
     **/
    string      m_quote_id;

    /**
     * The title or name from the keyword.
     **/
    string      m_title;
}

#endif
