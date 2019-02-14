#include <QRegularExpression>
#include <QTest>
#include <QSize>
#include <parsers/parserfromxml.hpp>
#include "test_parser.hpp"
#include <QDebug>

Test_Parser::Test_Parser( QObject *parent ) :
    QObject( parent ) {}

void    Test_Parser::ReportTreeParseTest() {
    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/default.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );
      
    QString input_scheme = QFINDTESTDATA( "default.txt" );
    QFile scheme_file( input_scheme );

    QVERIFY2( scheme_file.open( QIODevice::ReadOnly | QIODevice::Text ), "Can't open default.txt file." );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVector<QString> classes;
    QByteArray line = scheme_file.readLine();

    QString curr_line;

    curr_line = line.data();

    curr_line.remove( curr_line.size() - 1, 1 );

    QString error( curr_line.toLatin1().data() );

    error += " can't be found";

    QVERIFY2( curr_line.compare( report->getName(), Qt::CaseInsensitive ) == 0, error.toLatin1().data() );

    classes.append( curr_line );

    line = scheme_file.readLine();

    curr_line = line.data();

    curr_line.remove( curr_line.size() - 1, 1 );

    /* Styles block */

    if( curr_line.compare( "Styles" ) == 0 )
    {
        int styles_num = report->getStyles().size();

        QVector<QString> styles;

        QVERIFY2( curr_line.compare( "Styles", Qt::CaseInsensitive ) == 0, "No 'Style' line in default.txt" );

        for( int i = 0; i < styles_num; ++i )
        {
            QVERIFY2( !scheme_file.atEnd(), "Styles reading error in default.txt: to few styles in default.txt" );

            line = scheme_file.readLine();

            curr_line = line.data();

            curr_line.remove( curr_line.size() - 1, 1 );

            QVERIFY2( curr_line.compare( "/Styles", Qt::CaseInsensitive ) != 0, "Styles reading error in default.txt: to few styles in default.txt" );

            styles.append( curr_line );
        }

        line = scheme_file.readLine();

        curr_line = line.data();

        curr_line.remove( curr_line.size() - 1, 1 );

        QVERIFY2( curr_line.compare( "/Styles", Qt::CaseInsensitive ) == 0, "Styles reading error in default.txt: can't find '/Styles' in default.txt or to much styles in file" );

        for( int i = 0; i < styles.size(); ++i )
        {
            error = "Style '" + styles.at( i ) + "' not parsed";
            QVERIFY2( !report->getStyle( styles.at( i ) ).isNull(), error.toLatin1().data() );
        }

        line = scheme_file.readLine();

        curr_line = line.data();

        curr_line.remove( curr_line.size() - 1, 1 );
    }

    /* Detail */

    if( curr_line.compare( "Detail" ) == 0 )
    {
        QVERIFY2( !report->getDetail().isNull(), "Detail block not parsed" );

        int bands_num = 0;

        while( !scheme_file.atEnd() )
        {
            line = scheme_file.readLine();

            curr_line = line.data();

            curr_line.remove( curr_line.size() - 1, 1 );

            if( curr_line.compare( "/Detail" ) == 0 )
            {
                QVERIFY2( bands_num == report->getDetail()->getBandsSize(), "To many bands parsed" );
                break;
            }

            if( curr_line.compare( "Band" ) == 0 )
            {
                QVERIFY2( bands_num < report->getDetail()->getBandsSize(), "To few bands parsed" );

                int static_text_num = 0, text_field_num = 0;

                while( !scheme_file.atEnd() )
                {
                    line = scheme_file.readLine();

                    curr_line = line.data();

                    curr_line.remove( curr_line.size() - 1, 1 );

                    if( curr_line.compare( "/Band" ) == 0 )
                    {
                        error = "To many static text objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( static_text_num == report->getDetail()->getBand( bands_num )->getStaticTextsSize(),
                            error.toLatin1().data() );

                        error = "To many text field objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( text_field_num == report->getDetail()->getBand( bands_num )->getTextFieldsSize(),
                            error.toLatin1().data() );

                        break;
                    }

                    if( curr_line.compare( "StaticText" ) == 0 )
                    {
                        error = "To few static text objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( static_text_num < report->getDetail()->getBand( bands_num )->getStaticTextsSize(),
                            error.toLatin1().data() );

                        ++static_text_num;
                    }

                    if( curr_line.compare( "TextField" ) == 0 )
                    {
                        error = "To few text field objects parsed in band number " + QString::number( bands_num ) +
                            " " + report->getDetail()->getBand( bands_num )->getName();
                        QVERIFY2( text_field_num < report->getDetail()->getBand( bands_num )->getTextFieldsSize(),
                            error.toLatin1().data() );

                        ++text_field_num;
                    }
                }

                ++bands_num;
            }
        }

        QVERIFY2( bands_num == report->getDetail()->getBandsSize(), "Detail block test error" );
    }
}

void    Test_Parser::ReportTagParseTest() {
    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/report test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVERIFY2( !report.isNull(), "Null ptr report returned" );

    QVERIFY2( report->getName().compare( "test_report" ) == 0, "Uncorrect report name" );
    /*
    QSize report_size = report->getSize();

    QVERIFY2( report_size.width() == 600, "Uncorrect report width");

    QVERIFY2( report_size.height() == 900, "Uncorrect report height");*/

    QString error = "Wrong query string in report test: '";
    error += report->getQuery();
    error += "'";

    //QVERIFY2( report->getQuery() == " select * from customers ", error.toLatin1().data());

    QVERIFY2( !report->getStyle( "Arial_Normal" ).isNull(), "Null ptr style returned in report test" );

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontSize() == 12, "Wrong font size in report test" );

    error = "Wrong font name in report test: '";
    error += report->getStyle( "Arial_Normal" )->getFontName();
    error += "'";

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontName() == "Arial", error.toLatin1().data() );

    error = "Wrong PDF font name in report test: '";
    error += report->getStyle( "Arial_Normal" )->getPDFFontName();
    error += "'";

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFFontName() == "c:\\tahoma.ttf", error.toLatin1().data() );

    error = "Wrong PDF encoding in report test: '";
    error += report->getStyle( "Arial_Normal" )->getPDFEncoding();
    error += "'";

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFEncoding() == "Cp1251", error.toLatin1().data() );
}

void    Test_Parser::TextTest() {
    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/text test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QString error;

    QVERIFY2( !report.isNull(), "Null ptr report returned in text test" );

    QVERIFY2( !report->getDetail().isNull(), "Null ptr detail in text test" );

    QVERIFY2( report->getDetail()->getBandsSize() == 1, "Wrong bands number in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 ).isNull(), "Null ptr band in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getHeight() == 400, "Wrong band height in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticTextsSize() == 1, "Not one static text in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 )->getStaticText( 0 ).isNull(), "Null ptr static text in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getPos().x() == 380 && report->getDetail()->getBand( 0 )->getStaticText( 0 )->getPos().y() == 0, "Wrong static text position in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getWidth() == 200, "Wrong static text width in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getHeight() == 20, "Wrong static text height in text test" );

    error = "Wrong static text in text test: '";
    error += report->getDetail()->getBand( 0 )->getStaticText( 0 )->getText();
    error += "'";

    QVERIFY2( report->getDetail()->getBand( 0 )->getStaticText( 0 )->getText() == "Тест !!", error.toLatin1().data() );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextFieldsSize() == 1, "Not one text field in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 )->getTextField( 0 ).isNull(), "Null ptr text field in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextField( 0 )->getPos().x() == 220 && report->getDetail()->getBand( 0 )->getTextField( 0 )->getPos().y() == 20, "Wrong text field position in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextField( 0 )->getWidth() == 100, "Wrong text field width in text test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getTextField( 0 )->getHeight() == 200, "Wrong text field height in text test" );
/*
    error = "Wrong text field in text test: '";
    error += report->getDetail()->getBand( 0 )->getTextFieldld( 0 )->getText();
    error += "'";
*/
    //QVERIFY2( report->getDetail()->getBand(0)->getTextField(0)->getText() == "$P{title}", error.toLatin1().data() );
}

void Test_Parser::ReportFieldParseTest()
{

    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/field test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();
    
    QVERIFY2( !report.isNull(), "Null ptr report returned in text test" );

    QVERIFY2( !report->getField( "Title" ).isNull(), "Null ptr field in field test" );

    QVERIFY2( report->getField("Title")->getClassName() == "QString", "Wrong className in field test");

    //QVERIFY2( report->getField("PersonName")->getData( 0 ) )
    
    
    //QVERIFY2( report->get().getBandsSize() == 1, "Wrong bands number in text test" );

    //QVERIFY2( !report-> getDetail()->getetBand( 0 ).isNull(), "Null ptr band in text test" );
    

    
}

void Test_Parser::ReportLineParseTest()
{
    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/line test.qreport" );
    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QString error;

    QVERIFY2( !report.isNull(), "Null ptr report returned in line test" );

    QVERIFY2( !report->getDetail().isNull(), "Null ptr detail in line test" );

    QVERIFY2( report->getDetail()->getBandsSize() == 1, "Wrong bands number in text test" );

    QVERIFY2( !report->getDetail()->getBand( 0 ).isNull(), "Null ptr band in line test" );

    QVERIFY2( !report->getDetail()->getBand( 0 )->getLine( 0 ).isNull(), "Null ptr in line test" );

   // QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getAlignment() == Qt::Alignment(), "Wrong line alignment in line test" );

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getHeight() == 25, "Wrong line height in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getPos().x() == 200 && report->getDetail()->getBand( 0 )->getLine( 0 )->getPos().y() == 20, "Wrong position in line test");

    // QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getRect() )
    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getSize() == QSize(5,2), "Wrong line size in line test");

   //  QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getStyle() == )

   //  QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getTagName())

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getWidth() == 10, "Wrong line width in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getX() == 10, "Wrong line X in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->getY() == 20, "wrong line Y in line test");

    QVERIFY2( report->getDetail()->getBand( 0 )->getLine( 0 )->isBold(), "Wrong line bold in line test");
}

void Test_Parser::ReportStyleParseTest()
{
    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/style test.qreport" );

    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QString error;

    QVERIFY2( !report.isNull(), "Null ptr report returned in style test" );

    QVERIFY2( !report->getStyle( "Arial_Normal" ).isNull(), "Null ptr band in style test" );

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontColor() == QColor("red"), "Wrong font color in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontName() == "Arial", "Wrong font name in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getFontSize() == 12, "Wrong font size in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFEncoding() == "Cp1251", "Wrong PDF encoding in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->getPDFFontName() == "c:\\tahoma.ttf", "Wrong PDF encoding in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isBold(), "Wrong bold in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isDefault(), "Wrong default in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isItalic(), "Wrong italic in style test");

    QVERIFY2( report->getStyle( "Arial_Normal" )->isPDFEmbedded(), "Wrong PDFEmbedded in style test");



}

void Test_Parser::OptionalFieldsTest()
{
    qtreports::detail::ParserFromXML parser;
    QString input = QFINDTESTDATA( "reports/optional.qreport" );

    QVERIFY2( parser.parse( input ), parser.getLastError().toStdString().c_str() );

    qtreports::detail::ReportPtr report = parser.getReport();

    QVERIFY( !report.isNull());

    QCOMPARE( report->getWidth(), 595 );
    QCOMPARE( report->getHeight(), 842 );

    QVERIFY( !report->getStyle("Optional_style").isNull() );

    QCOMPARE( report->getStyle("Optional_style")->getFontSize(), 12);
    QCOMPARE( report->getStyle("Optional_style")->isDefault(), false);
    QCOMPARE( report->getStyle("Optional_style")->isBold(), false);
    QCOMPARE( report->getStyle("Optional_style")->isItalic(), false);

    QVERIFY( !report->getDetail().isNull() );
    QVERIFY( !report->getDetail()->getBand(0).isNull() );
    QVERIFY( !report->getDetail()->getBand(0)->getStaticText(0).isNull() );

    QCOMPARE( report->getDetail()->getBand(0)->getStaticText(0)->getAlignment() & Qt::AlignLeft, Qt::AlignLeft);
    QCOMPARE( report->getDetail()->getBand(0)->getStaticText(0)->getAlignment() & Qt::AlignVCenter, Qt::AlignVCenter);
}

void    Test_Parser::FullTest() {
}

void    Test_Parser::parse() {
    ReportTreeParseTest();
    ReportTagParseTest();
    ReportStyleParseTest();
    ReportFieldParseTest();
    TextTest();

    OptionalFieldsTest();
    

    qtreports::detail::ParserFromXML parser;

    QCOMPARE( parser.parse( "" ), false );

    QFile file( "reports/errored.qrxml" );
    QVERIFY2( file.open( QIODevice::OpenModeFlag::ReadOnly ), file.errorString().toStdString().c_str() );
    QVERIFY( file.size() != 0 );
    QCOMPARE( parser.parse( "reports/errored.qrxml" ), false );
    file.close();

    QString reportPath = QFINDTESTDATA( "reports/full.qrxml" );
    //qDebug() << endl << "Used report: " << reportPath;

    QVERIFY2( parser.parse( reportPath ), parser.getLastError().toStdString().c_str() );
    QVERIFY( parser.getLog() != QString() );
    QVERIFY( parser.getReport() != qtreports::detail::ReportPtr() );
    QCOMPARE( parser.getLastError(), QString() );
    //QWARN( parser.getLog().toStdString().c_str() );

    auto report = parser.getReport();

    QVERIFY( !report.isNull() );
    QCOMPARE( report->getTagName(), QString( "report" ) );
    QCOMPARE( report->getName(), QString( "full_report" ) );
    QCOMPARE( report->getWidth(), 600 );
    QCOMPARE( report->getHeight(), 500 );
    QCOMPARE( report->getSize(), QSize( 600, 500 ) );
    QCOMPARE( report->getOrientation(), QPrinter::Orientation::Landscape );
    QCOMPARE( report->getLeftMargin(), 11 );
    QCOMPARE( report->getRightMargin(), 12 );
    QCOMPARE( report->getTopMargin(), 13 );
    QCOMPARE( report->getBottomMargin(), 14 );
    QCOMPARE( report->getMargins(), QMargins( 11, 13, 12, 14 ) );
    QCOMPARE( report->getLastError(), QString() );
    QCOMPARE( report->getRowCount(), 0 );

    auto style = report->getStyle( "Arial_Normal" );
    QVERIFY( !style.isNull() );
    QCOMPARE( style->getTagName(), QString( "style" ) );
    QCOMPARE( style->getName(), QString( "Arial_Normal" ) );
    QCOMPARE( style->isDefault(), true );
    QCOMPARE( style->getFontName(), QString( "Arial" ) );
    QCOMPARE( style->getFontSize(), 12 );
    QCOMPARE( style->getFontColor(), QColor( "red" ) );
    QCOMPARE( style->isBold(), true );
    QCOMPARE( style->isItalic(), true );
    QCOMPARE( style->isUnderline(), true );
    QCOMPARE( style->isStrikeThrough(), true );
    QCOMPARE( style->getPDFFontName(), QString( "c:\\tahoma.ttf" ) );
    QCOMPARE( style->getPDFEncoding(), QString( "Cp1251" ) );
    QCOMPARE( style->isPDFEmbedded(), false );
    QCOMPARE( style->getLastError(), QString() );

    auto styles = report->getStyles();
    QVERIFY( !styles.isEmpty() );
    QCOMPARE( styles.size(), 1 );
    QCOMPARE( styles.value( "Arial_Normal" ), style );
    QCOMPARE( report->getDefaultStyle(), style );

    QCOMPARE( report->getQuery(), QString( "\n     select idImg, nameImg, image from images; \n  " ) );

    auto field_idImg = report->getField( "idImg" );
    QVERIFY( !field_idImg.isNull() );
    QCOMPARE( field_idImg->getTagName(), QString( "field" ) );
    QCOMPARE( field_idImg->getName(), QString( "idImg" ) );
    QCOMPARE( field_idImg->getClassName(), QString( "integer" ) );
    QCOMPARE( field_idImg->getData( 0 ), QString() );
    QCOMPARE( field_idImg->getLastError(), QString() );
    QCOMPARE( field_idImg->getRowCount(), 0 );

    auto field_nameImg = report->getField( "nameImg" );
    QVERIFY( !field_nameImg.isNull() );
    QCOMPARE( field_nameImg->getTagName(), QString( "field" ) );
    QCOMPARE( field_nameImg->getName(), QString( "nameImg" ) );
    QCOMPARE( field_nameImg->getClassName(), QString( "QString" ) );
    QCOMPARE( field_nameImg->getData( 0 ), QString() );
    QCOMPARE( field_nameImg->getLastError(), QString() );
    QCOMPARE( field_nameImg->getRowCount(), 0 );

    auto field_image = report->getField( "image" );
    QVERIFY( !field_image.isNull() );
    QCOMPARE( field_image->getTagName(), QString( "field" ) );
    QCOMPARE( field_image->getName(), QString( "image" ) );
    QCOMPARE( field_image->getClassName(), QString( "QString" ) );
    QCOMPARE( field_image->getData( 0 ), QString() );
    QCOMPARE( field_image->getData< QImage >( 0 ), QImage() );
    QCOMPARE( field_image->getLastError(), QString() );
    QCOMPARE( field_image->getRowCount(), 0 );

    auto fields = report->getFields();
    QVERIFY( !fields.isEmpty() );
    QCOMPARE( fields.size(), 3 );
    QCOMPARE( fields.value( "idImg" ), field_idImg );
    QCOMPARE( fields.value( "nameImg" ), field_nameImg );
    QCOMPARE( fields.value( "image" ), field_image );

    //FIX. Not full
    auto title = report->getTitle();
    QVERIFY( !title.isNull() );
    QCOMPARE( title->getTagName(), QString( "title" ) );
    QCOMPARE( title->getName(), QString() );
    QCOMPARE( title->getLastError(), QString() );
    //QCOMPARE( title->getWidth(), 600 );
    QCOMPARE( title->getHeight(), 200 );

    //FIX. Not full
    auto band_0_title = title->getBand( 0 );
    QVERIFY( !band_0_title.isNull() );
    QCOMPARE( band_0_title->getTagName(), QString( "band" ) );
    QCOMPARE( band_0_title->getName(), QString() );
    QCOMPARE( band_0_title->getLastError(), QString() );
    //QCOMPARE( band_0_title->getWidth(), 600 );
    QCOMPARE( band_0_title->getHeight(), 200 );
    QVERIFY( band_0_title->getLine( 0 ) != qtreports::detail::LinePtr() );
    QCOMPARE( band_0_title->getLines().empty(), false );
    QCOMPARE( band_0_title->getLinesSize(), 1 );
    QVERIFY( band_0_title->getRect( 0 ) != qtreports::detail::RectPtr() );
    QCOMPARE( band_0_title->getRects().empty(), false );
    QCOMPARE( band_0_title->getRectsSize(), 1 );
    QVERIFY( band_0_title->getEllipse( 0 ) != qtreports::detail::EllipsePtr() );
    QCOMPARE( band_0_title->getEllipses().empty(), false );
    QCOMPARE( band_0_title->getEllipsesSize(), 1 );
    QVERIFY( band_0_title->getImage( 0 ) != qtreports::detail::ImagePtr() );
    QCOMPARE( band_0_title->getImages().empty(), false );
    QCOMPARE( band_0_title->getImagesSize(), 1 );
    QVERIFY( band_0_title->getTextField( 0 ) != qtreports::detail::TextFieldPtr() );
    QCOMPARE( band_0_title->getTextFields().empty(), false );
    QCOMPARE( band_0_title->getTextFieldsSize(), 1 );
    QCOMPARE( band_0_title->getTextWidgets().empty(), false );
    QCOMPARE( band_0_title->getTextWidgets().size(), 2 );
    QCOMPARE( band_0_title->getTextWidgetsSize(), 2 );

    //FIX. Not full
    auto staticText_0_band_0_title = band_0_title->getStaticText( 0 );
    QVERIFY( !staticText_0_band_0_title.isNull() );
    QCOMPARE( staticText_0_band_0_title->getTagName(), QString( "staticText" ) );
    QCOMPARE( staticText_0_band_0_title->getName(), QString() );
    QCOMPARE( staticText_0_band_0_title->getLastError(), QString() );
    QCOMPARE( staticText_0_band_0_title->getX(), 0 );
    QCOMPARE( staticText_0_band_0_title->getY(), 40 );
    QCOMPARE( staticText_0_band_0_title->getWidth(), 200 );
    QCOMPARE( staticText_0_band_0_title->getHeight(), 20 );
    QCOMPARE( staticText_0_band_0_title->getPos(), QPoint( 0, 40 ) );
    QCOMPARE( staticText_0_band_0_title->getSize(), QSize( 200, 20 ) );
    QCOMPARE( staticText_0_band_0_title->getRect(), QRect( 0, 40, 200, 20 ) );
    QCOMPARE( staticText_0_band_0_title->getStyle(), QString( "Arial_Normal" ) );
    QCOMPARE( staticText_0_band_0_title->getAlignment() & Qt::AlignRight, Qt::AlignRight );
    QCOMPARE( staticText_0_band_0_title->getAlignment() & Qt::AlignTop, Qt::AlignTop );
    QCOMPARE( staticText_0_band_0_title->getText(), QString( "TopRight Text" ) );
    QCOMPARE( staticText_0_band_0_title->getOriginalText(), QString( "TopRight Text" ) );

    auto staticTexts_band_0_title = band_0_title->getStaticTexts();
    QVERIFY( !staticTexts_band_0_title.isEmpty() );
    QCOMPARE( staticTexts_band_0_title.size(), 1 );
    QCOMPARE( band_0_title->getStaticTextsSize(), 1 );
    QCOMPARE( staticTexts_band_0_title.value( 0 ), staticText_0_band_0_title );

    auto bands_title = title->getBands();
    QVERIFY( !bands_title.isEmpty() );
    QCOMPARE( bands_title.size(), 1 );
    QCOMPARE( title->getBandsSize(), 1 );
    QCOMPARE( bands_title.value( 0 ), band_0_title );

    //FIX. Not full
    auto detail = report->getDetail();
    QVERIFY( !detail.isNull() );
    QCOMPARE( detail->getTagName(), QString( "detail" ) );
    QCOMPARE( detail->getName(), QString() );
    QCOMPARE( detail->getLastError(), QString() );
    //QCOMPARE( detail->getWidth(), 600 );
    QCOMPARE( detail->getHeight(), 530 );

    //FIX. Not full
    auto band_0_detail = detail->getBand( 0 );
    QVERIFY( !band_0_detail.isNull() );
    QCOMPARE( band_0_detail->getTagName(), QString( "band" ) );
    QCOMPARE( band_0_detail->getName(), QString() );
    QCOMPARE( band_0_detail->getLastError(), QString() );
    //QCOMPARE( band_0_detail->getWidth(), 600 );
    QCOMPARE( band_0_detail->getHeight(), 200 );

    //FIX. Not full
    auto textField_0_band_0_detail = band_0_detail->getTextField( 0 );
    QVERIFY( !textField_0_band_0_detail.isNull() );
    QCOMPARE( textField_0_band_0_detail->getTagName(), QString( "textField" ) );
    QCOMPARE( textField_0_band_0_detail->getName(), QString() );
    QCOMPARE( textField_0_band_0_detail->getLastError(), QString() );
    QCOMPARE( textField_0_band_0_detail->getSize(), QSize( 100, 30 ) );
    QCOMPARE( textField_0_band_0_detail->getPos(), QPoint( 20, 20 ) );
    QCOMPARE( textField_0_band_0_detail->getClassName(), QString( "QString" ) );
    QCOMPARE( textField_0_band_0_detail->getText(), QString( "$P{param1}" ) );
    QCOMPARE( textField_0_band_0_detail->getOriginalText(), QString( "$P{param1}" ) );

    //FIX. Not full
    auto band_1_detail = detail->getBand( 1 );
    QVERIFY( !band_1_detail.isNull() );
    QCOMPARE( band_1_detail->getTagName(), QString( "band" ) );
    QCOMPARE( band_1_detail->getName(), QString() );
    QCOMPARE( band_1_detail->getLastError(), QString() );
    //QCOMPARE( band_1_detail->getWidth(), 600 );
    QCOMPARE( band_1_detail->getHeight(), 230 );

    //FIX. Not full
    auto textField_0_band_1_detail = band_1_detail->getTextField( 0 );
    QVERIFY( !textField_0_band_1_detail.isNull() );
    QCOMPARE( textField_0_band_1_detail->getTagName(), QString( "textField" ) );
    QCOMPARE( textField_0_band_1_detail->getName(), QString() );
    QCOMPARE( textField_0_band_1_detail->getLastError(), QString() );
    QCOMPARE( textField_0_band_1_detail->getText(), QString( "$F{idImg}" ) );
    QCOMPARE( textField_0_band_1_detail->getOriginalText(), QString( "$F{idImg}" ) );

    //FIX. Not full
    auto textField_1_band_1_detail = band_1_detail->getTextField( 1 );
    QVERIFY( !textField_1_band_1_detail.isNull() );
    QCOMPARE( textField_1_band_1_detail->getTagName(), QString( "textField" ) );
    QCOMPARE( textField_1_band_1_detail->getName(), QString() );
    QCOMPARE( textField_1_band_1_detail->getLastError(), QString() );
    QCOMPARE( textField_1_band_1_detail->getAlignment() & Qt::AlignLeft, Qt::AlignLeft );
    QCOMPARE( textField_1_band_1_detail->getAlignment() & Qt::AlignBottom, Qt::AlignBottom );
    QCOMPARE( textField_1_band_1_detail->getText(), QString( "\n          $F{nameImg}\n        " ) );
    QCOMPARE( textField_1_band_1_detail->getOriginalText(), QString( "\n          $F{nameImg}\n        " ) );

    //FIX. Not full
    QCOMPARE( band_1_detail->getTextFieldsSize(), 2 );

    //FIX. Not full
    auto image_0_band_1_detail = band_1_detail->getImage( 0 );
    QVERIFY( !image_0_band_1_detail.isNull() );
    QCOMPARE( image_0_band_1_detail->getTagName(), QString( "image" ) );
    QCOMPARE( image_0_band_1_detail->getName(), QString() );
    QCOMPARE( image_0_band_1_detail->getLastError(), QString() );
    QCOMPARE( image_0_band_1_detail->getSize(), QSize( 425, 200 ) );
    QCOMPARE( image_0_band_1_detail->getPos(), QPoint( 102, 0 ) );
    QCOMPARE( image_0_band_1_detail->getText(), QString( "$F{image}" ) );
    QCOMPARE( image_0_band_1_detail->getOriginalText(), QString( "$F{image}" ) );
    QCOMPARE( image_0_band_1_detail->getImage(), QImage() );

    //FIX. Not full
    auto band_2_detail = detail->getBand( 2 );
    QVERIFY( !band_2_detail.isNull() );
    QCOMPARE( band_2_detail->getTagName(), QString( "band" ) );
    QCOMPARE( band_2_detail->getName(), QString() );
    QCOMPARE( band_2_detail->getLastError(), QString() );
    //QCOMPARE( band_2_detail->getWidth(), 600 );
    QCOMPARE( band_2_detail->getHeight(), 100 );

    //FIX. Not full
    auto rect_0_band_2_detail = band_2_detail->getRect( 0 );
    QVERIFY( !rect_0_band_2_detail.isNull() );
    QCOMPARE( rect_0_band_2_detail->getTagName(), QString( "rect" ) );
    QCOMPARE( rect_0_band_2_detail->getName(), QString() );
    QCOMPARE( rect_0_band_2_detail->getLastError(), QString() );
    QCOMPARE( rect_0_band_2_detail->getPos(), QPoint( 50, 0 ) );
    QCOMPARE( rect_0_band_2_detail->getSize(), QSize( 100, 100 ) );

    //FIX. Not full
    auto line_0_band_2_detail = band_2_detail->getLine( 0 );
    QVERIFY( !line_0_band_2_detail.isNull() );
    QCOMPARE( line_0_band_2_detail->getTagName(), QString( "line" ) );
    QCOMPARE( line_0_band_2_detail->getName(), QString() );
    QCOMPARE( line_0_band_2_detail->getLastError(), QString() );
    QCOMPARE( line_0_band_2_detail->getPos(), QPoint( 100, 0 ) );
    QCOMPARE( line_0_band_2_detail->getSize(), QSize( 1, 100 ) );

    //FIX. Not full
    auto ellipse_0_band_2_detail = band_2_detail->getEllipse( 0 );
    QVERIFY( !ellipse_0_band_2_detail.isNull() );
    QCOMPARE( ellipse_0_band_2_detail->getTagName(), QString( "ellipse" ) );
    QCOMPARE( ellipse_0_band_2_detail->getName(), QString() );
    QCOMPARE( ellipse_0_band_2_detail->getLastError(), QString() );
    QCOMPARE( ellipse_0_band_2_detail->getPos(), QPoint( 50, 0 ) );
    QCOMPARE( ellipse_0_band_2_detail->getSize(), QSize( 100, 100 ) );

    //FIX. Not full
    QCOMPARE( detail->getBandsSize(), 3 );
}

void    Test_Parser::getReport() {
    qtreports::detail::ParserFromXML parser;
    QVERIFY( parser.getReport().isNull() );
}

void    Test_Parser::getLastError() {
    qtreports::detail::ParserFromXML parser;
    QCOMPARE( parser.getLastError(), QString() );

    QString reportPath = QFINDTESTDATA( "reports/errored.qrxml" );
    //qDebug() << endl << "Used report: " << reportPath;
    QCOMPARE( parser.parse( reportPath ), false );
    QVERIFY( parser.getLastError() != QString() );
}

void    Test_Parser::getLog() {
    qtreports::detail::ParserFromXML parser;
    QCOMPARE( parser.getLog(), QString() );

    QString reportPath = QFINDTESTDATA( "reports/full.qrxml" );
    //qDebug() << endl << "Used report: " << reportPath;
    QVERIFY2( parser.parse( reportPath ), parser.getLastError().toStdString().c_str() );
    QVERIFY( parser.getLog() != QString() );
}
