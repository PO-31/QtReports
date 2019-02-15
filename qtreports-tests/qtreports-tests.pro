QT += core gui sql widgets printsupport testlib

TARGET = qtreports-tests
TEMPLATE = app
CONFIG += release c++11
INCLUDEPATH += ../qtreports-lib/src/
win32: LIBS   += -L "$$PWD"/../build/qtreports-lib/
message(Lib path: "$$PWD"/../build/qtreports-lib/)
LIBS   += -lqtreports-lib

DESTDIR = $$PWD/../build/qtreports-tests/

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
    test_convertertohtml.hpp \
    test_convertertopdf.hpp \
    test_convertertoqwidget.hpp \
    test_engine.hpp \
    test_field.hpp \
    test_groups.hpp \
    test_parser.hpp

SOURCES += \
    main.cpp \
    test_convertertohtml.cpp \
    test_convertertopdf.cpp \
    test_convertertoqwidget.cpp \
    test_engine.cpp \
    test_field.cpp \
    test_groups.cpp \
    test_parser.cpp

QMAKE_CXXFLAGS += -std=c++11

message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")

