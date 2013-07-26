<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"
</%pre>

<%config>
</%config>

<%args>
</%args>

<%session scope="shared">
    UserSession userSession();
</%session>

<%cpp>
    userSession.logout();
</%cpp>
