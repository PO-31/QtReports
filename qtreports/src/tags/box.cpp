#include "box.hpp"

namespace qtreports
{
    namespace detail
    {
        Box::Box()
        {
            m_border = "Thin";
            m_borderColor = "black";
        }
        Box::~Box(){}

        void Box::setBorder(const QString &border)
        {
            m_border = border;
        }

        void Box::setBorderColor(const QString &borderColor)
        {
            m_borderColor = borderColor;
        }

        QString Box::getBorder() const
        {
            return m_border;
        }

        QString Box::getBorderColor() const
        {
            return m_borderColor;
        }
    }
}
