#include "replacer.hpp"
#include <QRegularExpression>
#include <QImage>
#include <QByteArray>
#include <QDebug>

namespace qtreports
{
    namespace detail
    {

        Replacer::Replacer() {}

        Replacer::~Replacer() {}

        QString     Replacer::replaceParameters( const QString & text, const ReportPtr & report )
        {
            auto newText = text;
            QRegularExpression expr( "(\\$P\\{\\w+\\})", QRegularExpression::CaseInsensitiveOption );
            auto iterator = expr.globalMatch( newText );
            while( iterator.hasNext() )
            {
                auto match = iterator.next();
                auto name = match.captured( 1 ).remove( 0, 3 ).remove( -1, 1 );
                auto parameter = report->getParameter( name );
                newText.replace( match.captured( 1 ), parameter.toString() ); //need fix for classname
            }

            return newText;
        }

        bool    Replacer::replaceParametersInTextWidget( const TextWidgetPtr & widget, const ReportPtr & report )
        {
            auto text = widget->getText();
            auto replacedText = replaceParameters( text, report );
            widget->setText( replacedText );

            return true;
        }

        bool    Replacer::replaceParametersInSection( const SectionPtr & section, const ReportPtr & report )
        {
            if( section.isNull() )
            {
                m_lastError = "Section is empty.";
                return false;
            }

            for( auto && band : section->getBands() )
            {
                for( auto && textWidget : band->getTextWidgets() )
                {
                    if( !replaceParametersInTextWidget( textWidget, report ) )
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool    Replacer::replaceParameters( const ReportPtr & report )
        {
            if( report.isNull() )
            {
                m_lastError = "Report is empty.";
                return false;
            }

            auto detail = report->getDetail();
            if( detail.isNull() )
            {
                m_lastError = "Report->Detail is empty.";
                return false;
            }

            if( !replaceParametersInSection( detail, report ) )
            {
                return false;
            }

            auto title = report->getTitle();
            if( !title.isNull() && !replaceParametersInSection( title, report ) )
            {
                return false;
            }

            return true;
        }

        QString     Replacer::replaceField( const QString & text, const ReportPtr & report, int i )
        {
            auto newText = text;
            QRegularExpression expr( "(\\$F\\{\\w+\\})", QRegularExpression::CaseInsensitiveOption );
            auto iterator = expr.globalMatch( newText );
            while( iterator.hasNext() )
            {
                auto match = iterator.next();
                auto name = match.captured( 1 ).remove( 0, 3 ).remove( -1, 1 );
                auto parameter = report->getField( name )->getData( i );
                newText.replace( match.captured( 1 ), parameter );
            }

            return newText;
        }

        QImage  Replacer::replaceFieldImage( const QString & text, const ReportPtr & report, int i )
        {
            QRegularExpression expr( "(\\$F\\{\\w+\\})", QRegularExpression::CaseInsensitiveOption );
            auto iterator = expr.globalMatch( text );
            while( iterator.hasNext() )
            {
                auto match = iterator.next();
                auto name = match.captured( 1 ).remove( 0, 3 ).remove( -1, 1 );
                auto byteArray = report->getField( name )->getData< QByteArray >( i );
                auto image = QImage::fromData( byteArray );
                return image;
            }

            return QImage();
        }

        bool    Replacer::replaceFieldInTextWidget( const TextWidgetPtr & widget, const ReportPtr & report, int i )
        {
            auto text = widget->getOriginalText();
            auto replacedText = replaceField( text, report, i );
            widget->setText( replacedText );

            return true;
        }

        bool    Replacer::replaceFieldInImageWidget( const ImagePtr & widget, const ReportPtr & report, int i )
        {
            auto text = widget->getOriginalText();
            auto image = replaceFieldImage( text, report, i );
            auto size = widget->getSize();
            widget->setImage( image.scaled( size ) );

            return true;
        }

        bool    Replacer::replaceFieldInSection( const SectionPtr & section, const ReportPtr & report, int i )
        {
            if( section.isNull() )
            {
                m_lastError = "Section is empty.";
                return false;
            }

            for( auto && band : section->getBands() )
            {
                for( auto && textWidget : band->getTextWidgets() )
                {
                    if( !replaceFieldInTextWidget( textWidget, report, i ) )
                    {
                        return false;
                    }
                }

                for( auto && imageWidget : band->getImages() )
                {
                    if( !replaceFieldInImageWidget( imageWidget, report, i ) )
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        bool    Replacer::replace( const SectionPtr & section, const ReportPtr & report, int i )
        {
            if( !replaceFieldInSection( section, report, i ) )
            {
                return false;
            }
            if( !replaceParameters( report ) )
            {
                return false;
            }

            return true;
        }

        const QString   Replacer::getLastError() const
        {
            return m_lastError;
        }

    }
}
