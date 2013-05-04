
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet
LIBS = -I ./src


TMP_SOURCES =  \
./src/controller/LoginController.cpp \
./src/controller/LogoutController.cpp \
./src/controller/NewAccountController.cpp \
./src/controller/NewQuoteController.cpp \
./src/resources/favicon.cpp \
./src/resources/style.cpp \
./src/view/access_denied.cpp \
./src/view/home.cpp \
./src/view/keyword-detail.cpp \
./src/view/keyword-register.cpp \
./src/view/login.cpp \
./src/view/logout.cpp \
./src/view/mainmenu.cpp \
./src/view/newquote.cpp \
./src/view/newaccount.cpp  \
./src/view/portaladmin.cpp \
./src/view/portalquote.cpp \
./src/view/templates/header.cpp


clean:
	rm -f $(TMP_SOURCES)

dist: $(TMP_SOURCES)

%.cpp %.h: %.ecpp
	$(ECPPC) $(LIBS) $<



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
