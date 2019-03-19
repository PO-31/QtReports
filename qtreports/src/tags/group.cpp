#include "group.hpp"

namespace qtreports {
    namespace detail {

        Group::Group() {}

        Group::~Group() {}

        void    Group::setExpression( const QString & text )
        {
            m_expression = text;
        }

        const QString   Group::getExpression() const
        {
            return m_expression;
        }

        void    Group::setHeader( const SectionPtr & header )
        {
            m_header = header;
        }

        const SectionPtr    Group::getHeader() const
        {
            return m_header;
        }

        void    Group::setFooter( const SectionPtr & footer )
        {
            m_footer = footer;
        }

        const SectionPtr    Group::getFooter() const
        {
            return m_footer;
        }

    }
}
