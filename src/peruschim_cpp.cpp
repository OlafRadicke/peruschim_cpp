#include <tnt/tntnet.h>
#include <tnt/configurator.h>
#include <string>
#include <cxxtools/log.h>
#include "./models/Config.h"


#include "Poco/Logger.h"
#include "Poco/AsyncChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/Message.h"

log_define("PERUSCHIM")



int main ( int argc, char* argv[] )
{
    try
    {

        Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
        Poco::Logger::root().setChannel(pCons);
//         Poco::AutoPtr<Poco::AsyncChannel> pAsync(new Poco::AsyncChannel(pCons));
//         Poco::Logger::root().setChannel(pAsync);


        Poco::Logger& logger = Poco::Logger::get("TestLogger");
        logger.setLevel(Poco::Message::PRIO_ERROR);


        logger.information("This is an informational message");
        logger.warning("This is a warning message");



        Config& config = Config::it();
        config.read();

        log_init(config.logging());

        tnt::Tntnet app;
        tnt::Configurator tntConfigurator(app);
        tntConfigurator.setSessionTimeout ( config.sessionTimeout() );

        app.listen( config.appIp(), config.appPort() );

        // configure static stuff
        app.mapUrl("^/resources/(.*)", "resources")
           .setPathInfo("resources/$1");
        app.mapUrl("^/favicon.ico$", "resources")
           .setPathInfo("resources/favicon.ico");
        app.mapUrl("^/feed-icon.png$", "resources")
           .setPathInfo("resources/feed-icon.png");


        // special pages
        app.mapUrl( "^/(.*)$", "$1" );
        app.mapUrl( "^/$", "home" );
        app.mapUrl( "^/rss.xml", "RSSfeedView" );

        // mvc stuff
        app.mapUrl( "^/(.*)$", "$1Controller" );
        app.mapUrl( "^/(.*)$", "$1View" );

        std::cout << "peruschim cpp is started and run on http://" << config.appIp()
            << ":" <<  config.appPort() << "/" << std::endl;
        log_info("starting PERUSCHIM");
        log_info(
            "peruschim cpp is started and run on http://" <<  config.appIp() \
            << ":" <<  config.appPort() << "/"
        );

        logger.error( "###### Only a test error!!!! ####");
        logger.information("### now: exicute app.run()!!!");

        app.run();
    } catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
}
