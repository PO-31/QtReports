#pragma once
#ifndef TEXTWIDGET_HPP
#define TEXTWIDGET_HPP
#include <QString>
#include <QSharedPointer>
#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Базовый класс для тегов, имеющих текстовое содержание.

        Базовый класс для тегов, имеющих текстовое содержание.
        */
        class TextWidget : public Widget {

        public:
            TextWidget();
            ~TextWidget();

            /*! @~russian
            Устанавливает текст тэга. Параметры не будут заменены.
            @param[in] text Текст
            */
            void            setText( const QString & text );

            /*! @~russian
            Возвращает текущий текст тэга.
            */
            const QString   getText() const;

            /*! @~russian
            Устанавливает оригинальный текст тэга. Все параметры будут заменены на
            реальные значения. Итоговое значение можно получить с помощью getText()
            @param[in] text Текст
            */
            void            setOriginalText( const QString & text );

            /*! @~russian
            Возвращает оригинальный текст тэга.
            */
            const QString   getOriginalText() const;

        protected:
            QString     m_text;
            QString     m_originalText;

        };
        typedef QSharedPointer< TextWidget > TextWidgetPtr;

    }
}

#endif // TEXTWIDGET_HPP
