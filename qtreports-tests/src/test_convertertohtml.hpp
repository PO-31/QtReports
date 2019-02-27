#pragma once
#ifndef TEST_CONVERTERTOHTML_HPP
#define TEST_CONVERTERTOHTML_HPP
#include <QObject>

class Test_ConverterToHTML : public QObject {
    Q_OBJECT

public:
    explicit Test_ConverterToHTML( QObject * parent = Q_NULLPTR );
    ~Test_ConverterToHTML();

private slots:
    void    convert();

    void    getHTML();
    void    getLastError();

};

#endif // TEST_CONVERTERTOHTML_HPP
