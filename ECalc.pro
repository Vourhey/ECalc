#-------------------------------------------------
#
# Project created by QtCreator 2012-11-14T21:59:02
#
#-------------------------------------------------

QT       += core gui

TARGET = ECalc
TEMPLATE = app

CONFIG += debug_and_release
TRANSLATIONS += translations/ecalc_ru.ts


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/button.cpp \
    src/lineedit.cpp \
    src/bineditor.cpp \
    src/numbersystemswitcher.cpp \
    src/basickeyboard.cpp \
    src/advancekeyboard.cpp \
    src/programmingkeyboard.cpp \
    src/number.cpp \
#    src/history.cpp \
    src/calculator.cpp \
    src/calcobject.cpp

HEADERS  += src/mainwindow.h \
    src/button.h \
    src/lineedit.h \
    src/bineditor.h \
    src/numbersystemswitcher.h \
    src/basickeyboard.h \
    src/advancekeyboard.h \
    src/programmingkeyboard.h \
    src/number.h \
#    src/history.h \
    src/calculator.h \
    src/calcobject.h

OBJECTS_DIR = obj/
MOC_DIR = moc/

# Автоматически создаем файлы перевода .qm
!isEmpty(TRANSLATIONS) {

  isEmpty(QMAKE_LRELEASE) {
    win32:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
  }

  isEmpty(TS_DIR):TS_DIR = translations

  TSQM.name = lrelease ${QMAKE_FILE_IN}
  TSQM.input = TRANSLATIONS
  TSQM.output = $$TS_DIR/${QMAKE_FILE_BASE}.qm
  TSQM.commands = $$QMAKE_LRELEASE ${QMAKE_FILE_IN}
  TSQM.CONFIG = no_link
  QMAKE_EXTRA_COMPILERS += TSQM
  PRE_TARGETDEPS += compiler_TSQM_make_all
} else:message(No translation files in project)

