TEMPLATE = subdirs lib

DESTDIR = $$PWD/build/

SUBDIRS += \
    qtreports-lib \
    qtreports-tests

qtreports-tests.depends = qtreports-lib
