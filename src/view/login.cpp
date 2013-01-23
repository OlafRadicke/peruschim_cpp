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
#include <cxxtools/log.h>
#include <stdexcept>

log_define("component.artikel23i")

// <%pre>
#line 1 "./src/view/artikel23i.ecpp"

// put your includes here
// #include "foo.h"

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

static tnt::ComponentFactoryImpl<_component_> Factory("artikel23i");

static const char* rawData = "\010\000\000\000\222\000\000\000<html>\n <head>\n  <title>ecpp-application artikel23i</ti"
  "tle>\n </head>\n <body>\n  <h1>artikel23i</h1>\n  <p>Hello world!</p>\n </body>\n</html>\n";

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
  log_trace("artikel23i " << qparam.getUrl());

  tnt::DataChunks data(rawData);

  // <%args>
  // </%args>

  // <%cpp>
#line 13 "./src/view/artikel23i.ecpp"

// put your C++ code here

  reply.out() << data[0]; // <html>\n <head>\n  <title>ecpp-application artikel23i</title>\n </head>\n <body>\n  <h1>artikel23i</h1>\n  <p>Hello world!</p>\n </body>\n</html>\n
  // <%/cpp>
  return HTTP_OK;
}

} // namespace
