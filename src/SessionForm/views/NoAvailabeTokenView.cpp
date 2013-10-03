////////////////////////////////////////////////////////////////////////
// SessionForm/views/NoAvailabeTokenView.cpp
// generated with ecppc
//

#include <tnt/ecpp.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <tnt/httpheader.h>
#include <tnt/http.h>
#include <tnt/data.h>
#include <tnt/componentfactory.h>
#include <cxxtools/log.h>
#include <stdexcept>

log_define("component.NoAvailabeTokenView")

// <%pre>
#include <Core/models/UserSession.h>
#line 2 "Core/views/parts/user-session.ecpp.html"

    #include <Core/models/Config.h>
    #include <RouteReverse/manager/Manager.h>

// </%pre>

namespace
{
class _component_ : public tnt::EcppComponent
{
    _component_& main()  { return *this; }

  protected:
    ~_component_();

  public:
    _component_(const tnt::Compident& ci, const tnt::Urlmapper& um, tnt::Comploader& cl);

    unsigned operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam);
};

static tnt::EcppComponentFactoryImpl<_component_> Factory("NoAvailabeTokenView");

static const char* rawData = "p\000\000\000t\000\000\000\355\000\000\000\001\001\000\000\002\001\000\000\003\001\000"
  "\000!\001\000\0003\001\000\000_\001\000\000p\001\000\000\234\001\000\000\251\001\000\000\261\001\000\000\265\001\000"
  "\000\310\001\000\000\327\001\000\000\363\001\000\000\035\002\000\000,\002\000\000J\002\000\000s\002\000\000\354\002"
  "\000\000\360\002\000\000\277\003\000\000$\007\000\000\317\007\000\000\014\010\000\000\034\010\000\000\n\n\n\n\n\n<!DO"
  "CTYPE HTML>\n<html>\n<head>\n    <title>PERUSCHHIM - Neuen Account anlegen</title>\n    <meta charset = \"UTF-8\" />"
  "\n    \n</head>\n<body>\n    \n\n\n    <div class=\"login-link\">\n\n        <a href=\"\">\n            Normale Ansic"
  "ht\n        </a>\n        <a href=\"\">\n            Mobilen Version\n        </a>\n        <br>\n        (ID:)\n    "
  "    <a href=\"\">Abmelden</a>\n<!--        <a href=\"http:///LogIn\">Anmelden</a> -->\n        <a href=\"\">Anmelden<"
  "/a>\n        <br>\n        <a href=\"\">\n            <img\n                src=\"\"\n                width=\"22\"\n "
  "               height=\"22\"\n                alt=\"rss-feed-icon\" />\n        </a>\n    </div>\n\n    \n<div id=\"h"
  "eader-logo\">\n    <a href=\"home\">\n        <div id=\"logo-black\">\n            <h1>PERUSCHIM</h1>\n        </div>"
  "\n        <div id=\"logo-blue\">\n            with C++/Tntnet\n        </div>\n    </a>\n</div>\n    <div class=\"cen"
  "terbox\">\n        <h1>Fehlerhafte Formularverarbeitung</h1>\n        <div class=\"feedback-box\">\n            <b>\n"
  "                Wenn sie diese Seite sehen ist etwas mit der Formularverarbeitung\n                schief gelaufen. D"
  "as tut mir leide! Folgende Ursachen k\303\266nnen der\n                Grund sein:\n            </b>\n            <ul"
  ">\n                <li>\n                    Das Formular wurde (versehentlich) zwei mal abgesendet in\n             "
  "       dem die Seite neu geladen haben.\n                </li>\n                <li>\n                    Es waren/si"
  "nd in mehreren Fenster das selbe Formular\n                    ge\303\266ffnet.\n                </li>\n             "
  "   <li>\n                    Das Formular stammt von einer Sitzung die bereits abgelaufen\n                    ist\n "
  "               </li>\n            </ul>\n        </div>\n    </div>\n\n    <p id=\"foot\">\n        PERUSCHIM ist fre"
  "ie Software. Den Sourcecode findest bei\n        <a href=\"https://github.com/OlafRadicke/peruschim_cpp\">github.com<"
  "/a>\n    </p>\n<!-- add your piwik Tracking Code and recompile the code. --></body>\n</html>\n";

// <%shared>
// </%shared>

// <%config>
// </%config>

#define SET_LANG(lang) \
     do \
     { \
       request.setLang(lang); \
       reply.setLocale(request.getLocale()); \
     } while (false)

_component_::_component_(const tnt::Compident& ci, const tnt::Urlmapper& um, tnt::Comploader& cl)
  : EcppComponent(ci, um, cl)
{
  // <%init>
  // </%init>
}

_component_::~_component_()
{
  // <%cleanup>
  // </%cleanup>
}

unsigned _component_::operator() (tnt::HttpRequest& request, tnt::HttpReply& reply, tnt::QueryParams& qparam)
{
  log_trace("NoAvailabeTokenView " << qparam.getUrl());

  tnt::DataChunks data(rawData);

#line 23 "SessionForm/views/NoAvailabeTokenView.ecpp"
  TNT_SESSION_SHARED_VAR(UserSession, userSession, ());   // <%session> UserSession userSession
  // <%cpp>
  reply.out() << data[0]; // \n\n\n\n
  reply.out() << data[1]; // \n\n<!DOCTYPE HTML>\n<html>\n<head>\n    <title>PERUSCHHIM - Neuen Account anlegen</title>\n    <meta charset = "UTF-8" />\n    
  // <& "style" ...
  { 
#line 32 "SessionForm/views/NoAvailabeTokenView.ecpp"
    tnt::QueryParams _tnt_cq0;
#line 32 "SessionForm/views/NoAvailabeTokenView.ecpp"
    callComp("style", request, reply, _tnt_cq0);
    // &>
  }
  reply.out() << data[2]; // \n</head>\n<body>\n    
  // <%include> Core/views/parts/user-session.ecpp.html
  reply.out() << data[3]; // \n
  reply.out() << data[4]; // \n
#line 7 "Core/views/parts/user-session.ecpp.html"
 RouteReverse::Manager routeReverseManager;

  reply.out() << data[5]; // \n    <div class="login-link">\n
#line 10 "Core/views/parts/user-session.ecpp.html"
 if ( userSession.isHandheldVersion() ) {

  reply.out() << data[6]; // \n        <a href="
#line 12 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( RouteReverse::Manager::getLinkTo("SwitchToHandheldVersion", request) );
  reply.out() << data[7]; // ">\n            Normale Ansicht\n        </a>\n
#line 15 "Core/views/parts/user-session.ecpp.html"
 } else {

  reply.out() << data[8]; //         <a href="
#line 16 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( RouteReverse::Manager::getLinkTo("SwitchToHandheldVersion", request) );
  reply.out() << data[9]; // ">\n            Mobilen Version\n        </a>\n
#line 19 "Core/views/parts/user-session.ecpp.html"
 }

  reply.out() << data[10]; //         <br>\n
#line 21 "Core/views/parts/user-session.ecpp.html"
 if (  userSession.isInRole ( "user" ) == true) {

  reply.out() << data[11]; //         
#line 22 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( userSession.getUserName( ) );
  reply.out() << data[12]; // (ID:
#line 22 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( userSession.getUserID( ) );
  reply.out() << data[13]; // )\n        <a href="
#line 23 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( RouteReverse::Manager::getLinkTo("logout", request) );
  reply.out() << data[14]; // ">Abmelden</a>\n
#line 24 "Core/views/parts/user-session.ecpp.html"
 } else {

  reply.out() << data[15]; // <!--        <a href="http://
#line 25 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( Config::it().domainName() );
  reply.out() << data[16]; // /LogIn">Anmelden</a> -->\n        <a href="
#line 26 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( RouteReverse::Manager::getLinkTo("LogIn", request) );
  reply.out() << data[17]; // ">Anmelden</a>\n
#line 27 "Core/views/parts/user-session.ecpp.html"
 }

  reply.out() << data[18]; //         <br>\n        <a href="
#line 29 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( RouteReverse::Manager::getLinkTo("RSSfeedView", request) );
  reply.out() << data[19]; // ">\n            <img\n                src="
#line 31 "Core/views/parts/user-session.ecpp.html"
  reply.sout() << ( RouteReverse::Manager::getLinkTo("Core/feed-icon.png", request) );
  reply.out() << data[20]; // "\n                width="22"\n                height="22"\n                alt="rss-feed-icon" />\n        </a>\n    </div>\n\n
  // </%include>
  reply.out() << data[21]; //     
  // <%include> Core/views/parts/head.ecpp.html
  reply.out() << data[22]; // \n<div id="header-logo">\n    <a href="home">\n        <div id="logo-black">\n            <h1>PERUSCHIM</h1>\n        </div>\n        <div id="logo-blue">\n            with C++/Tntnet\n        </div>\n    </a>\n</div>
  // </%include>
  reply.out() << data[23]; // \n    <div class="centerbox">\n        <h1>Fehlerhafte Formularverarbeitung</h1>\n        <div class="feedback-box">\n            <b>\n                Wenn sie diese Seite sehen ist etwas mit der Formularverarbeitung\n                schief gelaufen. Das tut mir leide! Folgende Ursachen k\303\266nnen der\n                Grund sein:\n            </b>\n            <ul>\n                <li>\n                    Das Formular wurde (versehentlich) zwei mal abgesendet in\n                    dem die Seite neu geladen haben.\n                </li>\n                <li>\n                    Es waren/sind in mehreren Fenster das selbe Formular\n                    ge\303\266ffnet.\n                </li>\n                <li>\n                    Das Formular stammt von einer Sitzung die bereits abgelaufen\n                    ist\n                </li>\n            </ul>\n        </div>\n    </div>\n
  // <%include> Core/views/parts/foot.ecpp.html
  reply.out() << data[24]; // \n    <p id="foot">\n        PERUSCHIM ist freie Software. Den Sourcecode findest bei\n        <a href="https://github.com/OlafRadicke/peruschim_cpp">github.com</a>\n    </p>\n
  // <%include> Core/resources/piwik.ecpp
  reply.out() << data[25]; // <!-- add your piwik Tracking Code and recompile the code. -->
  // </%include>
  // </%include>
  reply.out() << data[26]; // </body>\n</html>\n
  // <%/cpp>
  return HTTP_OK;
}

} // namespace
