#-------------------------------------------------
#
# Project created by QtCreator 2010-03-19T13:53:32
#
#-------------------------------------------------

QT       += core gui sql webkit

TARGET = SeafoodTabbed
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Fishes.cpp

HEADERS  += mainwindow.h \
    Fishes.h

FORMS    += mainwindow.ui

databasefiles.sources = seafood.db
databasefiles.path = .

DEPLOYMENT += databasefiles

