#include "test_convertertopdf.hpp"

#include <QTest>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDebug>

#include <qtreports/engine.hpp>
#include <qtreports/../../src/converters/convertertopdf.hpp>

Test_ConverterToPDF::Test_ConverterToPDF( QObject * parent ) :
    QObject( parent )
{}

Test_ConverterToPDF::~Test_ConverterToPDF() {}

void    Test_ConverterToPDF::convert()
{
    QString reportPath = QFINDTESTDATA( "../samples/reports/tests-images/test.full.qrxml" );
    qDebug() << endl << "Used report: " << reportPath;

    qtreports::Engine engine;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QMap < QString, QVariant > map;
    map[ "title" ] = "Best Title in World";
    qDebug() << endl << "Used map: " << map;
    QVERIFY2( engine.setParameters( map ), engine.getLastError().toStdString().c_str() );

    QString dbPath = QFINDTESTDATA( "../samples/databases/tests-images.db" );
    qDebug() << endl << "Used db: " << dbPath;
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
    auto db = QSqlDatabase::addDatabase( "QSQLITE" );
    db.setDatabaseName( dbPath );
    QVERIFY2( db.open(), db.lastError().text().toStdString().c_str() );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );

    auto report = engine.getReport();
    auto outPath = "test.pdf";

    qtreports::detail::ConverterToPDF converter( report );
    QVERIFY2( converter.convert( outPath ), converter.getLastError().toStdString().c_str() );
    QCOMPARE( converter.getDPI(), 600 );
    QCOMPARE( converter.getLastError(), QString() );

    QCOMPARE( QFile::exists( outPath ), true );
    QFile file( outPath );
    QVERIFY2( file.open( QIODevice::OpenModeFlag::ReadOnly ), file.errorString().toStdString().c_str() );
    QVERIFY( file.size() != 0 );
    file.close();
    QCOMPARE( QFile::remove( outPath ), true );
}

void    Test_ConverterToPDF::setDPI()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToPDF converter( report );

    converter.setDPI( 500 );
    QCOMPARE( converter.getDPI(), 500 );
}

void    Test_ConverterToPDF::getDPI()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToPDF converter( report );

    QCOMPARE( converter.getDPI(), 600 );
}

void    Test_ConverterToPDF::getLastError()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToPDF converter( report );

    QCOMPARE( converter.getLastError(), QString() );
}
