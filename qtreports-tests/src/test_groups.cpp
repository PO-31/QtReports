#include "test_groups.hpp"

#include <QTest>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QFileSystemModel>
#include <QDebug>

#include <qtreports/engine.hpp>

Test_Groups::Test_Groups( QObject * parent ) :
    QObject( parent ) {}

Test_Groups::~Test_Groups() {}

void    Test_Groups::engine()
{
    QString reportPath = QFINDTESTDATA( "../samples/reports/test/test.group.qreport" );
    //qDebug() << endl << "Used report: " << reportPath;
    qtreports::Engine engine( reportPath );
    QVERIFY2( engine.isOpened(), engine.getLastError().toStdString().c_str() );
}
