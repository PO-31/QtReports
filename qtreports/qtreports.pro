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
    src/engine.cpp \
    src/tags/summary.cpp \
    src/tags/box.cpp \
    src/tags/cellcontents.cpp \
    src/tags/crosstab.cpp \
    src/tags/crosstabgroup.cpp \
    src/tags/crosstabheader.cpp \
    src/tags/crosstabcell.cpp \
    src/tags/variable.cpp

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
    include/qtreports/engine.hpp \
    src/tags/summary.hpp \
    src/tags/box.hpp \
    src/tags/cellcontents.hpp \
    src/tags/crosstab.hpp \
    src/tags/crosstabgroup.hpp \
    src/tags/crosstabheader.hpp \
    src/tags/crosstabcell.hpp \
    src/tags/variable.hpp

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
