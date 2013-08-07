<%pre>
    #include "models/WebACL.h"
    #include "models/UserSession.h"
</%pre>

<%session scope="shared">
    UserSession userSession();
</%session>

<%cpp>
    userSession.logout();
</%cpp>
