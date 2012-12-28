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
#    src/advancekeyboard.cpp \
    src/programmingkeyboard.cpp \
    src/number.cpp

HEADERS  += src/mainwindow.h \
    src/button.h \
    src/lineedit.h \
    src/bineditor.h \
    src/numbersystemswitcher.h \
    src/basickeyboard.h \
#    src/advancekeyboard.h \
    src/programmingkeyboard.h \
    src/number.h

OBJECTS_DIR = obj/
MOC_DIR = moc/
