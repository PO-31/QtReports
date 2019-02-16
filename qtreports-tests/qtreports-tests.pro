QT += core gui sql widgets printsupport testlib

TARGET = qtreports-tests
TEMPLATE = app
CONFIG += c++14 release

INCLUDEPATH += $$PWD/../qtreports/include/

LIBS += -L"$$PWD"/../build/ -lqtreports

DESTDIR = $$PWD

DISTFILES += \
    DB/images.db \
    DB/testDB.db \
    reports/detail.qreport \
    reports/errored.qrxml \
    reports/field test.qreport \
    reports/full.qrxml \
    reports/group.qreport \
    reports/multy_group.qreport \
    reports/style test.qreport \
    reports/default.qreport \
    reports/html.qreport \
    reports/images.qrxml \
    reports/optional.qreport \
    reports/report test.qreport \
    reports/simple.qreport \
    reports/students.qreport \
    reports/text test.qreport \
    default.txt \
    query \
    script \
    sql script

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

message("Target: $$TARGET")
message("Using config: $$CONFIG")
message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")

