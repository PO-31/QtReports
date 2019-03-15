#pragma once
#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QString>
#include <QPoint>
#include <QSize>
#include <QRect>
#include <QSharedPointer>

#include "style.hpp"
#include "object.hpp"

namespace qtreports
{
    namespace detail
    {
        /*! @~russian
        @brief Базовый класс для тэгов, которые подлежат отображению
        
        Базовый класс для тэгов, которые подлежат отображению.
        Координаты объекта являются локальными относительно родительского объекта.
        */
        class Widget : public Object {

        public:
            Widget();
            virtual ~Widget();

            /*! @~russian
            Устанавливает положение объекта. 
            Аргумент - неотрицательные координаты объекта, с центром координат в
            верхнем левом углу. Координаты задаются относительно внешнего объекта.
            @param[in] pos Положение объекта
            */
            void			setPosition( const QPoint & pos );
            
            /*! @~russian
            устанавливается координата х
            @param[in] x Новое значение координаты х
            */
            void			setX( int x );
            
            /*! @~russian
            устанавливается координата у
            @param[in] y Новое значение координаты у
            */
            void			setY( int y );
            
            /*! @~russian
            Устанавливается размер объекта
            @param[in] size размер объекта
            */
            void			setSize( const QSize & size );
            
             /*! @~russian
            Устанавливается ширина
            @param[in] width  ширина объекта
            */
            void			setWidth( int width );
            
             /*! @~russian
            Устанавливается высота
            @param[in] height высота объекта
            */
            void			setHeight( int height );

             /*! @~russian
            Устанавливается высота
            @param[in] rect высота объекта
            */
            void			setRect( const QRect & rect );
            
            /*! @~russian
            Устанавливается индекс стиля объекта
            @param[in] style Новый стиль объекта
            */
            /* Устанавливает индекс стиля объекта значением styleId, отрицательные значения - стиль по умолчанию. */
            //void            setStyle( const StylePtr & style );
            void            setStyle( const QString & style );

            void            setAlignment( Qt::Alignment alignment );
            
            Qt::Alignment   getAlignment();
            
            /*! @~russian
            Устанавливается позиция объекта
            Возвращается позиция объекта
            */
            const QPoint    getPos() const;
            
            /*! @~russian
            Устанавливается координата х
            Возвращает координату X 
            */
            int             getX() const;
            
            /*! @~russian
            Устанавливается координата у
            Возвращает координату Y 
            */
            int             getY() const;
            
            /*! @~russian
            Устанавливается размер объекта
            возвращает размер объекта
            */
            const QSize     getSize() const;
            
            /*! @~russian
            Возвращает текущую ширину объекта
            */
            int             getWidth() const;
            
            /*! @~russian
            Устанавливается высота объекта
            Возвращает высоту объекта
            */
            int             getHeight() const;

            const QRect     getRect() const;

            /* Возвращает индекс стиля. */
            //const StylePtr  getStyle() const;
            /*! @~russian
            Получаем индекс стиля
            Возвращает индекс стиля
            */
            const QString   getStyle() const;
            
            /*! @~russian
            Возвращаем индекс стиля
            */
            bool            isBold() const;
            
            /*! @~russian
            Возвращаем индекс стиля
            @param[in] isBold - bool 
            */
            void            setBold( bool isBold );

        protected:
            bool                    m_isBold;
            QRect					m_rect;
            Qt::Alignment           m_alignment;
            //StylePtr				m_style;
            QString				    m_style;

        };
        typedef QSharedPointer< Widget > WidgetPtr;

    }
}

#endif // WIDGET_HPP
