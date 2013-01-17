
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet
CXXFLAGS+=-I/usr/include -fPIC -O2
LDFLAGS+=-shared -L/usr/lib -ltntnet -lcxxtools


TNTSOURCES = ./src/view/artikel23i.ecpp 

SOURCES = ./src/view/artikel23i.cpp 

OBJECTS = /src/view/artikel23i.o 
CC =  g++
CPPFLAGS_SO = -shared -L/usr/local/lib -ltntnet -lcxxtools
CPPFLAGS_O = -I/usr/local/include -fPIC -O2
DIST = ./bin
# clean:
# 	rm ./src/view/artikel23i.so ./src/view/artikel23i.o

all-o: ./bin/artikel23i.so

./bin/artikel23i.so: ./src/view/artikel23i.o
	if [ ! -d $(DIST) ]; then mkdir $(DIST) ; fi
	$(CC) -o ./bin/artikel23i.so $(CPPFLAGS_SO) ./src/view/artikel23i.o  
	rm ./src/view/artikel23i.cpp 

./src/view/artikel23i.o: ./src/view/artikel23i.cpp
	$(CC) -o ./src/view/artikel23i.o $(CPPFLAGS_O) -c ./src/view/artikel23i.cpp 

./src/view/artikel23i.cpp: ./src/view/artikel23i.ecpp
	$(ECPPC)   -o ./src/view/artikel23i.cpp  ./src/view/artikel23i.ecpp 


test: all
	${TNTNET} tntnet.conf

/src/view/artikel23i.so: all-o
	${CXX} -o $@ ${LDFLAGS} $^

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
