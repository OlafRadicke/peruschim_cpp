////////////////////////////////////////////////////////////////////////
// ./src/view/login.cpp
// generated with ecppc
//

#include <tnt/ecpp.h>
#include <tnt/convert.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>
#include <tnt/httpheader.h>
#include <tnt/http.h>
#include <tnt/data.h>
#include <tnt/componentfactory.h>
#include <tnt/comploader.h>
#include <tnt/tntconfig.h>
#include <cxxtools/log.h>
#include <stdexcept>

log_define("component.login")

// <%pre>
#line 1 "./src/view/login.ecpp"

    // put your includes here
    // #include "foo.h"
    #include "../model/WebACL.h"

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
    // <%config>
    static std::string db_url;
    static std::string db_user;
    static std::string db_password;
    // </%config>

};

class _component_Factory : public tnt::ComponentFactoryImpl<_component_>
{
  public:
    _component_Factory()
      : tnt::ComponentFactoryImpl<_component_>("login")
      { }
    tnt::Component* doCreate(const tnt::Compident& ci,
      const tnt::Urlmapper& um, tnt::Comploader& cl);
    virtual void doConfigure(const tnt::Tntconfig& config);
};

tnt::Component* _component_Factory::doCreate(const tnt::Compident& ci,
  const tnt::Urlmapper& um, tnt::Comploader& cl)
{
  return new _component_(ci, um, cl);
}

void _component_Factory::doConfigure(const tnt::Tntconfig& config)
{
  // <%config>
    if (config.hasValue("db_url"))
      _component_::db_url = config.getValue("db_url");
    if (config.hasValue("db_user"))
      _component_::db_user = config.getValue("db_user");
    if (config.hasValue("db_password"))
      _component_::db_password = config.getValue("db_password");
  // </%config>
}

static _component_Factory factory;

static const char* rawData = "0\000\000\0001\000\000\0002\000\000\0003\000\000\0004\000\000\000\244\000\000\000\266\000"
  "\000\000\310\000\000\000\330\000\000\000\351\000\000\000\376\000\000\000O\002\000\000\n\n\n\n\n<html>\n<head>\n    <t"
  "itle>Login</title>\n</head>\n<body>\n\n    <h1>Anmeldung</h1>\n    <p>Hello world! <br />\nName:  <br />\nPasswort:  "
  "<br />\nuserRoll:  <br />\ndb_url:  <br />\ndb_user:  <br />\ndb_password: \n    </p>\n\n    <form method=\"post\" >"
  "\n        <p>Benutzer:<br><input name=\"name\" type=\"text\" size=\"30\" maxlength=\"30\"></p>\n        <p>Passwort:<"
  "br><input name=\"password\" type=\"password\" size=\"30\" maxlength=\"40\"></p>\n        <p><input type=\"submit\" va"
  "lue=\" Absenden \"><input type=\"reset\" value=\" Abbrechen\"></p>\n    </form>\n</body>\n</html>";

// <%shared>
// </%shared>

// <%config>
std::string _component_::db_url =  "database=localhost";
std::string _component_::db_user =  "user=user";
std::string _component_::db_password =  "password=password";
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
  log_trace("login " << qparam.getUrl());

  tnt::DataChunks data(rawData);

  // <%args>
std::string name = qparam.has("name") ? tnt::stringToWithDefault<std::string>(qparam.param("name"), ( ""), reply.out().getloc()) : ( "");
std::string password = qparam.has("password") ? tnt::stringToWithDefault<std::string>(qparam.param("password"), ( ""), reply.out().getloc()) : ( "");
  // </%args>

#line 23 "./src/view/login.ecpp"
  typedef std::string userName_type;
  TNT_SESSION_COMPONENT_VAR(userName_type, userName, "std::string userName", ( "anonymous"));   // <%session> std::string userName( "anonymous")
#line 24 "./src/view/login.ecpp"
  typedef std::string userRoll_type;
  TNT_SESSION_COMPONENT_VAR(userRoll_type, userRoll, "std::string userRoll", ( "logout"));   // <%session> std::string userRoll( "logout")
  // <%cpp>
  reply.out() << data[0]; // \n
  reply.out() << data[1]; // \n
  reply.out() << data[2]; // \n
  reply.out() << data[3]; // \n
#line 27 "./src/view/login.ecpp"

    
    // put your C++ code here
    if ( WebACL::authUser ( name, password ) ) {
        userRoll = "login";
        userName = name;
    } else {
        userRoll = "logout";
    };

  reply.out() << data[4]; // \n<html>\n<head>\n    <title>Login</title>\n</head>\n<body>\n\n    <h1>Anmeldung</h1>\n    <p>Hello world! <br />\nName: 
#line 46 "./src/view/login.ecpp"
  reply.sout() << ( name );
  reply.out() << data[5]; //  <br />\nPasswort: 
#line 47 "./src/view/login.ecpp"
  reply.sout() << ( password );
  reply.out() << data[6]; //  <br />\nuserRoll: 
#line 48 "./src/view/login.ecpp"
  reply.sout() << ( userRoll );
  reply.out() << data[7]; //  <br />\ndb_url: 
#line 49 "./src/view/login.ecpp"
  reply.sout() << ( db_url );
  reply.out() << data[8]; //  <br />\ndb_user: 
#line 50 "./src/view/login.ecpp"
  reply.sout() << ( db_user );
  reply.out() << data[9]; //  <br />\ndb_password: 
#line 51 "./src/view/login.ecpp"
  reply.sout() << ( db_password );
  reply.out() << data[10]; // \n    </p>\n\n    <form method="post" >\n        <p>Benutzer:<br><input name="name" type="text" size="30" maxlength="30"></p>\n        <p>Passwort:<br><input name="password" type="password" size="30" maxlength="40"></p>\n        <p><input type="submit" value=" Absenden "><input type="reset" value=" Abbrechen"></p>\n    </form>\n</body>\n</html>
  // <%/cpp>
  return HTTP_OK;
}

} // namespace
