#include <QPdfWriter>
#include <QPainter>
#include "convertertoqwidget.hpp"
#include "convertertopdf.hpp"

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

            ConverterToQWidget converter( m_report );
            bool result = converter.convert( ConverterToQWidget::WidgetType::Report );
            if( !result ) {
                m_lastError = "Cannot convert to QWidget: " + converter.getLastError();
                return false;
            }

            auto widget = converter.getQWidget();
            widget->show();
            widget->hide();
            widget->resize( m_report->getSize() );

            QPdfWriter writer( path );
            writer.setCreator( "QReports Library" );
            writer.setTitle( m_report->getName() );

            QPainter painter( &writer );

            //Only for Qt 5.3+
            //auto pageSize = writer.pageLayout().pageSize();
            //auto size = pageSize.sizePixels( m_dpi );
            //auto sizeInch = pageSize.size( QPageSize::Unit::Inch );
            //widget->resize( sizeInch.width() * m_dpi, sizeInch.height() * m_dpi );
            //writer.setResolution( m_dpi );
            
            //Inch 2.54, A4 inch size 8.26 x 11.69
            qreal scale = 2 * 8.26;

            //widget->resize( widget->width(), rect.height() / scale );
            painter.scale( scale, scale );

            /*
            auto height = m_printedWidget->height() * scale;
            auto count = static_cast< int >( std::ceil( height / rect.height() ) );
            for( int i = 0; i < count; ++i )
            {
                i != 0 ? printer->newPage() : 0;
                m_printedWidget->render( &painter, QPoint( 0, -i * rect.height() / scale ) );
            }
            */

            widget->render( &painter );

            return true;
        }

        const QString   ConverterToPDF::getLastError() const {
            return m_lastError;
        }

    }
}
