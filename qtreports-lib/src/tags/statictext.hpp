#pragma once
#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP
#include <QSharedPointer>
#include "textwidget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <staticText>

        Класс, реализующий тэг <staticText>
        */
        class StaticText : public TextWidget {

        public:
            StaticText();
            ~StaticText();

        private:

        };
        typedef QSharedPointer< StaticText > StaticTextPtr;

    }
}

#endif // STATICTEXT_HPP
