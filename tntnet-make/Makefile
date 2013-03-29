
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet


TMP_SOURCES =  \
./src/view/access_denied.cpp \
./src/view/favicon.cpp \
./src/view/header.cpp \
./src/view/home.cpp \
./src/view/login.cpp \
./src/view/logout.cpp \
./src/view/mainmenu.cpp \
./src/view/newquote.cpp \
./src/view/portaladmin/add_db_connection.cpp  \
./src/view/portaladmin/edit_db_connection.cpp  \
./src/view/portaladmin/newaccont.cpp  \
./src/view/portaladmin/portaladmin.cpp \
./src/view/portaloperator/portaloperator.cpp \
./src/view/portalprovider/anonymous_seeker_list.cpp \
./src/view/portalprovider/portalprovider.cpp \
./src/view/portalseeker/portalseeker.cpp \
./src/view/style.cpp

OBJECTS =  \
./src/view/access_denied.o \
./src/view/favicon.o \
./src/view/header.o \
./src/view/home.o \
./src/view/login.o \
./src/view/logout.o \
./src/view/mainmenu.o \
./src/view/newquote.o \
./src/view/portaladmin/add_db_connection.o  \
./src/view/portaladmin/edit_db_connection.o  \
./src/view/portaladmin/newaccont.o \
./src/view/portaladmin/portaladmin.o \
./src/view/portaloperator/portaloperator.o \
./src/view/portalprovider/anonymous_seeker_list.o \
./src/view/portalprovider/portalprovider.o \
./src/view/portalseeker/portalseeker.o \
./src/view/style.o



clean:
	rm -f $(TMP_SOURCES) 



dist: $(OBJECTS) 

%.cpp %.h: %.ecpp
	$(ECPPC) $<


./src/view/favicon.cpp:
	ecppc -b ./src/view/favicon.ico


.SUFFIXES: .ecpp .gif .jpg .css .js .cpp


.gif.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/gif ${ECPPFLAGS_GIF} -b -o $@ $<
.jpg.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/jpg ${ECPPFLAGS_JPG} -b -o $@ $<
.png.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/png ${ECPPFLAGS_PNG} -b -o $@ $<
# .ico.cpp:
# 	${ECPPC} ${ECPPFLAGS} -m image/x-icon ${ECPPFLAGS_ICO} -b -o $@ $<
.css.cpp:
	${ECPPC} ${ECPPFLAGS} -m text/css ${ECPPFLAGS_CSS} -b -o $@ $<
.js.cpp:
	${ECPPC} ${ECPPFLAGS} -m application/javascript ${ECPPFLAGS_JS} -b -o $@ $<

.PHONY: dist