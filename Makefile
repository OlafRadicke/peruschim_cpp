

TNTNET=tntnet
TNTMAKEFILE = ./tntnet-make/Makefile

CPPFLAGS = -Wall -Werror -pedantic  -Wno-long-long
CPPFLAGS += -fPIC -O2
LIBS =  -ltntnet -lcxxtools -ltntdb
LIBS += -I ./src


CC = g++
DIST = ./bin
PROG_NAME = ./peruschim_cpp


OBJECTS = \
./src/peruschim_cpp.o \
./src/controller/EditAccountController.o \
./src/controller/EditOwnVersesController.o \
./src/models/AccountData.o \
./src/models/Config.o \
./src/models/DatabaseProxy.o \
./src/models/Edition.o \
./src/models/EditionManager.o \
./src/models/KeywordData.o \
./src/models/KeywordRegister.o \
./src/models/OString.o \
./src/models/Quote.o \
./src/models/QuoteRegister.o \
./src/models/UserSession.o \
./src/models/WebACL.o\
./src/resources/favicon.o \
./src/resources/style.o \
./src/views/access_denied.o \
./src/views/EditAccountView.o \
./src/views/edit_editions.o \
./src/views/EditOwnVersesView.o \
./src/views/editquote.o \
./src/views/export_own_verses.o \
./src/views/home.o \
./src/views/import_own_verses.o \
./src/views/keyword_detail.o \
./src/views/keyword_register.o \
./src/views/login.o \
./src/views/logout.o \
./src/views/mainmenu.o \
./src/views/newaccount.o \
./src/views/newquote.o \
./src/views/portalaccount.o \
./src/views/portaladmin.o \
./src/views/portalquote.o \
./src/views/reset_own_password.o

all: dist

quick-clean:
	make clean -f  $(TNTMAKEFILE)

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
	LANG=C LC_ALL=C  $(CC) $(CPPFLAGS)  $(LIBS) -o $(PROG_NAME) $(OBJECTS)

testtest:
	LANG=C LC_ALL=C  echo $(LIBS)

%.o: %.cpp
	LANG=C LC_ALL=C  echo $(LIBS)
	LANG=C LC_ALL=C  $(CC) $(CPPFLAGS) $(LIBS) -I usr -o ./$@  -c ./$<


convecpp:
	############################## Start ##############################
	make dist -f $(TNTMAKEFILE)

# Für englische Fehlermeldungen LANG=C LC_ALL=C
test: dist
	echo $(LIBS)
	cd $(DIST)&& ls && $(PROG_NAME)
debug:
	cd $(DIST)&& gdb $(PROG_NAME)

install:
	echo "ist noch nicht implementiert"

uninstall:
	echo "ist noch nicht implementiert"




.PHONY: test clean instsrc/modelsall dist uninstall convecpp
