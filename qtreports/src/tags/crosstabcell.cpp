#include "crosstabcell.hpp"

namespace qtreports
{
    namespace detail
    {
        CrosstabCell::CrosstabCell() {}

        CrosstabCell::~CrosstabCell() {}

        void CrosstabCell::setCellContents(const CellContentsPtr &cellContents)
        {
            m_cellContents = cellContents;
        }

        const CellContentsPtr CrosstabCell::getCellContents()
        {
            return m_cellContents;
        }

        void CrosstabCell::setWidth(int width)
        {
            m_width = width;
        }

        int CrosstabCell::getWidth()
        {
            return m_width;
        }

        void CrosstabCell::setHeight(int height)
        {
            m_height = height;
        }

        int CrosstabCell::getHeight()
        {
            return m_height;
        }
    }
}
