#-------------------------------------------------
#
# Project created by QtCreator 2010-08-30T10:49:36
#
#-------------------------------------------------

QT       += core gui svg

TARGET = listElements
TEMPLATE = app


SOURCES += main.cpp\
    zodiacsign.cpp \
    mainwindow.cpp \
    zodiacmodel.cpp \
    zodiacdelegate.cpp \
    PLLayout.cpp


# DEFINES = USE_DELEGATE

HEADERS  += mainwindow.h \
    zodiacsign.h \
    zodiacmodel.h \
    zodiacdelegate.h \
    PLLayout.h

FORMS    += mainwindow.ui

symbian {
    TARGET.UID3 = 0xe5e9fbec
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    assets.qrc
