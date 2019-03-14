#include <QApplication>
#include <QTest>
#include "test_engine.hpp"
#include "test_parser.hpp"
#include "test_convertertoqwidget.hpp"
#include "test_convertertopdf.hpp"
#include "test_convertertohtml.hpp"
#include "test_field.hpp"
#include "test_groups.hpp"

int main( int argc, char *argv[] ) {
    QApplication a( argc, argv );
    int result = 0;
    result |= QTest::qExec( new Test_Engine, argc, argv );
    result |= QTest::qExec( new Test_Parser, argc, argv );
    result |= QTest::qExec( new Test_ConverterToQWidget, argc, argv );
    result |= QTest::qExec( new Test_ConverterToPDF, argc, argv );
    result |= QTest::qExec( new Test_ConverterToHTML, argc, argv );
    result |= QTest::qExec( new Test_Field, argc, argv);
    result |= QTest::qExec( new Test_Groups, argc, argv);

    return result;
	//return a.exec();
}
