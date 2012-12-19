#-------------------------------------------------
#
# Project created by QtCreator 2012-11-14T21:59:02
#
#-------------------------------------------------

QT       += core gui

TARGET = Calculator
TEMPLATE = app

CONFIG += debug


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/button.cpp \
    src/lineedit.cpp \
    src/bineditor.cpp \
    src/numbersystemswitcher.cpp \
    src/basickeyboard.cpp \
    src/trigonometryfuncs.cpp \
    src/additionalprogrammingfuncs.cpp \
    src/advancekeyboard.cpp \
    src/programmingkeyboards.cpp

HEADERS  += src/mainwindow.h \
    src/button.h \
    src/lineedit.h \
    src/bineditor.h \
    src/numbersystemswitcher.h \
    src/basickeyboard.h \
    src/trigonometryfuncs.h \
    src/additionalprogrammingfuncs.h \
    src/advancekeyboard.h \
    src/programmingkeyboards.h

OBJECTS_DIR = obj/
MOC_DIR = moc/
