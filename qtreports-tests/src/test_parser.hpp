#pragma once
#ifndef TEST_PARSER_HPP
#define TEST_PARSER_HPP
#include <QObject>

class Test_Parser : public QObject {
    Q_OBJECT

public:
    explicit Test_Parser( QObject * parent = Q_NULLPTR );

private:
    void ReportTreeParseTest();
    void ReportTagParseTest();
    void TextTest();
    void ReportFieldParseTest();
    void ReportLineParseTest();
    void ReportStyleParseTest();

    void OptionalFieldsTest();
    void FullTest();


private slots:
    void    parse();
    void    getReport();
    void    getLastError();
    void    getLog();

};

#endif // TEST_PARSER_HPP
