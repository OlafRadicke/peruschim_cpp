
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet
CPPFLAGS_SO = -shared -L/usr/local/lib -ltntnet -lcxxtools
CPPFLAGS_O = -I/usr/local/include -fPIC -O2
CC =  g++
DIST = ./bin
PROG_NAME = ./bin/artikel23i.so

TNTSOURCES = ./src/view/artikel23i.ecpp 
TMP_SOURCES = ./src/view/artikel23i.cpp 
OBJECTS = ./src/view/artikel23i.o 

clean:
	rm $(TMP_SOURCES) $(OBJECTS)

dist: $(PROG_NAME)

$(PROG_NAME): $(OBJECTS)
	if [ ! -d $(DIST) ]; then mkdir $(DIST) ; fi
	$(CC) -o ./$< $(CPPFLAGS_SO) ./$@ 
	rm $(OBJECTS) $(TMP_SOURCES)

%.o: %.cpp
	$(CC) -o ./$@ $(CPPFLAGS_O) -c ./$<

%.cpp: %.ecpp
	$(ECPPC)   -o ./$@  ./$< 


test: dist
	${TNTNET} tntnet.conf

install:
	echo "ist noch nicht implementiert"

uninstall:
	echo "ist noch nicht implementiert"


.SUFFIXES: .ecpp .gif .jpg .css .js .cpp

/src/view/*.ecpp.cpp:
	${ECPPC} ${ECPPFLAGS} ${ECPPFLAGS_CPP} -o /src/view/$@ /src/view/*$<
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

.PHONY: test clean install dist uninstall