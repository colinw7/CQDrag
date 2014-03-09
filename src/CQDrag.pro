TEMPLATE = lib

TARGET = CQDrag

DEPENDPATH += .

CONFIG += staticlib

QT += widgets

# Input
HEADERS += \
../include/CQDrag.h \

SOURCES += \
CQDrag.cpp \

OBJECTS_DIR = ../obj

DESTDIR = ../lib

INCLUDEPATH += \
. \
../include \
