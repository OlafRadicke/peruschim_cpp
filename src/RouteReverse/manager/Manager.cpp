/*
* Copyright (C) 2013 Olaf Radicke <briefkasten@olaf-radicke.de>
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



#include <string>
#include <map>
#include <iostream>
#include <cxxtools/log.h>
#include <cxxtools/mutex.h>
#include <RouteReverse/manager/Manager.h>


namespace RouteReverse
{


log_define("RouteReverse.Manager")

std::map< std::string, std::string > Manager::reverseMAP = std::map< std::string, std::string >();


// A --------------------------------------------------------------------------


void Manager::addRoute( URLData &urlData, tnt::Tntnet &app ) {


    if ( urlData.urlRegEx != "" && urlData.componentName != "" ) {
        if ( urlData.componentPathInfo != "" ) {
            app.mapUrl( urlData.urlRegEx, urlData.componentName )
            .setPathInfo( urlData.componentPathInfo );
        } else {
            app.mapUrl( urlData.urlRegEx, urlData.componentName );
        }
    }

    if ( urlData.reverseRoute != "") {
        if ( Manager::reverseMAP.count( urlData.componentName ) > 0 ) {
            std::string errorText = "[" + std::string(__FILE__) + " "
                + cxxtools::convert<std::string>( __LINE__ ) + "] "
                + " the url " + urlData.componentName
                + " is all ready set as reverse route!";
            log_debug( errorText );
            throw errorText.c_str();
        }
        static cxxtools::Mutex mutex;
        cxxtools::MutexLock lock(mutex);
        Manager::reverseMAP[ urlData.componentName ] = urlData.reverseRoute;
        log_debug( "List of know reverse routes: \n" <<
            RouteReverse::Manager::getAllReversesRoutes() );
    }
}


// G --------------------------------------------------------------------------

std::string Manager::getAllReversesRoutes(){

    std::string returnString;

    std::map< std::string, std::string >::iterator it;
    for (
        std::map< std::string, std::string >::iterator it=Manager::reverseMAP.begin();
        it!=Manager::reverseMAP.end();
        ++it
    ){
        returnString += it->first + " => " + it->second + "\n";
    }
    return returnString;
}


std::string  Manager::getLinkTo(
        std::string compunentName,
        const tnt::HttpRequest& request ){

    std::string targetURL;
    std::string returnURL;
    std::string currentURL = request.getUrl ();

    std::map<std::string, std::string>::const_iterator it =
        Manager::reverseMAP.find( compunentName );
    if (it != Manager::reverseMAP.end())
        targetURL = it->second;

    returnURL = targetURL;

    size_t pathDepth = std::count( currentURL.begin(), currentURL.end(), '/' );
    for ( unsigned int i = 1; i < pathDepth; i++){
        returnURL = "../" + returnURL;
    }

    return returnURL;
}

std::string  Manager::getAbsolutURL(
        std::string compunentName,
        const tnt::HttpRequest& request ){

    std::string targetURL;
    std::string returnURL;

    std::map<std::string, std::string>::const_iterator it =
        Manager::reverseMAP.find( compunentName );
    if (it != Manager::reverseMAP.end())
        targetURL = it->second;

    if ( request.isSsl() ) {
        returnURL = "https://" +request.getVirtualHost()
            + "/" + targetURL;
    } else{
        returnURL = "http://" +request.getVirtualHost()
            + "/" + targetURL;
    }
    return returnURL;
}

} // END namespace SessionForm




