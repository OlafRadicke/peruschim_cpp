#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include "models/WebACL.h"
#include "models/UserSession.h"
#include "models/Quote.h"
#include "models/QuoteRegister.h"

namespace controller
{
  class EditOwnVerses : public tnt::Component
  {
    public:
      unsigned operator() (
          tnt::HttpRequest& request, 
          tnt::HttpReply& reply, 
          tnt::QueryParams& qparam);
  };

  static tnt::ComponentFactoryImpl<EditOwnVerses> factory("controller/EditOwnVerses");


}
