
#ifndef EDITOWNVERSES_H
#define EDITOWNVERSES_H

#include <tnt/component.h>
#include <tnt/componentfactory.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include "Core/models/WebACL.h"
#include "Core/models/UserSession.h"
#include "Core/models/Quote.h"
#include "Core/models/QuoteRegister.h"


class EditOwnVerses : public tnt::Component
{
public:
    unsigned operator() (
        tnt::HttpRequest& request,
        tnt::HttpReply& reply,
        tnt::QueryParams& qparam
    );
};

#endif

