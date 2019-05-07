QT += core gui sql widgets printsupport testlib

TARGET = qtreports-tests
TEMPLATE = app
CONFIG += c++14

INCLUDEPATH += "$$PWD"/../qtreports/include/

LIBS += -L"$$PWD"/../build/lib/
LIBS += -lqtreports

DESTDIR = $$PWD

DISTFILES += \
    default.txt

HEADERS += \
    src/test_convertertohtml.hpp \
    src/test_convertertopdf.hpp \
    src/test_convertertoqwidget.hpp \
    src/test_engine.hpp \
    src/test_field.hpp \
    src/test_groups.hpp \
    src/test_parser.hpp

SOURCES += \
    src/main.cpp \
    src/test_convertertohtml.cpp \
    src/test_convertertopdf.cpp \
    src/test_convertertoqwidget.cpp \
    src/test_engine.cpp \
    src/test_field.cpp \
    src/test_groups.cpp \
    src/test_parser.cpp

QMAKE_CXXFLAGS += -std=c++14

coverage {
    CONFIG -= release debug
    CONFIG += release
}
message("Target: $$TARGET")
message("Using config: $$CONFIG")
message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")

