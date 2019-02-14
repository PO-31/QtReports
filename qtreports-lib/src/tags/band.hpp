#pragma once
#ifndef BAND_HPP
#define BAND_HPP
#include <QVector>
#include <QSharedPointer>
#include "statictext.hpp"
#include "textfield.hpp"
#include "line.hpp"
#include "rect.hpp"
#include "ellipse.hpp"
#include "image.hpp"
#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <band>

        Класс, реализующий тэг <band>
        */
        class Band : public Widget {

        public:
            Band();
            ~Band();

            /*! @~russian
            Добавляет <staticText> в <band>
            @param[in] staticText Указатель на <staticText>
            */
            void                            addStaticText( const StaticTextPtr & staticText );

            /*! @~russian
            Возвращает вектор указателей на <staticText>
            */
            const QVector< StaticTextPtr >  getStaticTexts() const;

            /*! @~russian
            Возвращает указатель на <staticText> по индексу
            @param[in] index Индекс
            */
            const StaticTextPtr             getStaticText( int index ) const;

            /*! @~russian
            Возращает количество <staticText> в текущем <band>
            */
            int                             getStaticTextsSize() const;

            /*! @~russian
            Добавляем <textField> в <band>
            @param[in] textField Указатель на <textField>
            */
            void                            addTextField( const TextFieldPtr & textField );

            /*! @~russian
            Возвращает вектор указателей на <textField>
            */
            const QVector< TextFieldPtr >   getTextFields() const;

            /*! @~russian
            Возвращает указатель на <textField> по индексу
            @param[in] index индекс
            */
            const TextFieldPtr              getTextField( int index ) const;

            /*! @~russian
            Возращает количество <textField> в текущем <band>
            */
            int                             getTextFieldsSize() const;

            /*! @~russian
            Возвращает количество текстовых виджетов( <staticText>, <textField> )
            */
            int                             getTextWidgetsSize() const;

            /*! @~russian
            Возвращает вектор текстовых виджетов( <staticText>, <textField> )
            */
            QVector< TextWidgetPtr >        getTextWidgets() const;

            /*! @~russian
            Добавить <line> в <band>
            @param[in] line Указатель на <line>
            */
            void                            addLine( const LinePtr & line );

            /*! @~russian
            Возвращает указатель на <line> по индексу
            @param[in] index индекс
            */
            const LinePtr                   getLine( int index ) const;

            /*! @~russian
            Возращает количество <line> в текущем <band>
            */
            int                             getLinesSize() const;

            /*! @~russian
            Возвращает вектор указателей на <line>
            */
            const QVector< LinePtr >        getLines() const;

            /*! @~russian
            Добавляем <rect> в <band>
            @param[in] rect Указатель на <rect>
            */
            void                            addRect( const RectPtr & rect );

            /*! @~russian
            Возвращает указатель на <rect> по индексу
            @param[in] index индекс
            */
            const RectPtr                   getRect( int index ) const;

            /*! @~russian
            Возращает количество <rect> в текущем <band>
            */
            int                             getRectsSize() const;

            /*! @~russian
            Возвращает вектор указателей на <rect>
            */
            const QVector< RectPtr >        getRects() const;

            /*! @~russian
            Добавляем <ellipse> в <band>
            @param[in] ellipse Указатель на <ellipse>
            */
            void                            addEllipse( const EllipsePtr & ellipse );

            /*! @~russian
            Возвращает указатель на <ellipse> по индексу
            @param[in] index индекс
            */
            const EllipsePtr                getEllipse( int index ) const;

            /*! @~russian
           Возращает количество <ellipse> в текущем <band>
           */
            int                             getEllipsesSize() const;

            /*! @~russian
            Возвращает вектор указателей на <ellipse>
            */
            const QVector< EllipsePtr >     getEllipses() const;

            /*! @~russian
            Добавляет <image> в <band>
            @param[in] image Указатель на <image>
            */
            void                            addImage( const ImagePtr & image );

            /*! @~russian
            Возвращает указатель на <image> по индексу
            @param[in] index индекс
            */
            const ImagePtr                  getImage( int index ) const;

            /*! @~russian
            Возращает количество <image> в текущем <band>
            */
            int                             getImagesSize() const;

            /*! @~russian
            Возвращает вектор указателей на <image>
            */
            const QVector< ImagePtr >       getImages() const;

        private:
            QVector< StaticTextPtr >    m_staticTexts;
            QVector< TextFieldPtr >     m_textFields;
            QVector< TextWidgetPtr >    m_textWidgets;
            QVector< LinePtr >          m_lines;
            QVector< RectPtr >          m_rects;
            QVector< EllipsePtr >       m_ellipses;
            QVector< ImagePtr >         m_images;

        };
        typedef QSharedPointer< Band > BandPtr;

    }
}

#endif // BAND_HPP
