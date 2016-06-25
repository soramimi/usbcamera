#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T23:13:27
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Test
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ImageWidget.cpp

HEADERS  += MainWindow.h \
    ImageWidget.h

FORMS    += MainWindow.ui

win32:INCLUDEPATH += C:\opencv\build\include
win32:LIBS += -LC:\opencv\build\x86\vc12\lib

unix:LIBS += -lopencv_core -lopencv_highgui

