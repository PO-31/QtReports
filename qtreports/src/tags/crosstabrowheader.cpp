#include "crosstabrowheader.hpp"

namespace qtreports
{
    namespace detail
    {
        CrosstabRowHeader::CrosstabRowHeader() {}
        CrosstabRowHeader::~CrosstabRowHeader() {}

        void CrosstabRowHeader::setCellContents(const CellContentsPtr &cellContents)
        {
            m_cellContentsPtr = cellContents;
        }

        const CellContentsPtr CrosstabRowHeader::getCellContents() const
        {
            return m_cellContentsPtr;
        }
    }
}
