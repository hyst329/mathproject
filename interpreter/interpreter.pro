CONFIG += c++11
TARGET = interpreter
TEMPLATE = app

SOURCES += \
    main.cpp

CONFIG += lex
CONFIG += yacc

include(flex.pri)
include(bison.pri)
FLEXSOURCES = grammar/mp.l
BISONSOURCES = grammar/mp.y
