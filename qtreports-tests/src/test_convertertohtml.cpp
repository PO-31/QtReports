﻿#include "test_convertertohtml.hpp"

#include <QTest>
#include <QMap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QFile>
#include <QDebug>

#include <qtreports/engine.hpp>
#include <qtreports/../../src/converters/convertertohtml.hpp>

Test_ConverterToHTML::Test_ConverterToHTML( QObject * parent ) :
    QObject( parent )
{}

Test_ConverterToHTML::~Test_ConverterToHTML() {}

void    Test_ConverterToHTML::convert()
{
    QString reportPath;

    {
        qtreports::Engine engine;
        qtreports::detail::ConverterToHTML *converterToHTML = new qtreports::detail::ConverterToHTML( engine.getReport() );
        QCOMPARE(converterToHTML->convert("some_path"), false);
        delete converterToHTML;

        reportPath = QFINDTESTDATA("../samples/reports/test/test.empty.qreport");
        QVERIFY2( engine.open(reportPath) , engine.getLastError().toStdString().c_str());
        converterToHTML = new qtreports::detail::ConverterToHTML( engine.getReport() );
        QCOMPARE(converterToHTML->convert("some_path"), false);
        delete converterToHTML;
    }

    reportPath = QFINDTESTDATA( "../samples/reports/tests-images/test.full.qrxml" );

    qDebug() << endl << "Used report: " << reportPath;

    qtreports::Engine engine;
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );

    QMap < QString, QVariant > map;
    map[ "title" ] = "Best Title in World";
    map[ "param1" ] = "Best param1 in World";
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

    qtreports::detail::ConverterToHTML converterToMemory( report );
    QVERIFY2( converterToMemory.convert(), converterToMemory.getLastError().toStdString().c_str() );

    QVERIFY( converterToMemory.getHTML() != QString() );
    QCOMPARE( converterToMemory.getLastError(), QString() );


    {
        qtreports::detail::ConverterToHTML converterToErrorPath( report );
        auto outPath = "";
    #ifdef Q_OS_WIN
        outPath = "%.?";
    #else
        outPath = "testfile";
        QVERIFY(!QFile::exists(outPath));
        QFile file(outPath);
        QVERIFY(file.open(QFile::WriteOnly));
        file.write("\0");
        file.close();
        QVERIFY(file.setPermissions(QFile::ReadUser));
    #endif
        QVERIFY(!converterToErrorPath.convert( outPath ));
        QCOMPARE(converterToErrorPath.getLastError(), QString("The file can not be opened"));
    #ifndef Q_OS_WIN
        QVERIFY(file.remove());
    #endif
    }

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
    db.close();

    dbPath = QFINDTESTDATA( "../samples/databases/test.db" );
    reportPath = QFINDTESTDATA( "../samples/reports/test/sample.crosstab.qreport" );
    db.setDatabaseName(dbPath);
    QVERIFY2(db.open(), db.lastError().text().toStdString().c_str());
    QVERIFY2( engine.open( reportPath ), engine.getLastError().toStdString().c_str() );
    QVERIFY2( engine.setConnection( db ), engine.getLastError().toStdString().c_str() );
    qtreports::detail::ConverterToHTML converter(engine.getReport());
    QVERIFY2( converter.convert(), converter.getLastError().toStdString().c_str() );
    db.close();
}

void    Test_ConverterToHTML::getHTML()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToHTML converter( report );

    QCOMPARE( converter.getHTML(), QString() );
}

void    Test_ConverterToHTML::getLastError()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToHTML converter( report );

    QCOMPARE( converter.getLastError(), QString() );
}
