

TNTNET=/usr/bin/tntnet
TNTMAKEFILE = ./tntnet-make/Makefile

CPPFLAGS = -Wall -Werror -pedantic  -Wno-long-long
CPPFLAGS += -fPIC -O2  
LIBS =  -ltntnet -lcxxtools -ltntdb
LIBS += -L/usr/lib
LIBS += -I/usr/include 

CC = g++
DIST = ./bin
PROG_NAME = ./peruschim_cpp


OBJECTS = \
./src/controller/LoginController.o \
./src/controller/LogoutController.o \
./src/controller/NewAccountController.o \
./src/peruschim_cpp.o \
./src/models/AccountData.o \
./src/models/Config.o \
./src/models/DatabaseProxy.o \
./src/models/Edition.o \
./src/models/EditionManager.o \
./src/models/KeywordData.o \
./src/models/KeywordRegister.o \
./src/models/Quote.o \
./src/models/UserSession.o \
./src/models/WebACL.o\
./src/resources/favicon.o \
./src/resources/style.o \
./src/view/access_denied.o \
./src/view/home.o \
./src/view/keyword-register.o \
./src/view/login.o \
./src/view/logout.o \
./src/view/mainmenu.o \
./src/view/newquote.o \
./src/view/newaccount.o  \
./src/view/portaladmin.o \
./src/view/portalquote.o \
./src/view/templates/header.o

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

# ./src/models/WebACL.o: ./src/models/WebACL.cpp
# 	$(CC) -o ./src/models/WebACL.o -I/usr/include -ltntdb ./src/models/WebACL.cpp

%.o: %.cpp
	LANG=C LC_ALL=C  $(CC)  $(CPPFLAGS) -o ./$@  -c ./$< $(LIBS)


convecpp:
	############################## Start ##############################
	make dist -f $(TNTMAKEFILE)

# Für englische Fehlermeldungen LANG=C LC_ALL=C
test: dist
	cd $(DIST)&& ls && $(PROG_NAME)

debug:
	cd $(DIST)&& gdb $(PROG_NAME)

install:
	echo "ist noch nicht implementiert"

uninstall:
	echo "ist noch nicht implementiert"




.PHONY: test clean install dist uninstall convecpp