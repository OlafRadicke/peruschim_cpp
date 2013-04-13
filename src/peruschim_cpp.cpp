#include <tnt/tntnet.h>
#include <string>
#include "./models/Config.h"

int main ( int argc, char* argv[] )
{
    Config config;
    int port =  atoi(config.get( "APP-PORT" ).c_str());
    std::string ip_addr =  config.get( "APP-IP" );

    
    try
    {
        tnt::Tntnet app;
//         Configurator configurator( app );
        app.listen( ip_addr, port );
        app.mapUrl( "^/login", "login" ).setPathInfo( "login" );
        app.mapUrl( "^/home", "home" ).setPathInfo( "home" );
        app.mapUrl( "^/newaccount", "newaccount" ).setPathInfo( "newaccount" );
        app.mapUrl( "^/newquote", "newquote" ).setPathInfo( "newquote" );
        app.mapUrl( "^/$", "home" ).setPathInfo( "home" );
        app.mapUrl( "^/(.*)$", "$1" );
        
        std::cout << "peruschim cpp is started and run on http://" <<  ip_addr \
            << ":" <<  port << "/" << std::endl;
        app.run();
    } catch ( const std::exception& e )
    {
        std::cerr << e.what() << std::endl;
    }
}