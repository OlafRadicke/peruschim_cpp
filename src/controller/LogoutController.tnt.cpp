<%pre>
    #include "../models/WebACL.h"
    #include "../models/UserSession.h"
</%pre>

<%config>
</%config>

<%args>
</%args>

<%session scope="global">
    UserSession userSession();
</%session>

<%cpp>
    userSession.lockout();
</%cpp>
