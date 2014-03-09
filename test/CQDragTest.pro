TEMPLATE = app

TARGET = CQDragTest

DEPENDPATH += .

QT += widgets

#CONFIG += debug

# Input
SOURCES += \
CQDragTest.cpp \

HEADERS += \
CQDragTest.h \

DESTDIR     = .
OBJECTS_DIR = .

INCLUDEPATH += \
. ../include \

unix:LIBS += \
-L../lib \
-lCQDrag \
