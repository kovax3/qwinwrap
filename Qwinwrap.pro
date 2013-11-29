#-------------------------------------------------
#
# Project created by QtCreator 2011-10-25T14:34:47
#
#-------------------------------------------------
QT       +=  phonon
TARGET = qwinwrap
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    objdesk.cpp

HEADERS  += mainwindow.h \
    objdesk.h

FORMS    += mainwindow.ui

RESOURCES += \
    images.qrc


TRANSLATIONS =  Qwinwrap_ar.ts

CODECFORTR = UTF-8

#install
target.path = /usr/bin/
 applications.path = /usr/share/applications
    applications.files =qwinwrap.desktop
icon.path = /usr/share/icons/hicolor/64x64/apps
    icon.files =qwinwrap.png
    INSTALLS += target\
                            applications\
                            icon
