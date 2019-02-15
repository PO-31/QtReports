TEMPLATE = subdirs lib

SUBDIRS += \
    qtreports \
    qtreports-tests

qtreports-tests.depends = qtreports
