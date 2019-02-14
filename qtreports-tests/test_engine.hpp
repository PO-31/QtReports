#pragma once
#ifndef TEST_ENGINE_HPP
#define TEST_ENGINE_HPP
#include <QObject>

class Test_Engine : public QObject {
    Q_OBJECT

public:
    explicit Test_Engine( QObject * parent = Q_NULLPTR );
    ~Test_Engine();

private slots:
    void    engine();

    void    open();
    void    close();

    void    setParameters();
    void    setConnection();
    void    setDataSource();
    void    setQuery();
    void    addScript();
    void    setDataModel();

    void    createPDF();
    void    createHTML();
    void    createWidget();
    void    createLayout();
    void    print();

    void    isOpened();
    void    getReport();
    void    getLastError();

};

#endif // TEST_ENGINE_HPP
