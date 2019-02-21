QT += core gui sql widgets printsupport

TARGET = qtreports-viewer
TEMPLATE = app
CONFIG += release c++14
INCLUDEPATH += ../qtreports/include/
LIBS   += -L"$$PWD"/../build/lib/
LIBS   += -lqtreports
DESTDIR = "$$PWD"/../build/viewer/

SOURCES += src/main.cpp

QMAKE_CXXFLAGS += -std=c++14

message("Using LIB: $$LIBS")
message("Using spec: $$QMAKESPEC")
message("Compiler: $$QMAKE_CXX")
