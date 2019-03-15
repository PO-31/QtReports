#include "textfield.hpp"

namespace qtreports
{
    namespace detail
    {

        TextField::TextField() {}

        TextField::~TextField() {}

        void    TextField::setClassName( const QString & name )
        {
            m_className = name;
        }

        const QString   TextField::getClassName() const
        {
            return m_className;
        }

    }
}
