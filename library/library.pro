TEMPLATE = aux

OTHER_FILES +=

DISTFILES += \
    matan.hem \
    matrix.hem \
    algebra.hem

DESTDIR = ..

library_headers.path = $$OUT_PWD/../library
library_headers.files = *.hem

INSTALLS += library_headers
