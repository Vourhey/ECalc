#-------------------------------------------------
#
# Project created by QtCreator 2012-11-14T21:59:02
#
#-------------------------------------------------

QT       += core gui

TARGET = Calculator
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/calculator.cpp \
    src/button.cpp \
    src/lineedit.cpp \
    src/bineditor.cpp \
    src/numbersystemswitcher.cpp

HEADERS  += src/mainwindow.h \
    src/calculator.h \
    src/button.h \
    src/lineedit.h \
    src/bineditor.h \
    src/numbersystemswitcher.h

OBJECTS_DIR = obj/
MOC_DIR = moc/
