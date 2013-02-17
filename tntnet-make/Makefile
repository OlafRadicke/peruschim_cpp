
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet


TNTSOURCES = ./src/view/artikel23t.ecpp \
./src/view/header.ecpp \
./src/view/home.ecpp \
./src/view/login.ecpp \
./src/view/logout.ecpp \
./src/view/newaccont.ecpp \
./src/view/portaladmin.ecpp \
./src/view/style.ecpp

TMP_SOURCES = ./src/view/artikel23t.cpp \
./src/view/header.cpp \
./src/view/home.cpp \
./src/view/login.cpp \
./src/view/logout.cpp \
./src/view/newaccont.cpp  \
./src/view/portaladmin.cpp \
./src/view/style.cpp

OBJECTS = ./src/view/artikel23t.o \
./src/view/header.o \
./src/view/home.o \
./src/view/login.o \
./src/view/logout.o \
./src/view/newaccont.o \
./src/view/portaladmin.o \
./src/view/style.o



clean:
	rm -f $(TMP_SOURCES) 



dist: $(OBJECTS) 

%.cpp %.h: %.ecpp
	$(ECPPC) $<


.SUFFIXES: .ecpp .gif .jpg .css .js .cpp


.gif.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/gif ${ECPPFLAGS_GIF} -b -o $@ $<
.jpg.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/jpg ${ECPPFLAGS_JPG} -b -o $@ $<
.png.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/png ${ECPPFLAGS_PNG} -b -o $@ $<
.ico.cpp:
	${ECPPC} ${ECPPFLAGS} -m image/x-icon ${ECPPFLAGS_ICO} -b -o $@ $<
.css.cpp:
	${ECPPC} ${ECPPFLAGS} -m text/css ${ECPPFLAGS_CSS} -b -o $@ $<
.js.cpp:
	${ECPPC} ${ECPPFLAGS} -m application/javascript ${ECPPFLAGS_JS} -b -o $@ $<

.PHONY: dist