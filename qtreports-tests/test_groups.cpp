#include <QTest>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QFileSystemModel>
#include <engine.hpp>
#include "test_groups.hpp"
#include <QDebug>

Test_Groups::Test_Groups( QObject * parent ) :
    QObject( parent ) {}

Test_Groups::~Test_Groups() {}

void    Test_Groups::engine()
{
    QString reportPath = QFINDTESTDATA( "group.qreport" );
    //qDebug() << endl << "Used report: " << reportPath;
    qtreports::Engine engine( reportPath );
    QVERIFY2( engine.isOpened(), engine.getLastError().toStdString().c_str() );
}
