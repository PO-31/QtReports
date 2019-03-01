#include <QFile>
#include <QTextStream>
#include <qtreports/converters/utils/replacer.hpp>
#include <qtreports/converters/convertertohtml.hpp>
//#include "cmath"
#include <cmath>

namespace qtreports {
    namespace detail {

        ConverterToHTML::ConverterToHTML( const ReportPtr & report ) :
            m_report( report ) {}

        ConverterToHTML::~ConverterToHTML() {}

        bool    ConverterToHTML::convert() {
            return createHTML();
        }

        bool    ConverterToHTML::convert( const QString & path ) {
            if( !convert() ) {
                return false;
            }

            QFile file( path );
            file.open(
                QIODevice::OpenModeFlag::WriteOnly |
                QIODevice::OpenModeFlag::Text |
                QIODevice::OpenModeFlag::Truncate
            );

            if( !file.isOpen() ) {
                m_lastError = "The file can not be opened";
                return false;
            }

            QTextStream stream( &file );
            stream.setCodec( "UTF-8" );
            stream << m_html;

            return true;
        }

        bool    ConverterToHTML::createHTML() {
            if(m_report.isNull())
            {
                m_lastError = "Report is empty";
                return false;
            }

            int pageHeight = m_report->getHeight();
            int pageWidth = m_report->getWidth();
            int freePageSpace = pageHeight;

            auto& styles = m_report->getStyles();

            m_html += QString("<!DOCTYPE html>\n"
                      "<html>\n"
                      " <head>\n"
                      "  <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>\n"
                      "  <title>Report</title>\n"
                      "  <style>\n"

                      "   div, .detail, .title, .band {\n"
                      "   position: relative;\n"
                      "   width: 100%;\n"
                      "   overflow: hidden;\n"
                      "   }\n"

                      "   @media print {\n"
                      "   .page {page-break-after: always;}\n"
                      "   }\n"

                      "   .page {\n"
                      "   width: %1px;\n"
                      "   height: %2px;\n" 
                      "   }\n"

                      "   .statictext, .textfield, .shape{\n"
                      "   position: absolute;\n"
                      "   background-color: transparent;\n"
                      "   }\n")
                    .arg(pageWidth).arg(pageHeight);

            for (auto i = styles.begin(); i != styles.end(); ++i) {
                auto* style = (*i).data();
                m_html += QString(
                    "   .%1 {\n"
                    "   font-family: %2 !important;\n"
                    "   font-size: %3pt !important;\n"
                    "   color: %4 !important;\n"
                    "   font-style: %5 !important;\n"
                    "   font-weight: %6 !important;\n"
                    "   text-decoration: %7 %8 !important;\n"
                    "   }\n"
                )
                .arg("style-" + style->getName())                       // 1 name
                .arg(style->getFontName())                              // 2 font-family
                .arg(style->getFontSize())                              // 3 font-size
                .arg(style->getFontColor().name())                      // 4 color
                .arg(style->isItalic() ? "italic" : "")                 // 5 font-style
                .arg(style->isBold() ? "800" : "300")                   // 6 font-weight
                .arg(style->isUnderline() ? "underline" : "")           // 7 text-docration
                .arg(style->isStrikeThrough() ? "line-through" : "");   // 8 text-decoration
            }
            QString defaultStyleName = m_report->getDefaultStyle().isNull() ? "" : "style-" + m_report->getDefaultStyle()->getName();

            m_html += QString("   .statictext {\n"
                      "   font-family: %3;\n"
                      "   font-size: %4pt;\n"
                      "   color: %5;\n"
                      "   font-style: %6;\n"
                      "   font-weight: %7;\n"
                      "   }\n"

                      "   .textfield {\n"
                      "   font-family: %8;\n"
                      "   font-size: %9pt;\n"
                      "   color: %10;\n"
                      "   font-style: %11;\n"
                      "   font-weight: %12;\n"
                      "   }\n"

                      "  </style>\n"
                      " </head>\n"
                      " <body>\n")
                    .arg("Verdana").arg("12").arg("black").arg("normal").arg("normal")
                    .arg("Verdana").arg("12").arg("black").arg("normal").arg("normal");

            m_html += "  <div class='page'>\n";

            auto title = m_report->getTitle();
            if(!title.isNull())
            {
                m_html += "   <div class='title'>\n";

                detail::Replacer replacer;
                if( !replacer.replace( title, m_report, 0 ) )
                {
                    m_lastError = "Error in replacing process: " + replacer.getLastError();
                    return false;
                }

            	for(auto && band : title->getBands())
            	{
                    QString elementStr = "";

                	for(auto && textField : band->getTextFields())
                	{                       
                        if (textField->getText() != "")
                        {
                            QString textAlignment = "left";
                            QString verticalAlignment = "middle";

                            if ((textField->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                                textAlignment = "left";
                            if ((textField->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                                textAlignment = "right";
                            if ((textField->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                                textAlignment = "center";
                            if ((textField->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                                textAlignment = "justify";

                            if ((textField->getAlignment() & Qt::AlignTop) == Qt::AlignTop)
                                verticalAlignment = "top";
                            if ((textField->getAlignment() & Qt::AlignBottom) == Qt::AlignBottom)
                                verticalAlignment = "bottom";
                            if ((textField->getAlignment() & Qt::AlignVCenter) == Qt::AlignVCenter)
                                verticalAlignment = "middle";
                            //if ((textField->getAlignment() & Qt::AlignBaseline) == Qt::AlignBaseline)
                            //    verticalAlignment = "baseline";

                            elementStr += QString("     <div class='textfield " + defaultStyleName + "' "
                               "style='left: %1px; top: %2px; "
                               "width: %3px; height: %4px; "
                               "text-align: %5; vertical-align: %6'>%7</div>\n")
                               .arg(textField->getX())
                               .arg(textField->getY())
                               .arg(textField->getWidth())
                               .arg(textField->getHeight())
                               .arg(textAlignment)
                               .arg(verticalAlignment)
                               .arg(textField->getText());
                        }
                    }

                    for(auto && staticText : band->getStaticTexts())
                    {
                        if (staticText->getText() != "")
                        {
                            QString textAlignment = "left";
                            QString verticalAlignment = "middle";

                            if ((staticText->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                                textAlignment = "left";
                            if ((staticText->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                                textAlignment = "right";
                            if ((staticText->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                                textAlignment = "center";
                            if ((staticText->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                                textAlignment = "justify";

                            if ((staticText->getAlignment() & Qt::AlignTop) == Qt::AlignTop)
                                verticalAlignment = "top";
                            if ((staticText->getAlignment() & Qt::AlignBottom) == Qt::AlignBottom)
                                verticalAlignment = "bottom";
                            if ((staticText->getAlignment() & Qt::AlignVCenter) == Qt::AlignVCenter)
                                verticalAlignment = "middle";
                            //if ((staticText->getAlignment() & Qt::AlignBaseline) == Qt::AlignBaseline)
                            //    verticalAlignment = "baseline";


                            elementStr += QString("     <div class='statictext " + defaultStyleName + "' "
                                "style='left: %1px; top: %2px; "
                                "width: %3px; height: %4px; "
                                "text-align: %5; vertical-align: %6'>%7</div>\n")
                                .arg(staticText->getX())
                                .arg(staticText->getY())
                                .arg(staticText->getWidth())
                                .arg(staticText->getHeight())
                                .arg(textAlignment)
                                .arg(verticalAlignment)
                                .arg(staticText->getText());
                        }
                    }

                    drawShapes(band, elementStr, 0);

                    freePageSpace -= band->getSize().height();

                    m_html += QString("    <div class='band' "
                             "style='height: %1px'>\n%2    </div>\n")
                             .arg(band->getSize().height())
                             .arg(elementStr);
            	}

            	m_html += "   </div>\n";
            }


            auto detail = m_report->getDetail();
            if(detail.isNull())
            {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            int pageCount = 0;
            int detailCount = m_report->getRowCount();

            for(int i = 0; i < detailCount; ++i)
            {
                detail::Replacer replacer;
                if( !replacer.replace( detail, m_report, i ) )
                {
                    m_lastError = "Error in replacing process: " + replacer.getLastError();
                    return false;
                }

                QString bandStr = "";

                for(auto && band : detail->getBands())
                {
                    bool isBandEmpty = true;
                    QString elementStr = "";

                    for(auto && textField : band->getTextFields())
                    {
                        if (textField->getText() != "")
                        {
                            QString textAlignment = "left";
                            QString verticalAlignment = "middle";

                            if ((textField->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                                textAlignment = "left";
                            if ((textField->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                                textAlignment = "right";
                            if ((textField->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                                textAlignment = "center";
                            if ((textField->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                                textAlignment = "justify";

                            if ((textField->getAlignment() & Qt::AlignTop) == Qt::AlignTop)
                                verticalAlignment = "top";
                            if ((textField->getAlignment() & Qt::AlignBottom) == Qt::AlignBottom)
                                verticalAlignment = "bottom";
                            if ((textField->getAlignment() & Qt::AlignVCenter) == Qt::AlignVCenter)
                                verticalAlignment = "middle";
                            //if ((textField->getAlignment() & Qt::AlignBaseline) == Qt::AlignBaseline)
                            //    verticalAlignment = "baseline";


                            elementStr += QString("     <div class='textfield " + defaultStyleName + "' "
                               "style='left: %1px; top: %2px; "
                               "width: %3px; height: %4px; "
                               "text-align: %5; vertical-align: %6'>%7</div>\n")
                               .arg(textField->getX())
                               .arg(textField->getY())
                               .arg(textField->getWidth())
                               .arg(textField->getHeight())
                               .arg(textAlignment)
                               .arg(verticalAlignment)
                               .arg(textField->getText());

                            isBandEmpty = false;
                        }
                    }

                    if (!isBandEmpty)
                    {                        
                        for(auto && staticText : band->getStaticTexts())
                        {
                            if (staticText->getText() != "")
                            {
                                QString textAlignment = "left";
                                QString verticalAlignment = "middle";

                                if ((staticText->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                                    textAlignment = "left";
                                if ((staticText->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                                    textAlignment = "right";
                                if ((staticText->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                                    textAlignment = "center";
                                if ((staticText->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                                    textAlignment = "justify";

                                if ((staticText->getAlignment() & Qt::AlignTop) == Qt::AlignTop)
                                    verticalAlignment = "top";
                                if ((staticText->getAlignment() & Qt::AlignBottom) == Qt::AlignBottom)
                                    verticalAlignment = "bottom";
                                if ((staticText->getAlignment() & Qt::AlignVCenter) == Qt::AlignVCenter)
                                    verticalAlignment = "middle";
                                //if ((staticText->getAlignment() & Qt::AlignBaseline) == Qt::AlignBaseline)
                                //    verticalAlignment = "baseline";

                                elementStr += QString("     <div class='statictext " + defaultStyleName + "' "
                                    "style='left: %1px; top: %2px; "
                                    "width: %3px; height: %4px; "
                                    "text-align: %5; vertical-align: %6'>%7</div>\n")
                                    .arg(staticText->getX())
                                    .arg(staticText->getY())
                                    .arg(staticText->getWidth())
                                    .arg(staticText->getHeight())
                                    .arg(textAlignment)
                                    .arg(verticalAlignment)
                                    .arg(staticText->getText());
                            }
                        }

                        drawShapes(band, elementStr, i);

                        if (freePageSpace < band->getSize().height())
                        {
                            m_html += QString("   <div class='detail'>\n%1   </div>\n")
                                    .arg(bandStr);

                            ++pageCount;
                            //колонтитул
                            freePageSpace = pageHeight - band->getSize().height();
                            m_html += "  </div>\n  <div class='page'>\n";
                            bandStr = "";
                        }
                        else
                            freePageSpace -= band->getSize().height();

                        bandStr += QString("    <div class='band' "
                                "style='height: %1px'>\n%2    </div>\n")
                                .arg(band->getSize().height())
                                .arg(elementStr);
                    }
                }

                m_html += QString("   <div class='detail'>\n%1   </div>\n")
                    .arg(bandStr);
            }

            ++pageCount;
            //Колонтитул
            m_html += "  </div>\n </body>\n</html>\n";
            return true;
        }

        void ConverterToHTML::drawShapes(QSharedPointer<Band> band, QString &elementStr, int index)
        {
            int imgCount = 0;

            for (auto && image : band->getImages())
            {
               QImage img = image->getImage();
                QBuffer imageBuffer;     //Создаём буффер для перевода картинки в QByteArray
                img.save(&imageBuffer, "png");  
                QString base64Img = "data:image/png;base64," + imageBuffer.data().toBase64(); //Преобразовываем картинку в текст

                elementStr += QString("     <div class='shape' "
                    "style='left: %1px; top: %2px; "
                    "width: %3px; height: %4px'>\n"
                    "      <img src='" + base64Img + "' alt='image_not_found'>\n     </div>\n")
                    .arg(image->getX())
                    .arg(image->getY())
                    .arg(image->getWidth())
                    .arg(image->getHeight());

                ++imgCount;
            }

            // Получаем количество линий
            int amountLines = band->getLines().size();
            int counterLines = 0;
            // Получаем количество не граничных линий
            int amountNotBorderLines = amountLines - 3;

            for( auto && line : band->getLines() )
            {
                bool isBorderLeft = false;
                float angleRad = atan2(line->getHeight(), line->getWidth());
                if(angleRad == 1.5208379f)
                    isBorderLeft = true;
                float lineWidth = sqrt(pow(line->getWidth(), 2) + pow(line->getHeight(), 2));

                if(isBorderLeft) { // Если линия вертикальная
                    if(counterLines != amountLines - 2) { // Если линия не последняя
                        elementStr += QString("     <div class='shape' "
                            "style='left: %1px; top: %2px; "
                            "width: %3px; height: %4px; "
                            "overflow: visible'>\n"
                            "      <div style='border-left: 1px solid black; height: %5px; width: 1px; "
                            "'></div>\n     </div>\n")
                            .arg(line->getX()) // устанавливаем координату X без изменений
                            .arg(line->getY())
                            .arg(line->getWidth())
                            .arg(line->getHeight())
                            .arg(lineWidth);
                        counterLines++;
                    }
                    else { // Если линия последняя
                        elementStr += QString("     <div class='shape' "
                            "style='left: %1px; top: %2px; "
                            "width: %3px; height: %4px; "
                            "overflow: visible'>\n"
                            "      <div style='border-left: 1px solid black; height: %5px; width: 1px; "
                            "'></div>\n     </div>\n")
                            // Смещаем координату X вправо на положение, равное amountNotBorderLines,
                            // умноженное на ширину линии. (Здесь ширина линии 1px, и нет возможности(пока что)
                            //                              получать ее из репорта).
                            .arg(line->getX() + amountNotBorderLines)
                            .arg(line->getY())
                            .arg(line->getWidth())
                            .arg(line->getHeight())
                            .arg(lineWidth)
                            ;
                        counterLines = 0;
                    }
                } else { // Если линия не вертикальная
                    elementStr += QString("     <div class='shape' "
                        "style='left: %1px; top: %2px; "
                        "width: %3px; height: %4px; "
                        "overflow: visible'>\n"
                        "      <div style='border-top: 1px solid black; height: 1px; width: %5px; "
                        "'></div>\n     </div>\n")
                        .arg(line->getX())
                        .arg(line->getY())
                        .arg(line->getWidth())
                        .arg(line->getHeight())
                        .arg(lineWidth)
                        ;
                }
            }

            for( auto && rect : band->getRects() )
            {
                elementStr += QString("     <div class='shape' "
                    "style='border: 1px solid black; left: %1px; top: %2px; "
                    "width: %3px; height: %4px;'></div>\n")
                    .arg(rect->getX())
                    .arg(rect->getY())
                    .arg(rect->getWidth())
                    .arg(rect->getHeight());
            }

            for( auto && ellipse : band->getEllipses() )
            {
                elementStr += QString("     <div class='shape' "
                    "style='border: 1px solid black; "
                    "left: %1px; top: %2px; "
                    "width: %3px; height: %4px; "
                    "-moz-border-radius: %5px / %6px; "
                    "-webkit-border-radius: %5px / %6px; "
                    "border-radius: %5px / %6px;'></div>\n")
                    .arg(ellipse->getX())
                    .arg(ellipse->getY())
                    .arg(ellipse->getWidth())
                    .arg(ellipse->getHeight())
                    .arg(ellipse->getWidth() / 2)
                    .arg(ellipse->getHeight() / 2);
            }
        }

        const QString   ConverterToHTML::getLastError() const {
            return m_lastError;
        }

        const QString   ConverterToHTML::getHTML() const {
            return m_html;
        }

    }
}
