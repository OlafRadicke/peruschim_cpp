#include <tnt/tntnet.h>
#include <string>
#include <cxxtools/log.h>
#include "./models/Config.h"


log_define("PERUSCHIM")

int main ( int argc, char* argv[] )
{
    try
    {
        Config& config = Config::it();
        config.read();

        log_init(config.logging());

        tnt::Tntnet app;
        app.listen( config.appIp(), config.appPort() );
        app.mapUrl( "^/login", "login" ).setPathInfo( "login" );

        app.mapUrl( "^/(.*)$", "$1Controller" );
        app.mapUrl( "^/(.*)$", "$1View" );
        app.mapUrl( "^/$", "home" ).setPathInfo( "home" );

        app.mapUrl( "^/(.*)$", "$1" );

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
