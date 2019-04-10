#include "crosstabheader.hpp"

namespace qtreports {
    namespace detail {

        CrosstabHeader::CrosstabHeader() {}

        CrosstabHeader::~CrosstabHeader() {}

        void CrosstabHeader::setCellContents(const CellContentsPtr &cellContents)
        {
            m_cellContents = cellContents;
        }

        const CellContentsPtr CrosstabHeader::getCellContents()
        {
            return m_cellContents;
        }
    }
}
