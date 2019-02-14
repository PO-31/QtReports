#pragma once
#ifndef TEST_CONVERTERTOQWIDGET_HPP
#define TEST_CONVERTERTOQWIDGET_HPP
#include <QObject>

class Test_ConverterToQWidget : public QObject {
    Q_OBJECT

public:
    explicit Test_ConverterToQWidget( QObject * parent = Q_NULLPTR );
    ~Test_ConverterToQWidget();

private slots:
    void    convert();

    void    isReport();
    void    isLayout();
    void    getType();
    void    getQWidget();
    void    getPage();
    void    getPages();
    void    getLastError();

};

#endif // TEST_CONVERTERTOQWIDGET_HPP
