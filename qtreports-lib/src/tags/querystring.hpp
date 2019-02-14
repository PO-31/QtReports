#pragma once
#ifndef QUERYSTRING_HPP
#define QUERYSTRING_HPP
#include <QSharedPointer>
#include "object.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <queryString>

        Класс, реализующий тэг <queryString>
        */
        class QueryString : public Object {

        public:
            QueryString();
            ~QueryString();

            /*! @~russian
            Устанавливает текст <queryString>
            @param[in] text Строка
            */
            void            setText( const QString & text );

            /*! @~russian
            Возвращает текст <queryString>
            */
            const QString   getText() const;

        private:
            QString     m_text;

        };
        typedef QSharedPointer< QueryString > QueryStringPtr;

    }
}

#endif // QUERYSTRING_HPP
