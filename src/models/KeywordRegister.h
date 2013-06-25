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

#include <tntdb/connection.h>
#include <tntdb/connect.h>
#include <tntdb/result.h>
#include <tntdb/statement.h>

using namespace std;

/**
 * A helper class for store keyword name and count.
 **/
class KeywordCount {

public:
    /**
    * Name of keyword.
    **/
    string Name;

    /**
    * Count of keyword.
    **/
    string Count;

    KeywordCount () {
        this->Name = "";
        this->Count = "";
    }
};


/**
 * The class has methods for keyword operations.
 **/
class KeywordRegister {

public:

    /**
    * Get all used keywords.
    **/
    static vector<string> getAllKeywordTitles( void );

    /**
    * Get all used keywords with cound. Public keywords and own private user
    * keywords.
    * @arg owner_id login id.
    **/
    static vector<KeywordCount> getAllKeywordTitleAndCound( const unsigned long owner_id );

    /**
    * Get all used keywords with cound of public quotes.
    **/
    static vector<KeywordCount> getAllPubKeywordTitleAndCound( void );

    /**
    * Get only user own keywords.
    * keywords.
    * @arg owner_id login id.
    **/
    static vector<KeywordCount> getOwnKeywordTitleAndCound( const unsigned long owner_id );

private:


};

#endif
