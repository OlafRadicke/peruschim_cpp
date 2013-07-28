AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = peruschim_cpp

ecppSources = \
	style.ecpp \
	views/access_denied.ecpp \
	views/EditAccountView.ecpp \
	views/EditEditionsView.ecpp \
	views/EditOwnVersesView.ecpp \
	views/EditQuoteView.ecpp \
	views/ExportOwnVersesView.ecpp \
	views/home.ecpp \
	views/ImportOwnVersesView.ecpp \
	views/KeywordDetailView.ecpp \
	views/KeywordRegisterView.ecpp \
	views/login.ecpp \
	views/logout.ecpp \
	views/mainmenu.ecpp \
	views/NewAccountView.ecpp \
	views/newquote.ecpp \
	views/portalaccount.ecpp \
	views/portaladmin.ecpp \
	views/portalquote.ecpp \
	views/reset_own_password.ecpp

staticSources = \
	resources/favicon.ico \
	resources/peruschim.css

peruschim_cpp_SOURCES = \
	controller/EditAccountController.cpp \
	controller/EditEditionsController.cpp \
	controller/EditOwnVersesController.cpp \
	controller/EditQuoteController.cpp \
	controller/ExportOwnVersesController.cpp \
	controller/ImportOwnVersesController.cpp \
	controller/KeywordDetailController.cpp \
	controller/KeywordRegisterController.cpp \
	controller/NewAccountController.cpp \
	manager/BibleManager.cpp \
	manager/EditionManager.cpp \
	manager/QuoteManager.cpp \
	models/AccountData.cpp \
	models/Config.cpp \
	models/DatabaseProxy.cpp \
	models/KeywordData.cpp \
	models/KeywordRegister.cpp \
	models/OString.cpp \
	models/Quote.cpp \
	models/QuoteRegister.cpp \
	models/UserSession.cpp \
	models/WebACL.cpp \
	peruschim_cpp.cpp \
	$(ecppSources)

nodist_peruschim_cpp_SOURCES = \
	resources.cpp

peruschim_cpp_LDFLAGS = -lcxxtools -ltntnet -ltntdb

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(ecppSources:.ecpp=.deps) resource.cpp

#
# Rules for tntnet applications
#
resources.cpp: $(staticSources) Makefile.am
	$(ECPPC) -bb -z -n resources -p -o resources.cpp -I$(srcdir) $(staticSources)

SUFFIXES=.ecpp .ico .cpp

.ecpp.cpp:
	$(ECPPC) -I $(top_srcdir)/src -o $@ $<
.ecpp.deps:
	$(ECPPC) -M -n $* -I $(srcdir) -I $(srcdir)/include $< | $(SED) '1s/\(.*\).cpp:/\1.cpp \1.deps:/' > $@
.ico.cpp:
	$(ECPPC) -b -m image/x-icon -o $@ $<

-include $(ecppSources:.ecpp=.deps)
