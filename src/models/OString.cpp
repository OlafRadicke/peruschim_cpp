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

#include <string>
#include <iostream>
#include <sstream>
#include "models/OString.h"

# define DEBUG cout << "[" << __FILE__ << ":" << __LINE__ << "] " <<
# define ERROR cerr << "[" << __FILE__ << ":" << __LINE__ << "] " <<


std::string OString::IntToStr( const int number )
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

std::string unsignedLongToStr( unsigned long number )
{
   std::stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

std::string OString::LowerCase ( std::string keywords ) {
    keywords = StrReplace ( "A", "a", keywords);
    keywords = StrReplace ( "B", "b", keywords);
    keywords = StrReplace ( "C", "c", keywords);
    keywords = StrReplace ( "D", "d", keywords);
    keywords = StrReplace ( "E", "e", keywords);
    keywords = StrReplace ( "F", "f", keywords);
    keywords = StrReplace ( "G", "g", keywords);
    keywords = StrReplace ( "H", "h", keywords);
    keywords = StrReplace ( "I", "i", keywords);
    keywords = StrReplace ( "J", "j", keywords);
    keywords = StrReplace ( "K", "k", keywords);
    keywords = StrReplace ( "L", "l", keywords);
    keywords = StrReplace ( "M", "m", keywords);
    keywords = StrReplace ( "N", "n", keywords);
    keywords = StrReplace ( "O", "o", keywords);
    keywords = StrReplace ( "P", "p", keywords);
    keywords = StrReplace ( "Q", "q", keywords);
    keywords = StrReplace ( "R", "r", keywords);
    keywords = StrReplace ( "S", "s", keywords);
    keywords = StrReplace ( "T", "t", keywords);
    keywords = StrReplace ( "U", "u", keywords);
    keywords = StrReplace ( "V", "v", keywords);
    keywords = StrReplace ( "W", "w", keywords);
    keywords = StrReplace ( "X", "x", keywords);
    keywords = StrReplace ( "Y", "y", keywords);
    keywords = StrReplace ( "Z", "z", keywords);
    keywords = StrReplace ( "Ä", "ä", keywords);
    keywords = StrReplace ( "Ö", "ö", keywords);
    keywords = StrReplace ( "Ü", "ü", keywords);
    return keywords;
}

std::string OString::StrReplace (
    const std::string s_string,
    const std::string r_string,
    const std::string i_string
) {
  int pos;
  // return string
  std::string b_string = i_string;
  while (true) {
    pos = b_string.find(s_string);
    if (pos == -1) {
      break;
    } else {
      b_string.erase(pos, s_string.length());
      b_string.insert(pos, r_string);
    }
  }
  return b_string;
}
