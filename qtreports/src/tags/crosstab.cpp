#include "crosstab.hpp"
namespace qtreports
{
    namespace detail
    {
        Crosstab::Crosstab() {}
        Crosstab::~Crosstab() {}

        void Crosstab::setRowGroup(const CrosstabGroupPtr &rowGroup)
        {
            m_rowGroup = rowGroup;
        }

        const CrosstabGroupPtr Crosstab::getRowGroup()
        {
            return m_rowGroup;
        }

        void Crosstab::setColumnGroup(const CrosstabGroupPtr &columnGroup)
        {
            m_columnGroup = columnGroup;
        }

        const CrosstabGroupPtr Crosstab::getColumnGroup()
        {
            return m_columnGroup;
        }

        void Crosstab::setCrosstabCell(const CrosstabCellPtr &crosstabCell)
        {
            m_crosstabCell = crosstabCell;
        }

        const CrosstabCellPtr Crosstab::getCrosstabCell()
        {
            return m_crosstabCell;
        }
    }
}
