#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T17:13:48
#
#-------------------------------------------------

QT       += sql sql printsupport widgets

TARGET = qtreports-lib
TEMPLATE = lib
VERSION = 0.3.0-pre
CONFIG += c++11
DEFINES += QTREPORTSLIB
INCLUDEPATH += $$PWD/src/

SOURCES += \
    src/converters/utils/replacer.cpp \
    src/converters/convertertohtml.cpp \
    src/converters/convertertopdf.cpp \
    src/converters/convertertoqwidget.cpp \
    src/parsers/parserfromxml.cpp \
    src/tags/band.cpp \
    src/tags/detail.cpp \
    src/tags/ellipse.cpp \
    src/tags/field.cpp \
    src/tags/group.cpp \
    src/tags/image.cpp \
    src/tags/line.cpp \
    src/tags/object.cpp \
    src/tags/querystring.cpp \
    src/tags/rect.cpp \
    src/tags/report.cpp \
    src/tags/section.cpp \
    src/tags/statictext.cpp \
    src/tags/style.cpp \
    src/tags/textfield.cpp \
    src/tags/textwidget.cpp \
    src/tags/title.cpp \
    src/tags/widget.cpp \
    src/engine.cpp

HEADERS += \
    src/converters/utils/replacer.hpp \
    src/converters/convertertohtml.hpp \
    src/converters/convertertopdf.hpp \
    src/converters/convertertoqwidget.hpp \
    src/parsers/parserfromxml.hpp \
    src/tags/band.hpp \
    src/tags/detail.hpp \
    src/tags/ellipse.hpp \
    src/tags/field.hpp \
    src/tags/group.hpp \
    src/tags/image.hpp \
    src/tags/line.hpp \
    src/tags/object.hpp \
    src/tags/querystring.hpp \
    src/tags/rect.hpp \
    src/tags/report.hpp \
    src/tags/section.hpp \
    src/tags/statictext.hpp \
    src/tags/style.hpp \
    src/tags/textfield.hpp \
    src/tags/textwidget.hpp \
    src/tags/title.hpp \
    src/tags/widget.hpp \
    src/engine.hpp

QMAKE_CXXFLAGS += -std=c++11

DESTDIR = $$PWD/../build/qtreports-lib/

unix {
    target.path = /usr/lib
    INSTALLS += target
    headers.files = $$HEADERS
    headers.path = /usr/include/qtreports/
    INSTALLS += headers
}

win32 {
    CONFIG += build_all
    CONFIG += staticlib
    VERSION = 1.0.0
    TARGET = $$qtLibraryTarget(qtreportslib)
}

linux-clang {
    QMAKE_CXXFLAGS += -Wdocumentation
}

coverage {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CLEAN += $$OBJECTS_DIR/*.gcda $$OBJECTS_DIR/*.gcno
    QMAKE_CXXFLAGS += -c -g -Wall -fprofile-arcs -ftest-coverage -O0
    LIBS += -lgcov

    message(Code coverage collection enabled)
}
QMAKE_EXTRA_TARGETS += coverage

message("Using config: $$CONFIG")
message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
