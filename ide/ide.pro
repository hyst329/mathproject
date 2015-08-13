QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TARGET = ide
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp

CONFIG += windeployqt

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h

# ReplWidget written by pb82
include(replwidget/replwidget.pri)
