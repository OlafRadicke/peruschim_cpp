AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = peruschim_cpp
AM_CPPFLAGS = -I$(srcdir)

EXTRA_DIST = \
	controller/LogoutController.tnt.cpp \
	resources/favicon.ico \
	resources/piwik.ecpp \
	resources/peruschim.css \
	resources/small_screens.css \
	views/parts/user-session.ecpp.html \
	views/parts/head.ecpp.html \
	views/parts/foot.ecpp.html

noinst_HEADERS = \
	manager/BibleManager.h \
	manager/EditionManager.h \
	manager/KeywordRegister.h \
	manager/QuoteManager.h \
	manager/QuoteRegister.h \
	manager/WebACL.h \
	models/AccountData.h \
	models/Config.h \
	models/DatabaseProxy.h \
	models/Edition.h \
	models/KeywordData.h \
	models/OString.h \
	models/Quote.h \
	models/UserSession.h

ecppSources = \
	views/parts/style.ecpp \
	views/AccountRegisterView.ecpp \
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
	views/LogInView.ecpp \
	views/logout.ecpp \
	views/mainmenu.ecpp \
	views/NewAccountView.ecpp \
	views/NewQuoteView.ecpp \
	views/portalaccount.ecpp \
	views/portaladmin.ecpp \
	views/portalquote.ecpp \
	views/ResetOwnPasswordView.ecpp \
	views/RSSfeedView.ecpp \
	views/SwitchToHandheldVersionView.ecpp \
	views/TrustAUserView.ecpp

staticSources = \
	resources/favicon.ico \
	resources/peruschim.css \
	resources/small_screens.css \
	resources/feed-icon.png

peruschim_cpp_SOURCES = \
	controller/AccountRegisterController.cpp \
	controller/EditAccountController.cpp \
	controller/EditEditionsController.cpp \
	controller/EditOwnVersesController.cpp \
	controller/EditQuoteController.cpp \
	controller/ExportOwnVersesController.cpp \
	controller/ImportOwnVersesController.cpp \
	controller/KeywordDetailController.cpp \
	controller/KeywordRegisterController.cpp \
	controller/LogInController.cpp \
	controller/NewAccountController.cpp \
	controller/NewQuoteController.cpp \
	controller/ResetOwnPasswordController.cpp \
	controller/SwitchToHandheldVersionController.cpp \
	controller/TrustAUserController.cpp \
	manager/BibleManager.cpp \
	manager/EditionManager.cpp \
	manager/KeywordRegister.cpp \
	manager/QuoteManager.cpp \
	manager/QuoteRegister.cpp \
	manager/RSSfeedManager.cpp \
	manager/WebACL.cpp \
	models/AccountData.cpp \
	models/Config.cpp \
	models/DatabaseProxy.cpp \
	models/KeywordData.cpp \
	models/OString.cpp \
	models/Quote.cpp \
	models/UserSession.cpp \
	peruschim_cpp.cpp \
	$(ecppSources)

nodist_peruschim_cpp_SOURCES = \
	resources.cpp

peruschim_cpp_LDFLAGS = -lcxxtools -ltntnet -ltntdb

CLEANFILES = $(ecppSources:.ecpp=.cpp) $(ecppSources:.ecpp=.deps) resources.cpp

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
