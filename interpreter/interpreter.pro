CONFIG += c++11
TARGET = interpreter
TEMPLATE = app

SOURCES += \
    main.cpp

CONFIG += lex
CONFIG += yacc

QMAKE_LEX = flex
QMAKE_YACC = bison
LEXSOURCES += grammar/mp.l
YACCSOURCES += grammar/mp.y
