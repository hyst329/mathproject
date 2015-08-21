QT += core

CONFIG += c++11
TARGET = kernel
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
    Array.h \
    AST.h \
    BuiltinFunctions.h \
    Error.h \
    Matrix.h \
    NullType.h \
    Type.h \
    Function.h \
    StringType.h \
    ReferenceType.h

SOURCES += \
    Array.cpp \
    AST.cpp \
    BuiltinFunctions.cpp \
    Error.cpp \
    Matrix.cpp \
    NullType.cpp \
    placeholder.cpp \
    Type.cpp \
    Function.cpp \
    StringType.cpp \
    ReferenceType.cpp

#DESTDIR = ..
