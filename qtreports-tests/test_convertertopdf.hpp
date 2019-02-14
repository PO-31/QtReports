#pragma once
#ifndef TEST_CONVERTERTOPDF_HPP
#define TEST_CONVERTERTOPDF_HPP
#include <QObject>

class Test_ConverterToPDF : public QObject {
    Q_OBJECT

public:
    explicit Test_ConverterToPDF( QObject * parent = Q_NULLPTR );
    ~Test_ConverterToPDF();

private slots:
    void    convert();

    void    setDPI();
    void    getDPI();
    void    getLastError();

};

#endif // TEST_CONVERTERTOPDF_HPP
