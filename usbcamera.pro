DESTDIR = $$PWD/_bin
QMAKE_PROJECT_DEPTH = 0
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

win32:INCLUDEPATH += C:\tools\opencv\build\include
win32:LIBS += -LC:\tools\opencv\build\x64\vc16\lib

unix:INCLUDEPATH += /usr/include/opencv4
unix:LIBS += -lopencv_core -lopencv_highgui -lopencv_videoio

