#-------------------------------------------------
#
# Project created by QtCreator 2010-08-03T16:15:24
#
#-------------------------------------------------

QT       += core gui webkit sql

TARGET = contactengine
TEMPLATE = app

CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    contactsengine.cpp \
    dbtools.cpp

HEADERS  += mainwindow.h \
    contactsengine.h \
    database.h \
    dbtools.h \
    database.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = contacts

databasefiles.sources = contacts.csv
databasefiles.path = .

DEPLOYMENT += databasefiles

symbian {
    TARGET.UID3 = 0xec200759
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
