#pragma once
#ifndef TEST_FIELD_HPP
#define TEST_FIELD_HPP
#include <QObject>

class Test_Field : public QObject {
    Q_OBJECT

public:
    explicit Test_Field( QObject * parent = Q_NULLPTR );

private slots:
    void    test();

};

#endif // TEST_FIELD_HPP
