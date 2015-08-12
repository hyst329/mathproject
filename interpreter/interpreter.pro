CONFIG += c++11
TARGET = interpreter
TEMPLATE = app

INCLUDEPATH += ..

include(flex.pri)
include(bison.pri)

FLEXSOURCES = grammar/mp.l
BISONSOURCES = grammar/mp.y

SOURCES += \
    main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../kernel/release/ -lkernel
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../kernel/debug/ -lkernel
else:unix: LIBS += -L$$OUT_PWD/../kernel/ -lkernel

INCLUDEPATH += $$PWD/../kernel
DEPENDPATH += $$PWD/../kernel
