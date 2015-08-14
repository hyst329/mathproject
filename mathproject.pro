TEMPLATE = subdirs

SUBDIRS = ide interpreter kernel library \
    plotter
interpreter.depends = kernel

OTHER_FILES += \
               .gitignore \
               uncrustify.cfg

CONFIG += windeployqt
