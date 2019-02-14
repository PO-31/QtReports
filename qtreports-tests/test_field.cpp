#include "test_field.hpp"
#include <QTest>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QFileSystemModel>
#include <engine.hpp>
#include <QDebug>

Test_Field::Test_Field(QObject *parent): QObject(parent)
{

}

void Test_Field::test()
{
    qtreports::detail::Field field;

    field.setClassName(QString("QString"));

    QCOMPARE(field.getClassName(), QString("QString"));

    field.setName(QString("Field test"));

    QCOMPARE(field.getName(), QString("Field test"));

    QVector < QVariant > data;

    data.append(QString("str1"));
    data.append(QString("str2"));

    field.setData(data);

    QCOMPARE(field.getData(0), QString("str1"));
    QCOMPARE(field.getData(1), QString("str2"));
}
