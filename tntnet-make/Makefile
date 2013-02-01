
ECPPC=/usr/bin/ecppc
TNTNET=/usr/bin/tntnet


TNTSOURCES = ./src/view/artikel23t.ecpp \
./src/view/login.ecpp \
./src/view/newaccont.ecpp

TMP_SOURCES = ./src/view/artikel23t.cpp \
./src/view/login.cpp \
./src/view/newaccont.cpp


dist: $(TMP_SOURCES)

clean:
	rm $(TMP_SOURCES)

# $(TMP_SOURCES): $(TNTSOURCES)
# 	$(ECPPC)   -o ./$@  ./$< 

./src/view/artikel23t.cpp: ./src/view/artikel23t.ecpp
	$(ECPPC)   -o ./src/view/artikel23t.cpp  ./src/view/artikel23t.ecpp

./src/view/login.cpp: ./src/view/login.ecpp
	$(ECPPC)   -o ./src/view/login.cpp  ./src/view/login.ecpp


./src/view/newaccont.cpp: ./src/view/newaccont.ecpp
	$(ECPPC)   -o ./src/view/newaccont.cpp  ./src/view/newaccont.ecpp


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