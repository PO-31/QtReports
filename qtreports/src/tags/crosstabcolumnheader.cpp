#include "crosstabcolumnheader.hpp"

namespace qtreports
{
    namespace detail
    {
        CrosstabColumnHeader::CrosstabColumnHeader() {}
        CrosstabColumnHeader::~CrosstabColumnHeader() {}

        void CrosstabColumnHeader::setCellContents(const CellContentsPtr &cellContents)
        {
            m_cellContentsPtr = cellContents;
        }

        const CellContentsPtr CrosstabColumnHeader::getCellContents() const
        {
            return m_cellContentsPtr;
        }
    }
}
