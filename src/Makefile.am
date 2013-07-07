bin_PROGRAMS = peruschim_cpp

ecppSources = \
	resources/style.ecpp \
	views/access_denied.ecpp \
	views/EditAccountView.ecpp \
	views/edit_editions.ecpp \
	views/EditOwnVersesView.ecpp \
	views/editquote.ecpp \
	views/export_own_verses.ecpp \
	views/home.ecpp \
	views/import_own_verses.ecpp \
	views/keyword_detail.ecpp \
	views/keyword_register.ecpp \
	views/login.ecpp \
	views/logout.ecpp \
	views/mainmenu.ecpp \
	views/newaccount.ecpp \
	views/newquote.ecpp \
	views/portalaccount.ecpp \
	views/portaladmin.ecpp \
	views/portalquote.ecpp \
	views/reset_own_password.ecpp

icoSources = \
	resources/favicon.ico

peruschim_cpp_SOURCES = \
	peruschim_cpp.cpp \
	models/AccountData.cpp \
	models/Config.cpp \
	models/ConfigImpl.cpp \
	models/DatabaseProxy.cpp \
	models/EditionManager.cpp \
	models/KeywordData.cpp \
	models/KeywordRegister.cpp \
	models/OString.cpp \
	models/Quote.cpp \
	models/QuoteRegister.cpp \
	models/UserSession.cpp \
	models/WebACL.cpp \
	$(ecppSources) $(icoSources)

peruschim_cpp_LDFLAGS = -lcxxtools -ltntnet -ltntdb

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(icoSources:.ico=.cpp)

SUFFIXES=.ecpp .ico .cpp

.ecpp.cpp:
	$(ECPPC) -I $(top_srcdir)/src -o $@ $<
.ico.cpp:
	$(ECPPC) -b -m image/x-icon -o $@ $<
