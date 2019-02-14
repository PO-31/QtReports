#include "band.hpp"

namespace qtreports {
    namespace detail {

        Band::Band() {}

        Band::~Band() {}

        void    Band::addStaticText( const StaticTextPtr & staticText ) {
            m_staticTexts.append( staticText );
            m_textWidgets.append( staticText );
        }

        const QVector< StaticTextPtr >    Band::getStaticTexts() const
        {
            return m_staticTexts;
        }

        const StaticTextPtr  Band::getStaticText( int index ) const {
            return m_staticTexts.value( index );
        }

        int     Band::getStaticTextsSize() const {
            return m_staticTexts.size();
        }

        void    Band::addTextField( const TextFieldPtr & textField ) {
            m_textFields.append( textField );
            m_textWidgets.append( textField );
        }

        const QVector< TextFieldPtr >    Band::getTextFields() const
        {
            return m_textFields;
        }

        const TextFieldPtr  Band::getTextField( int index ) const {
            return m_textFields.value( index );
        }

        int     Band::getTextFieldsSize() const {
            return m_textFields.size();
        }

        QVector< TextWidgetPtr >    Band::getTextWidgets() const
        {
            return m_textWidgets;
        }

        int     Band::getTextWidgetsSize() const
        {
            return m_textWidgets.size();
        }

        void    Band::addLine( const LinePtr & line )
        {
            m_lines.append( line );
        }

        const LinePtr  Band::getLine( int index ) const
        {
            return m_lines.value( index );
        }

        int     Band::getLinesSize() const
        {
            return m_lines.size();
        }

        const QVector< LinePtr >    Band::getLines() const
        {
            return m_lines;
        }

        void    Band::addRect( const RectPtr & rect )
        {
            m_rects.append( rect );
        }

        const RectPtr  Band::getRect( int index ) const
        {
            return m_rects.value( index );
        }

        int     Band::getRectsSize() const
        {
            return m_rects.size();
        }

        const QVector< RectPtr >    Band::getRects() const
        {
            return m_rects;
        }

        void    Band::addEllipse( const EllipsePtr & rect )
        {
            m_ellipses.append( rect );
        }

        const EllipsePtr  Band::getEllipse( int index ) const
        {
            return m_ellipses.value( index );
        }

        int     Band::getEllipsesSize() const
        {
            return m_ellipses.size();
        }

        const QVector< EllipsePtr >    Band::getEllipses() const
        {
            return m_ellipses;
        }

        void    Band::addImage( const ImagePtr & image )
        {
            m_images.append( image );
        }

        const ImagePtr  Band::getImage( int index ) const
        {
            return m_images.value( index );
        }

        int     Band::getImagesSize() const
        {
            return m_images.size();
        }

        const QVector< ImagePtr >   Band::getImages() const
        {
            return m_images;
        }

    }
}
