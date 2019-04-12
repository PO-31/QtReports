#include "crosstab.hpp"
namespace qtreports
{
    namespace detail
    {
        Crosstab::Crosstab()
        {
            isRepeatColumnHeaders = true;
            isRepeatRowHeaders = true;
            columnBreakOffset = 10;
            runDirectionLeftToRight = true;
            ignoreWidth = false;
        }
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

        void Crosstab::setColumnHeadersRepeating(bool value)
        {
            isRepeatColumnHeaders = value;
        }

        void Crosstab::setRowHeadersRepeating(bool value)
        {
            isRepeatRowHeaders = value;
        }

        void Crosstab::setWidthIgnoring(bool value)
        {
            ignoreWidth = value;
        }

        void Crosstab::setRunDirectionLeftToRight(bool value)
        {
            runDirectionLeftToRight = value;
        }

        void Crosstab::setColumnBreakOffset(int value)
        {
                columnBreakOffset = value;
        }

        bool Crosstab::getColumnHeadersRepeating()
        {
            return isRepeatColumnHeaders;
        }

        bool Crosstab::getRowHeadersRepeating()
        {
            return isRepeatRowHeaders;
        }

        bool Crosstab::getWidthIgnoring()
        {
            return ignoreWidth;
        }

        bool Crosstab::getRunDirectionLeftToRight()
        {
            return runDirectionLeftToRight;
        }

        int Crosstab::getColumnBreakOffset()
        {
            return columnBreakOffset;
        }
    }
}
