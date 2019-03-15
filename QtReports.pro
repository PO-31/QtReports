TEMPLATE = subdirs

SUBDIRS += qtreports qtreports-tests qtreports-viewer

qtreports-tests.depends = qtreports
qtreports-viewer.depends = qtreports

HEADERS += \
    qtreports/include/qtreports/crosstab.h \
    qtreports/include/qtreports/tags/crosstab.h

SOURCES += \
    qtreports/include/qtreports/crosstab.cpp \
    qtreports/include/qtreports/tags/crosstab.cpp
