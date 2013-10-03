#include <tnt/tntnet.h>
#include <tnt/configurator.h>
#include <string>
#include <cxxtools/log.h>
#include <Core/models/Config.h>
#include <Core/manager/initcomponent.h>
#include <RouteReverse/manager/initcomponent.h>


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
