#pragma once
#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP
#include <QString>
#include <QSharedPointer>
#include "textwidget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <textField>

        Класс, реализующий тэг <textField>
        */
        class TextField : public TextWidget {

        public:
            TextField();
            ~TextField();

            /*! @~russian
            Устанавливает имя класса. Данное значение будет использоваться
            при вычислении содержимого.
            @param[in] name Имя класса
            */
            void            setClassName( const QString & name );

            /*! @~russian
            Возвращает текущее имя класса.
            */
            const QString   getClassName() const;

        private:
            QString     m_className;

        };
        typedef QSharedPointer< TextField > TextFieldPtr;

    }
}

#endif // TEXTFIELD_HPP
