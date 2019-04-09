#include "crosstabsection.hpp"


qtreports::detail::CrosstabSection::CrosstabSection()
{

}

qtreports::detail::CrosstabSection::~CrosstabSection()
{

}

void qtreports::detail::CrosstabSection::setCellContents(const qtreports::detail::CellContentsPtr &cellContents)
{
    m_cellContents = cellContents;
}

const qtreports::detail::CellContentsPtr qtreports::detail::CrosstabSection::getCellContents()
{
    return m_cellContents;
}
