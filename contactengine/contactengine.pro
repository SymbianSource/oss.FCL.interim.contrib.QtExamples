#-------------------------------------------------
#
# Project created by QtCreator 2010-08-03T16:15:24
#
#-------------------------------------------------

QT       += core gui sql svg

TARGET = contactengine
TEMPLATE = app

CONFIG += debug

include( apptemplatesrc/apptemplate.pri)

DEPENDPATH += apptemplatesrc

DEFINES += USE_ORANGE_FW

SOURCES += main.cpp\
        mainwindow.cpp \
    contactsengine.cpp \
    dbtools.cpp \
    detailsgv.cpp \
    mainview.cpp \
    contactlist.cpp

HEADERS  += mainwindow.h \
    contactsengine.h \
    database.h \
    dbtools.h \
    database.h \
    detailsgv.h \
    mainview.h \
    contactlist.h

FORMS    += mainwindow.ui \
    ContactList.ui

CONFIG += mobility
MOBILITY = contacts messaging

unix:INCLUDEPATH += /home/johnk/libs/include/QtContacts /home/johnk/libs/include/
unix:LIBS += -L/home/johnk/libs/lib -lQtContacts

databasefiles.sources = contacts.csv
databasefiles.path = .

DEPLOYMENT += databasefiles

symbian {
    TARGET.UID3 = 0xec200759
    TARGET.CAPABILITY += ReadUserData WriteUserData ReadDeviceData WriteDeviceData
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    resouce.qrc

OTHER_FILES += \
    readme.txt
