CONFIG += c++11
TARGET = kernel
TEMPLATE = lib

HEADERS += \
    Array.h \
    AST.h \
    BuiltinFunctions.h \
    Error.h \
    Matrix.h \
    NullType.h \
    Type.h \
    UserFunction.h

SOURCES += \
    Array.cpp \
    AST.cpp \
    BuiltinFunctions.cpp \
    Error.cpp \
    Matrix.cpp \
    NullType.cpp \
    placeholder.cpp \
    Type.cpp \
    UserFunction.cpp

