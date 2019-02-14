#pragma once
#ifndef TEST_GROUPS_HPP
#define TEST_GROUPS_HPP
#include <QObject>

class Test_Groups: public QObject {
    Q_OBJECT
public:
    explicit Test_Groups( QObject * parent = Q_NULLPTR );
    ~Test_Groups();

private slots:
    void    engine();
};

#endif // TEST_GROUPS_HPP
