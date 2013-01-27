

TNTNET=/usr/bin/tntnet

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
PROG_NAME = ./bin/artikel23t.so

SOURCES = ./src/model/Config.cpp \
./src/model/DatabaseProxy.cpp \
./src/model/WebACL.cpp \
./src/view/artikel23t.cpp \
./src/view/login.cpp

OBJECTS = ./src/model/Config.o \
./src/model/DatabaseProxy.o \
./src/model/WebACL.o\
./src/view/artikel23t.o \
./src/view/login.o 

clean:
	make clean -f tntnet.make 
	rm  $(OBJECTS)


dist: convecpp $(PROG_NAME)

$(PROG_NAME):  $(OBJECTS)
	if [ ! -d $(DIST) ]; then mkdir $(DIST) ; fi
	LANG=C LC_ALL=C  $(CC) $(CPPFLAGS) -shared -o $(PROG_NAME) $(OBJECTS) $(LIBS)

# ./src/model/WebACL.o: ./src/model/WebACL.cpp
# 	$(CC) -o ./src/model/WebACL.o -I/usr/include -ltntdb ./src/model/WebACL.cpp

%.o: %.cpp
	LANG=C LC_ALL=C  $(CC)  $(CPPFLAGS) -o ./$@  -c ./$< $(LIBS)


convecpp:
	make dist -f tntnet.make


test: dist
	cp $(PROG_NAME) ./
	LANG=C LC_ALL=C  ${TNTNET} tntnet.conf

install:
	echo "ist noch nicht implementiert"

uninstall:
	echo "ist noch nicht implementiert"




.PHONY: test clean install dist uninstall convecpp