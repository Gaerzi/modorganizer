#-------------------------------------------------
#
# Project created by QtCreator 2011-05-03T18:10:26
#
#-------------------------------------------------

contains(QT_VERSION, "^5.*") {
	QT       += core gui widgets webkitwidgets network declarative script xml sql xmlpatterns
} else {
	QT       += core gui webkit network xml declarative script sql xmlpatterns
}

TARGET = ModOrganizer
TEMPLATE = app

SOURCES += \
    transfersavesdialog.cpp \
    syncoverwritedialog.cpp \
    spawn.cpp \
    singleinstance.cpp \
    simpleinstalldialog.cpp \
    settingsdialog.cpp \
    settings.cpp \
    selfupdater.cpp \
    selectiondialog.cpp \
    savegameinfowidgetgamebryo.cpp \
    savegameinfowidget.cpp \
    savegamegamebryo.cpp \
    savegame.cpp \
    report.cpp \
    questionboxmemory.cpp \
    queryoverwritedialog.cpp \
    profilesdialog.cpp \
    profile.cpp \
    pluginlistsortproxy.cpp \
    pluginlist.cpp \
    overwriteinfodialog.cpp \
    nxmurl.cpp \
    nxmaccessmanager.cpp \
    nexusview.cpp \
    nexusinterface.cpp \
		nexusdialog.cpp \
    motddialog.cpp \
    modlistsortproxy.cpp \
    modlist.cpp \
    modinfodialog.cpp \
    modinfo.cpp \
    messagedialog.cpp \
    mainwindow.cpp \
    main.cpp \
    loghighlighter.cpp \
    logbuffer.cpp \
    lockeddialog.cpp \
    loadmechanism.cpp \
    json.cpp \
    installdialog.cpp \
    installationmanager.cpp \
    helper.cpp \
    fomodinstallerdialog.cpp \
    finddialog.cpp \
    filedialogmemory.cpp \
    executableslist.cpp \
    editexecutablesdialog.cpp \
    dummybsa.cpp \
    downloadmanager.cpp \
    downloadlistwidgetcompact.cpp \
    downloadlistwidget.cpp \
    downloadlistsortproxy.cpp \
    downloadlist.cpp \
    directoryrefresher.cpp \
    credentialsdialog.cpp \
    categoriesdialog.cpp \
    categories.cpp \
    bbcode.cpp \
    baincomplexinstallerdialog.cpp \
    archivetree.cpp \
    activatemodsdialog.cpp \
    moapplication.cpp \
    profileinputdialog.cpp \
    icondelegate.cpp \
    gameinfoimpl.cpp

HEADERS  += \
    transfersavesdialog.h \
    syncoverwritedialog.h \
    spawn.h \
    singleinstance.h \
    simpleinstalldialog.h \
    settingsdialog.h \
    settings.h \
    selfupdater.h \
		selectiondialog.h \
    savegameinfowidgetgamebryo.h \
    savegameinfowidget.h \
    savegamegamebyro.h \
    savegame.h \
    report.h \
    questionboxmemory.h \
    queryoverwritedialog.h \
    profilesdialog.h \
    profile.h \
    pluginlistsortproxy.h \
    pluginlist.h \
    overwriteinfodialog.h \
    nxmurl.h \
    nxmaccessmanager.h \
    nexusview.h \
    nexusinterface.h \
		nexusdialog.h \
    motddialog.h \
    modlistsortproxy.h \
    modlist.h \
    modinfodialog.h \
    modinfo.h \
    messagedialog.h \
    mainwindow.h \
    loghighlighter.h \
    logbuffer.h \
    lockeddialog.h \
    loadmechanism.h \
    json.h \
    installdialog.h \
    installationmanager.h \
    helper.h \
    fomodinstallerdialog.h \
    finddialog.h \
    filedialogmemory.h \
    executableslist.h \
    editexecutablesdialog.h \
    dummybsa.h \
    downloadmanager.h \
    downloadlistwidgetcompact.h \
    downloadlistwidget.h \
    downloadlistsortproxy.h \
    downloadlist.h \
    directoryrefresher.h \
    credentialsdialog.h \
    categoriesdialog.h \
    categories.h \
    bbcode.h \
    baincomplexinstallerdialog.h \
    archivetree.h \
    activatemodsdialog.h \
    moapplication.h \
    profileinputdialog.h \
    icondelegate.h \
    gameinfoimpl.h

FORMS    += \
    transfersavesdialog.ui \
    syncoverwritedialog.ui \
    simpleinstalldialog.ui \
    settingsdialog.ui \
		selectiondialog.ui \
    savegameinfowidget.ui \
    questionboxmemory.ui \
    queryoverwritedialog.ui \
    profilesdialog.ui \
    overwriteinfodialog.ui \
    nexusdialog.ui \
    motddialog.ui \
    modinfodialog.ui \
    messagedialog.ui \
    mainwindow.ui \
    lockeddialog.ui \
    installdialog.ui \
    fomodinstallerdialog.ui \
    finddialog.ui \
    editexecutablesdialog.ui \
    downloadlistwidgetcompact.ui \
    downloadlistwidget.ui \
    credentialsdialog.ui \
    categoriesdialog.ui \
    baincomplexinstallerdialog.ui \
    activatemodsdialog.ui \
    profileinputdialog.ui

INCLUDEPATH += ../shared ../archive ../uibase ../bsatk "$(BOOSTPATH)"

LIBS += -L"$(BOOSTPATH)/stage/lib"


CONFIG(debug, debug|release) {
	OUTDIR = $$OUT_PWD/debug
	DSTDIR = $$PWD/../../outputd
	LIBS += -L$$OUT_PWD/../shared/debug -L$$OUT_PWD/../bsatk/debug
	LIBS += -L$$OUT_PWD/../uibase/debug
} else {
	OUTDIR = $$OUT_PWD/release
	DSTDIR = $$PWD/../../output
	LIBS += -L$$OUT_PWD/../shared/release -L$$OUT_PWD/../bsatk/release
	LIBS += -L$$OUT_PWD/../uibase/release
	QMAKE_CXXFLAGS += /Zi
	QMAKE_LFLAGS += /DEBUG
}

CONFIG += embed_manifest_exe

# QMAKE_CXXFLAGS += /analyze

# QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'highestAvailable\' uiAccess=\'false\'\"

TRANSLATIONS = organizer_de.ts \
							 organizer_es.ts \
							 organizer_fr.ts \
							 organizer_zh_TW.ts \
               organizer_zh_CN.ts \
               organizer_cs.ts \
               organizer_tr.ts \
               organizer_ru.ts

!isEmpty(TRANSLATIONS) {
  isEmpty(QMAKE_LRELEASE) {
		win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
  }

  isEmpty(TS_DIR):TS_DIR = Translations

  TSQM.name = lrelease ${QMAKE_FILE_IN}
  TSQM.input = TRANSLATIONS
  TSQM.output = $$TS_DIR/${QMAKE_FILE_BASE}.qm
  TSQM.commands = $$QMAKE_LRELEASE ${QMAKE_FILE_IN}
  TSQM.CONFIG = no_link
  QMAKE_EXTRA_COMPILERS += TSQM
  PRE_TARGETDEPS += compiler_TSQM_make_all
} else:message(No translation files in project)

LIBS += -lmo_shared -luibase -lshell32 -lole32 -luser32 -ladvapi32 -lgdi32 -lPsapi -lVersion -lbsatk

DEFINES += UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS NOMINMAX

DEFINES += BOOST_DISABLE_ASSERTS NDEBUG
#DEFINES += QMLJSDEBUGGER


SRCDIR = $$PWD
SRCDIR ~= s,/,$$QMAKE_DIR_SEP,g
OUTDIR ~= s,/,$$QMAKE_DIR_SEP,g
DSTDIR ~= s,/,$$QMAKE_DIR_SEP,g

QMAKE_POST_LINK += mkdir -p $$quote($$DSTDIR) $$escape_expand(\\n)
QMAKE_POST_LINK += mkdir -p $$quote($$DSTDIR\\dlls) $$escape_expand(\\n)
QMAKE_POST_LINK += xcopy /y /i $$quote($$OUTDIR\\ModOrganizer*.exe) $$quote($$DSTDIR) $$escape_expand(\\n)
QMAKE_POST_LINK += xcopy /y /i $$quote($$OUTDIR\\ModOrganizer*.pdb) $$quote($$DSTDIR) $$escape_expand(\\n)
QMAKE_POST_LINK += xcopy /y /s /i $$quote($$SRCDIR\\stylesheets) $$quote($$DSTDIR)\\stylesheets $$escape_expand(\\n)
QMAKE_POST_LINK += xcopy /y /s /i $$quote($$SRCDIR\\tutorials) $$quote($$DSTDIR)\\tutorials $$escape_expand(\\n)
QMAKE_POST_LINK += xcopy /y /s /i $$quote($$SRCDIR\\*.qm) $$quote($$DSTDIR)\\translations $$escape_expand(\\n)

CONFIG(debug, debug|release) {
	QMAKE_POST_LINK += copy $$quote($$SRCDIR\\..\\dlls.manifest.debug) $$quote($$DSTDIR)\\dlls\\dlls.manifest $$escape_expand(\\n)
} else {
	QMAKE_POST_LINK += copy $$quote($$SRCDIR\\..\\dlls.manifest) $$quote($$DSTDIR)\\dlls $$escape_expand(\\n)
}

RESOURCES += \
		resources.qrc \
    stylesheet_resource.qrc

RC_FILE += \
    app_icon.rc

OTHER_FILES += \
    version.rc \
    tutorials/firststeps.qml \
    tutorials/tutorials.js \
    tutorials/tutorial_firststeps_main.js \
    tutorials/tutorial_firststeps_settings.js \
    tutorials/tutorials_settingsdialog.qml \
    tutorials/tutorials_mainwindow.qml \
    tutorials/Highlight.qml \
    tutorials/TutorialDescription.qml \
    tutorials/TutorialOverlay.qml \
    tutorials/tutorials_nexusdialog.qml \
    tutorials/tutorial_firststeps_browser.js \
    tutorials/tutorials_modinfodialog.qml \
    tutorials/tutorial_firststeps_modinfo.js \
    tutorials/tutorial_conflictresolution_main.js \
		tutorials/tutorial_conflictresolution_modinfo.js \
    app_icon.rc \
    dark.qss \
    stylesheets/dark.qss \
    tutorials/tutorial_window_installer.js \
    tutorials/tutorials_installdialog.qml