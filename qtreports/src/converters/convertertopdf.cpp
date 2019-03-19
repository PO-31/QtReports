#include "convertertopdf.hpp"

#include <QPdfWriter>
#include <QPainter>

#include "convertertoqwidget.hpp"

namespace qtreports {
    namespace detail {

        ConverterToPDF::ConverterToPDF( const ReportPtr & report ) :
            m_report( report ),
            m_dpi( 600 ) {}

        ConverterToPDF::~ConverterToPDF() {}

        bool    ConverterToPDF::convert( const QString & path ) {
            return create( path );
        }

        void    ConverterToPDF::setDPI( int dpi )
        {
            m_dpi = dpi;
        }

        int     ConverterToPDF::getDPI() const
        {
            return m_dpi;
        }

        bool    ConverterToPDF::create( const QString & path ) {
            if( m_report.isNull() ) {
                m_lastError = "Report is empty";
                return false;
            }

            QPdfWriter writer(path);
            writer.setCreator("QReports Library");
            writer.setTitle(m_report->getName());
            writer.setResolution(75);
            QPainter painter(&writer);
            QFont reportFont;
            QPen reportPen;

            auto &styles = m_report->getStyles();
            auto index = styles.begin();
            auto *style = (*index).data();
            reportFont.setFamily(style->getFontName());
            reportFont.setPointSize(style->getFontSize());
            style->isItalic() ? reportFont.setItalic(true) : reportFont.setItalic(false);
            style->isBold() ? reportFont.setBold(true) : reportFont.setBold(false);
            style->isUnderline() ? reportFont.setUnderline(true) : reportFont.setUnderline(true);
            style->isStrikeThrough() ? reportFont.setStrikeOut(true) : reportFont.setStrikeOut(false);
            reportPen.setColor(style->getFontColor());

            painter.setFont(reportFont);
            painter.setPen(reportPen);

//            for (auto i = styles.begin(); i != styles.end(); ++i) {
//                auto *style = (*i).data();
//                reportFont.setFamily(style->getFontName());
//                style->isItalic() ? reportFont.setItalic(true) : reportFont.setItalic(false);
//                style->isBold() ? reportFont.setBold(true) : reportFont.setBold(false);
//                reportFont.setPointSize(style->getFontSize());
//            }

            auto title = m_report->getTitle();
            if(!title.isNull()) {
                for(auto && band : title->getBands()) {
                    createBand(band, painter);
                }
            }

//            ConverterToQWidget converter( m_report );
//            bool result = converter.convert( ConverterToQWidget::WidgetType::Report );
//            if( !result ) {
//                m_lastError = "Cannot convert to QWidget: " + converter.getLastError();
//                return false;
//            }

//            auto widget = converter.getQWidget();
//            widget->show();
//            widget->hide();
//            widget->resize( m_report->getSize() );

            //painter.drawText(500, 0, m_report->getTitle()->getName());

            //Only for Qt 5.3+
//            auto pageSize = writer.pageLayout().pageSize();
//            auto size = pageSize.sizePixels( m_dpi );
//            auto sizeInch = pageSize.size( QPageSize::Unit::Inch );
//            widget->resize( sizeInch.width() * m_dpi, sizeInch.height() * m_dpi );
//            writer.setResolution( m_dpi );

            //Inch 2.54, A4 inch size 8.26 x 11.69
           // qreal scale = 2 * 8.26;

            //widget->resize( widget->width(), rect.height() / scale );
           // painter.scale( scale, scale );

            /*
            auto height = m_printedWidget->height() * scale;
            auto count = static_cast< int >( std::ceil( height / rect.height() ) );
            for( int i = 0; i < count; ++i )
            {
                i != 0 ? printer->newPage() : 0;
                m_printedWidget->render( &painter, QPoint( 0, -i * rect.height() / scale ) );
            }
            */



            //widget->render( &painter );
            painter.end();
            return true;
        }

        void ConverterToPDF::createBand(QSharedPointer<Band> band, QPainter &painter)
        {
            for(auto && textField : band->getTextFields()) {
                if(textField->getText() != "") {
                    Qt::AlignmentFlag alignment = Qt::AlignCenter;
                    if ((textField->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                        alignment = Qt::AlignLeft;
                    if ((textField->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                        alignment = Qt::AlignRight;
                    if ((textField->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                        alignment = Qt::AlignCenter;
                    if ((textField->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                        alignment = Qt::AlignJustify;
                    int x = textField->getX();
                    int y = textField->getY();
                    int w = textField->getWidth();
                    int h = textField->getHeight();
                    painter.drawText(x, y, w, h, alignment, textField->getText());
                }
            }

            for(auto && staticText : band->getStaticTexts()) {
                if(staticText->getText() != "") {
                    Qt::AlignmentFlag alignment = Qt::AlignCenter;
                    if ((staticText->getAlignment() & Qt::AlignLeft) == Qt::AlignLeft)
                        alignment = Qt::AlignLeft;
                    if ((staticText->getAlignment() & Qt::AlignRight) == Qt::AlignRight)
                        alignment = Qt::AlignRight;
                    if ((staticText->getAlignment() & Qt::AlignHCenter) == Qt::AlignHCenter)
                        alignment = Qt::AlignCenter;
                    if ((staticText->getAlignment() & Qt::AlignJustify) == Qt::AlignJustify)
                        alignment = Qt::AlignJustify;

                    int x = staticText->getX();
                    int y = staticText->getY();
                    int w = staticText->getWidth();
                    int h = staticText->getHeight();
                    painter.drawText(x, y, w, h, alignment, staticText->getText());
                }
            }


            for(auto && image : band->getImages()) {
                QImage img = image->getImage();
                QRect imageRect;
                imageRect.setX(image->getX());
                imageRect.setY(image->getY());
                imageRect.setWidth(image->getWidth());
                imageRect.setHeight(image->getHeight());
                painter.drawImage(imageRect, img);
            }

            for(auto && line : band->getLines()) {
                int x1 = line->getX();
                int y1 = line->getY();
                int x2 = x1 + line->getWidth() + 300;
                int y2 = y1 + line->getHeight() + 200;
                QLine qline(x1, y1, x2, y2);
                painter.drawLine(qline);
            }

            for(auto && rect : band->getRects()) {
                painter.drawRect(rect->getRect());
            }

            for(auto && ellipse : band->getEllipses()) {
                painter.drawEllipse(ellipse->getRect());
            }
        }

        const QString   ConverterToPDF::getLastError() const {
            return m_lastError;
        }

    }
}
