#pragma once
#ifndef TEST_CONVERTERTOHTMLSETPARAMETER_HPP_HPP
#define TEST_CONVERTERTOHTMLSETPARAMETER_HPP_HPP
#include <QObject>

class Test_ConverterToHTMLSetParameter : public QObject {
    Q_OBJECT

public:
    explicit Test_ConverterToHTMLSetParameter( QObject * parent = Q_NULLPTR );
    ~Test_ConverterToHTMLSetParameter();

private slots:
    void    convert();

    void    getHTML();
    void    getLastError();

};

#endif // TEST_CONVERTERTOHTMLSETPARAMETER_HPP
