#-------------------------------------------------
#
# Project created by QtCreator 2019-02-14T17:13:48
#
#-------------------------------------------------

QT       += core sql printsupport widgets

TARGET = qtreports
TEMPLATE = lib
CONFIG += c++14 skip_target_version_ext
DEFINES += QTREPORTS

qtreports_version=$$(QTREPORTS_VERSION)
isEmpty(qtreports_version) {
    VERSION = 0.0.0
} else {
    VERSION = $$qtreports_version
}

INCLUDEPATH += include/

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
    include/qtreports/converters/utils/replacer.hpp \
    include/qtreports/converters/convertertohtml.hpp \
    include/qtreports/converters/convertertopdf.hpp \
    include/qtreports/converters/convertertoqwidget.hpp \
    include/qtreports/parsers/parserfromxml.hpp \
    include/qtreports/tags/band.hpp \
    include/qtreports/tags/detail.hpp \
    include/qtreports/tags/ellipse.hpp \
    include/qtreports/tags/field.hpp \
    include/qtreports/tags/group.hpp \
    include/qtreports/tags/image.hpp \
    include/qtreports/tags/line.hpp \
    include/qtreports/tags/object.hpp \
    include/qtreports/tags/querystring.hpp \
    include/qtreports/tags/rect.hpp \
    include/qtreports/tags/report.hpp \
    include/qtreports/tags/section.hpp \
    include/qtreports/tags/statictext.hpp \
    include/qtreports/tags/style.hpp \
    include/qtreports/tags/textfield.hpp \
    include/qtreports/tags/textwidget.hpp \
    include/qtreports/tags/title.hpp \
    include/qtreports/tags/widget.hpp \
    include/qtreports/engine.hpp

QMAKE_CXXFLAGS += -std=c++14

DESTDIR = $$PWD/../build/lib/

unix {
    target.path = /usr/lib
    headers.files = include/*
    headers.path = /usr/include
    INSTALLS += headers target
}

win32 {
    CONFIG += dll static
}

linux-clang {
    QMAKE_CXXFLAGS += -Wdocumentation
}

build_coverage = $$(BUILD_COVERAGE)
equals(build_coverage, "TRUE") {
    CONFIG += coverage
}

coverage {
    QMAKE_CXXFLAGS_RELEASE -= -O2
    QMAKE_CLEAN += $$OBJECTS_DIR/*.gcda $$OBJECTS_DIR/*.gcno
    QMAKE_CXXFLAGS += -c -g -Wall -fprofile-arcs -ftest-coverage -O0
    LIBS += -lgcov

    CONFIG -= debug release
    CONFIG += release

    message(Code coverage collection enabled)
}
QMAKE_EXTRA_TARGETS += coverage

message("Target: $$TARGET")
message("Version $$VERSION")
message("Using config: $$CONFIG")
message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
