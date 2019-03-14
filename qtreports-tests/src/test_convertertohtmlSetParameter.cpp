#include <QTest>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <qtreports/engine.hpp>
#include <qtreports/converters/convertertohtml.hpp>
#include "test_convertertohtmlSetParameter.hpp"
#include <QDebug>

Test_ConverterToHTMLSetParameter::Test_ConverterToHTMLSetParameter( QObject * parent ) :
    QObject( parent )
{}

Test_ConverterToHTMLSetParameter::~Test_ConverterToHTMLSetParameter() {}

void    Test_ConverterToHTMLSetParameter::convert()
{
    QString reportPath = QFINDTESTDATA( "../samples/reports/tests-images/test.full.qrxml" );
    qDebug() << endl << "Used report: " << reportPath;

    qtreports::Engine engine;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

	QString name = "title";
    QString value = "Best Title in World";
    qDebug() << endl << "Used parameter name: " << name << " with value " << value;
    QVERIFY2( engine.setParameter( name, value ), engine.getLastError().toStdString().c_str() );

    QString dbPath = QFINDTESTDATA( "../samples/databases/tests-images.db" );
    qDebug() << endl << "Used db: " << dbPath;
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    auto db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( dbPath );
    QVERIFY2( db.open(), db.lastError().text().toStdString().c_str() );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    auto report = engine.getReport();

    qtreports::detail::ConverterToHTML converterToMemory( report );
    QVERIFY2( converterToMemory.convert(), converterToMemory.getLastError().toStdString().c_str() );
    QVERIFY( converterToMemory.getHTML() != QString() );
    QCOMPARE( converterToMemory.getLastError(), QString() );

    auto outPath = "test.pdf";
    qtreports::detail::ConverterToHTML converterToPath( report );
    QVERIFY2( converterToPath.convert( outPath ), converterToPath.getLastError().toStdString().c_str() );
    QVERIFY( converterToPath.getHTML() != QString() );
    QCOMPARE( converterToPath.getLastError(), QString() );

    QCOMPARE( QFile::exists( outPath ), true );
    QFile file( outPath );
    QVERIFY2( file.open( QIODevice::OpenModeFlag::ReadOnly ), file.errorString().toStdString().c_str() );
    QVERIFY( file.size() != 0 );
    file.close();
    QCOMPARE( QFile::remove( outPath ), true );
}

void    Test_ConverterToHTMLSetParameter::getHTML()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToHTML converter( report );

    QCOMPARE( converter.getHTML(), QString() );
}

void    Test_ConverterToHTMLSetParameter::getLastError()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToHTML converter( report );

    QCOMPARE( converter.getLastError(), QString() );
}
