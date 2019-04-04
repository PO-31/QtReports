#include "columngroup.hpp"

namespace qtreports
{
    namespace detail
    {
        ColumnGroup::ColumnGroup() {}
        ColumnGroup::~ColumnGroup() {}

        void ColumnGroup::setCrosstabColumnHeader(const CrosstabColumnHeaderPtr &crosstabColumnHeader)
        {
            m_crosstabColumnHeaderPtr = crosstabColumnHeader;
        }

        const CrosstabColumnHeaderPtr ColumnGroup::getCrosstabColumnHeader() const
        {
            return m_crosstabColumnHeaderPtr;
        }
    }
}
