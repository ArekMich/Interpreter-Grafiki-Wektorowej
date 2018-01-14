#-------------------------------------------------
#
# Project created by QtCreator 2017-08-23T20:33:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GrafikaWektorowa
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myarcobject.cpp \
    mytabwidget.cpp

HEADERS  += mainwindow.h \
    myarcobject.h \
    mytabwidget.h

FORMS    += mainwindow.ui \
    mytabwidget.ui

RESOURCES += resources.qrc

DISTFILES +=

win32 {
    RC_FILE =   GrafikaWektorowa.rc

}

