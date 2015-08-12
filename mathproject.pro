TEMPLATE = subdirs

SUBDIRS = ide interpreter kernel library
interpreter.depends = kernel

OTHER_FILES += .gitignore

CONFIG += windeployqt
