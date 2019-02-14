#pragma once
#ifndef ELLIPSE_HPP
#define ELLIPSE_HPP
#include <QSharedPointer>
#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <ellipse>

        Класс, реализующий тэг <ellipse>
        */
        class Ellipse : public Widget {

        public:
            Ellipse();
            ~Ellipse();

        private:

        };
        typedef QSharedPointer< Ellipse > EllipsePtr;

    }
}

#endif // ELLIPSE_HPP
