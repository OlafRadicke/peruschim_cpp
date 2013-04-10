
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet


TMP_SOURCES =  \
./src/controller/LoginController.cpp \
./src/controller/LogoutController.cpp \
./src/controller/NewAccountController.cpp \
./src/controller/NewQuoteController.cpp \
./src/resources/favicon.cpp \
./src/resources/style.cpp \
./src/view/access_denied.cpp \
./src/view/home.cpp \
./src/view/keyword-register.cpp \
./src/view/login.cpp \
./src/view/logout.cpp \
./src/view/mainmenu.cpp \
./src/view/newquote.cpp \
./src/view/newaccount.cpp  \
./src/view/portaladmin.cpp \
./src/view/portalquote.cpp \
./src/view/templates/header.cpp

OBJECTS =  \
./src/controller/LoginController.o \
./src/controller/LogoutController.o \
./src/controller/NewAccountController.o \
./src/controller/NewQuoteController.o \
./src/resources/favicon.o \
./src/resources/style.o \
./src/view/access_denied.o \
./src/view/home.o \
./src/view/keyword-register.o \
./src/view/login.o \
./src/view/logout.o \
./src/view/mainmenu.o \
./src/view/newquote.o \
./src/view/newaccount.o \
./src/view/portaladmin.o \
./src/view/portalquote.o \
./src/view/templates/header.o



clean:
	rm -f $(TMP_SOURCES) 

dist: $(OBJECTS) 

%.cpp %.h: %.ecpp
	$(ECPPC) $<


%.cpp %.h: %.tnt.cpp
	$(ECPPC) $<


./src/resources/favicon.cpp:
	ecppc -b ./src/resources/favicon.ico


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