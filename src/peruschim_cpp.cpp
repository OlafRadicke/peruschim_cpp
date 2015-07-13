/**
* @author Olaf Radicke <briefkasten@olaf-rdicke.de>
* @date 2013
* @copyright GNU Affero General Public License
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

#include <Core/models/Config.h>
#include <Core/initcomponent.h>
#include <RouteReverse/initcomponent.h>
#include <Core/manager/TableManager.h>

#include <tnt/tntnet.h>
#include <tnt/configurator.h>
#include <string>
#include <cxxtools/log.h>
#include <cstdlib>

log_define("PERUSCHIM")

int main ( int argc, char* argv[] )
{
    try
    {

        /* initialize random seed: */
        srand (time(NULL));

        Config& config = Config::it();
        config.read();

        log_init(config.logging());


        // Data base update check:
        TableManager tabM;
        if( tabM.update() == false ){
            log_error("Table update was failed! Abortion...");
            std::cerr << "Table update was failed! Abortion..." << std::endl;
            exit (EXIT_FAILURE);
        }

        // Init Application Server
        tnt::Tntnet app;
        tnt::Configurator tntConfigurator(app);
        tntConfigurator.setSessionTimeout ( config.sessionTimeout() );
        app.listen( config.appIp(), config.appPort() );



        // configure static stuff
        app.mapUrl("^/Core/resources/(.*)", "resources")
           .setPathInfo("Core/resources/$1");
        app.mapUrl("^/Core/favicon.ico$", "resources")
           .setPathInfo("Core/resources/favicon.ico");

//         app.mapUrl("^/Core/feed-icon.png$", "resources")
//            .setPathInfo("Core/resources/feed-icon.png");

        // special pages
        // 1 to 1 rout
        app.mapUrl( "^/(.*)$", "$1" );
        // default route for /
        app.mapUrl( "^/$", "home" );

        // controller rout for SessionForm token check.
        app.mapUrl( "^/(.*)", "SessionForm::Controller" );
        // controller rout for SessionForm token check.
        app.mapUrl( "^/SessionForm/NoAvailabeToken", "NoAvailabeTokenView" );

        // mvc stuff
        app.mapUrl( "^/(.*)$", "$1Controller" );
        app.mapUrl( "^/(.*)$", "$1View" );


        RouteReverse::initcomponent( app );
        Core::initcomponent( app );


        std::cout << "peruschim cpp is started and run on http://" << config.appIp()
            << ":" <<  config.appPort() << "/" << std::endl;
        log_info("starting PERUSCHIM");
        log_info(
            "peruschim cpp is started and run on http://" <<  config.appIp() \
            << ":" <<  config.appPort() << "/"
        );

        app.run();
    } catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
}
