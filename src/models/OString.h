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

#ifndef OSTRING_H
#define OSTRING_H

#include <string>

/**
 * Support basic string operations.
 */
class OString {

public:

    /**
     * Convert int to string.
     * @param number a number.
     **/
    static std::string IntToStr( const int number );

        /**
     * Convert unsigned long number to string.
     * @param number a number.
     **/
    static std::string unsignedLongToStr( unsigned long number );

    /**
     * Return a copy of the string with all the cased characters converted to
     * lowercase.
     **/
    static std::string LowerCase ( const std::string  );

    /**
     * Search and replace function.
     * @param s_strin search string
     * @param r_string replace string
     * @param i_string original input string
     * @return string with replacements
     **/
    static std::string StrReplace (
        const std::string s_strin,
        const std::string r_string,
        const std::string i_string
    );

};


#endif
