#pragma once
#ifndef BOX_HPP
#define BOX_HPP

#include "object.hpp"

namespace qtreports
{
    namespace detail
    {
        class Box: public Object {
        public:
            Box();
            ~Box();

            void        setBorder(const QString & border);
            void        setBorderColor(const QString & borderColor);
            QString     getBorder() const;
            QString     getBorderColor() const;

        private:
            QString m_border;
            QString m_borderColor;
        };
        typedef QSharedPointer<Box> BoxPtr;
    }
}

#endif // BOX_HPP
