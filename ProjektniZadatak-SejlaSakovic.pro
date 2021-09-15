#-------------------------------------------------
#
# Project created by QtCreator 2021-06-08T15:06:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjektniZadatak-SejlaSakovic
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    proizvodjac.cpp \
    potrosac.cpp

HEADERS  += dialog.h \
    proizvodjac.h \
    zajednickevarijable.h \
    potrosac.h

FORMS    += dialog.ui
