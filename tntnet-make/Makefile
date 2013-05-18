
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet
LIBS = -I ./src


TMP_SOURCES =  \
./src/resources/favicon.cpp \
./src/resources/style.cpp \
./src/views/access_denied.cpp \
./src/views/edit_account.cpp \
./src/views/edit_editions.cpp \
./src/views/editquote.cpp \
./src/views/home.cpp \
./src/views/keyword-detail.cpp \
./src/views/keyword-register.cpp \
./src/views/login.cpp \
./src/views/logout.cpp \
./src/views/mainmenu.cpp \
./src/views/newquote.cpp \
./src/views/newaccount.cpp  \
./src/views/portaladmin.cpp \
./src/views/portalquote.cpp


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
