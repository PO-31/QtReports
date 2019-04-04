#include "rowgroup.hpp"

namespace qtreports
{
    namespace detail
    {
        RowGroup::RowGroup() {}
        RowGroup::~RowGroup() {}

        void RowGroup::setCrosstabRowHeader(const CrosstabRowHeaderPtr &crosstabRowHeader)
        {
            m_crosstabRowHeaderPtr = crosstabRowHeader;
        }

        const CrosstabRowHeaderPtr RowGroup::getCrosstabRowHeader() const
        {
            return m_crosstabRowHeaderPtr;
        }
    }
}

