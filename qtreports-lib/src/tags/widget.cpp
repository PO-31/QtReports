#include "widget.hpp"

namespace qtreports {
    namespace detail {

        Widget::Widget() :
            m_isBold( false ),
            m_rect( 0, 0, 0, 0 ),
            m_alignment( Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter ) {}

        Widget::~Widget() {}

        void	Widget::setPosition( const QPoint & pos ) {
            m_rect.setTopLeft( pos );
        }

        void    Widget::setX( int x ) {
            m_rect.setLeft( x );
        }

        void    Widget::setY( int y ) {
            m_rect.setTop( y );
        }

        void	Widget::setSize( const QSize & size ) {
            m_rect.setSize( size );
        }

        void    Widget::setWidth( int width ) {
            m_rect.setWidth( width );
        }

        void    Widget::setHeight( int height ) {
            m_rect.setHeight( height );
        }

        void	Widget::setRect( const QRect & rect ) {
            m_rect = rect;
        }
        /*
        void	Widget::setStyle( const StylePtr & style ) {
            m_style = style;
        }
        */
        void	Widget::setStyle( const QString & style )
        {
            m_style = style;
        }

        void    Widget::setAlignment( Qt::Alignment alignment ) {
            m_alignment = alignment;
        }

        Qt::Alignment   Widget::getAlignment() {
            return m_alignment;
        }

        const QPoint    Widget::getPos() const {
            return m_rect.topLeft();
        }

        int             Widget::getX() const {
            return m_rect.x();
        }

        int             Widget::getY() const {
            return m_rect.y();
        }

        const QSize     Widget::getSize() const {
            return m_rect.size();
        }

        int             Widget::getWidth() const {
            return m_rect.width();
        }

        int             Widget::getHeight() const {
            return m_rect.height();
        }

        const QRect     Widget::getRect() const {
            return m_rect;
        }
        /*
        const StylePtr  Widget::getStyle() const {
            return m_style;
        }
        */
        const QString   Widget::getStyle() const
        {
            return m_style;
        }

        bool    Widget::isBold() const {
            return m_isBold;
        }

        void    Widget::setBold( bool isBold ) {
            m_isBold = isBold;
        }


        /*
        bool	Widget::setParameter( const QString & name, const QVariant & value ) {
            QString _x( "x" ), _y( "y" ), _w( "w" ), _h( "h" ), _style_name( "style_name" );

            if( !value.isValid() ) {
                m_lastError = "Invalid parameter value";
                return false;
            }

            if( isEquals( name, _x ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_pos.setX( value.toInt() );

                return true;
            }

            if( isEquals( name, _y ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_pos.setY( value.toInt() );

                return true;
            }

            if( isEquals( name, _w ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setWidth( value.toInt() );
                return true;
            }

            if( isEquals( name, _h ) ) {
                if( value.type() != QVariant::Int ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_size.setHeight( value.toInt() );
                return true;
            }

            if( isEquals( name, _style_name ) ) {
                if( value.type() != QVariant::String ) {
                    m_lastError = "Invalid type for this argument";
                    return false;
                }

                m_styleName = value.toString();

                return true;
            }

            return Object::setParameter( name, value );
        }
        */

    }
}
