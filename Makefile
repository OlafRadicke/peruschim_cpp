

TNTNET=/usr/bin/tntnet
TNTMAKEFILE = ./tntnet-make/Makefile

CPPFLAGS = -Wall -Werror -pedantic  -Wno-long-long
CPPFLAGS += -fPIC -O2  
LIBS =  -ltntnet -lcxxtools 
LIBS += -L/usr/lib
LIBS += -I/usr/include 
# tnt data base provider
# CPPFLAGS_O += -ltntdb
# pstgrsql 
LIBS += -lpqxx -lpq 

CC = g++
DIST = ./bin
PROG_NAME = ./artikel23t.so

SOURCES = ./src/model/Config.cpp \
./src/model/DatabaseProxy.cpp \
./src/model/WebACL.cpp \
./src/view/artikel23t.cpp \
./src/view/login.cpp \
./src/view/newaccont.cpp

OBJECTS = ./src/model/Config.o \
./src/model/DatabaseProxy.o \
./src/model/WebACL.o\
./src/view/artikel23t.o \
./src/view/login.o \
./src/view/newaccont.o

clean:
	make clean -f  $(TNTMAKEFILE)
	rm  $(OBJECTS)
	rm -Rvf $(DIST)


dist: convecpp $(PROG_NAME)
	if [ ! -d $(DIST) ]; then mkdir $(DIST) ; fi
	mv ./$(PROG_NAME) $(DIST)
	cp ./exsamples/artikel23t.conf $(DIST)
	cp ./exsamples/tntnet.conf $(DIST)
	cp ./exsamples/tntnet.properties $(DIST)
	cp ./AGPLv3.txt $(DIST)
	cp ./README.txt $(DIST)
	cp ./LICENSE.txt $(DIST)

$(PROG_NAME):  $(OBJECTS)
	LANG=C LC_ALL=C  $(CC) $(CPPFLAGS) -shared -o $(PROG_NAME) $(OBJECTS) $(LIBS)

# ./src/model/WebACL.o: ./src/model/WebACL.cpp
# 	$(CC) -o ./src/model/WebACL.o -I/usr/include -ltntdb ./src/model/WebACL.cpp

%.o: %.cpp
	LANG=C LC_ALL=C  $(CC)  $(CPPFLAGS) -o ./$@  -c ./$< $(LIBS)


convecpp:
	make dist -f $(TNTMAKEFILE)

# Für englische Fehlermeldungen LANG=C LC_ALL=C
test: dist
	cd $(DIST)&& ls && ${TNTNET} tntnet.conf

install:
	echo "ist noch nicht implementiert"

uninstall:
	echo "ist noch nicht implementiert"




.PHONY: test clean install dist uninstall convecpp