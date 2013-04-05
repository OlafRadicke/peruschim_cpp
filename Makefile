

TNTNET=/usr/bin/tntnet
TNTMAKEFILE = ./tntnet-make/Makefile

CPPFLAGS = -Wall -Werror -pedantic  -Wno-long-long
CPPFLAGS += -fPIC -O2  
LIBS =  -ltntnet -lcxxtools -ltntdb
LIBS += -L/usr/lib
LIBS += -I/usr/include 
# tnt data base provider
# CPPFLAGS_O += -ltntdb
# pstgrsql 
LIBS += -lpqxx -lpq 

CC = g++
DIST = ./bin
PROG_NAME = ./peruschim_cpp


OBJECTS = \
./src/peruschim_cpp.o \
./src/model/AccountData.o \
./src/model/Config.o \
./src/model/DatabaseProxy.o \
./src/model/Edition.o \
./src/model/EditionManager.o \
./src/model/KeywordData.o \
./src/model/KeywordRegister.o \
./src/model/Quote.o \
./src/model/UserSession.o \
./src/model/WebACL.o\
./src/view/access_denied.o \
./src/view/favicon.o \
./src/view/home.o \
./src/view/keyword-register.o \
./src/view/header.o \
./src/view/login.o \
./src/view/logout.o \
./src/view/mainmenu.o \
./src/view/newquote.o \
./src/view/portaladmin/newaccount.o  \
./src/view/portaladmin/portaladmin.o \
./src/view/style.o

all: dist

clean:
	make clean -f  $(TNTMAKEFILE)
	rm  $(OBJECTS)
	rm -Rvf $(DIST)


dist: convecpp $(PROG_NAME)
	if [ ! -d $(DIST) ]; then mkdir $(DIST) ; fi
	mv ./$(PROG_NAME) $(DIST)
	cp ./exsamples/$(PROG_NAME).conf $(DIST)
	cp ./exsamples/tntnet.conf $(DIST)
	cp ./exsamples/tntnet.properties $(DIST)
	cp ./AGPLv3.txt $(DIST)
	cp ./README.txt $(DIST)
	cp ./LICENSE.txt $(DIST)

$(PROG_NAME):  $(OBJECTS)
	LANG=C LC_ALL=C  $(CC) $(CPPFLAGS) -o $(PROG_NAME) $(OBJECTS) $(LIBS)

# ./src/model/WebACL.o: ./src/model/WebACL.cpp
# 	$(CC) -o ./src/model/WebACL.o -I/usr/include -ltntdb ./src/model/WebACL.cpp

%.o: %.cpp
	LANG=C LC_ALL=C  $(CC)  $(CPPFLAGS) -o ./$@  -c ./$< $(LIBS)


convecpp:
	############################## Start ##############################
	make dist -f $(TNTMAKEFILE)

# Für englische Fehlermeldungen LANG=C LC_ALL=C
test: dist
	cd $(DIST)&& ls && $(PROG_NAME)

install:
	echo "ist noch nicht implementiert"

uninstall:
	echo "ist noch nicht implementiert"




.PHONY: test clean install dist uninstall convecpp