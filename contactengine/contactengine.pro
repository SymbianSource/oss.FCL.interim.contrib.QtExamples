#-------------------------------------------------
#
# Project created by QtCreator 2010-08-03T16:15:24
#
#-------------------------------------------------

QT       += core gui webkit

TARGET = contactengine
TEMPLATE = app

CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    contactsengine.cpp

HEADERS  += mainwindow.h \
    contactsengine.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = contacts

symbian {
    TARGET.UID3 = 0xec200759
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
