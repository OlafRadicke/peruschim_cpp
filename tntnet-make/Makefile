
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet


TMP_SOURCES =  \
./src/controller/Login.cpp \
./src/view/access_denied.cpp \
./src/view/favicon.cpp \
./src/view/header.cpp \
./src/view/home.cpp \
./src/view/keyword-register.cpp \
./src/view/login.cpp \
./src/view/logout.cpp \
./src/view/mainmenu.cpp \
./src/view/newquote.cpp \
./src/view/portaladmin/newaccount.cpp  \
./src/view/portaladmin/portaladmin.cpp \
./src/view/portalquote.cpp \
./src/view/style.cpp

OBJECTS =  \
./src/controller/Login.o \
./src/view/access_denied.o \
./src/view/favicon.o \
./src/view/header.o \
./src/view/home.o \
./src/view/keyword-register.o \
./src/view/login.o \
./src/view/logout.o \
./src/view/mainmenu.o \
./src/view/newquote.o \
./src/view/portaladmin/newaccount.o \
./src/view/portaladmin/portaladmin.o \
./src/view/portalquote.o \
./src/view/style.o



clean:
	rm -f $(TMP_SOURCES) 

dist: $(OBJECTS) 

%.cpp %.h: %.ecpp
	$(ECPPC) $<


%.cpp %.h: %.tnt.cpp
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