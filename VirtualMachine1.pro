QT += core
QT -= gui

CONFIG += c++11
CXX_FLAGS += -std=c++11

TARGET = VirtualMachine1
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    tint.cpp \
    tryte.cpp \
    trit.cpp \
    bigint.cpp \
    translator.cpp \
    processor.cpp \
    tchar.cpp \
    tfloat.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    tint.h \
    trit.h \
    tryte.h \
    bigint.h \
    translator.h \
    processor.h \
    tchar.h \
    tfloat.h

RESOURCES += \
    resourses.qrc
