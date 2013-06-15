#include <tnt/tntnet.h>
#include <string>
#include <cxxtools/log.h>
#include "./models/Config.h"


log_define("PERUSCHIM")

int main ( int argc, char* argv[] )
{
    Config config;
    int port =  atoi(config.get( "APP-PORT" ).c_str());
    std::string ip_addr =  config.get( "APP-IP" );
    log_init("PERUSCHIM.properties");

    try
    {
        tnt::Tntnet app;
//         Configurator configurator( app );
        app.listen( ip_addr, port );
        app.mapUrl( "^/login", "login" ).setPathInfo( "login" );

//         app.mapUrl( "^/edit_own_verses$", "EditOwnVersesController" ).setPathInfo( "EditOwnVersesController" );
//         app.mapUrl( "^/edit_own_verses$", "EditOwnVersesView" ).setPathInfo( "EditOwnVersesView" );
        app.mapUrl( "^/(.*)$", "$1Controller" );
        app.mapUrl( "^/(.*)$", "$1View" );
        app.mapUrl( "^/$", "home" ).setPathInfo( "home" );

        // ruft bei /keyword-detail/keyword die Komponente keyword-detail
        // auf und übergibt den Parameter "keywordp".
        // Mit 'request.getArg(0)' läst sich der Wert auslesen.
//         app.mapUrl("^/keyword-detail/(.*)", "keyword-detail").pushArg("$1");

        app.mapUrl( "^/(.*)$", "$1" );
        std::cout << "peruschim cpp is started and run on http://" <<  ip_addr \
            << ":" <<  port << "/" << std::endl;
        log_info("starting PERUSCHIM");
        app.run();
    } catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
}
