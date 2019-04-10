#pragma once
#ifndef CROSSTAB_HPP
#define CROSSTAB_HPP

#include "widget.hpp"
#include "crosstabgroup.hpp"
#include "crosstabcell.hpp"

namespace qtreports
{
    namespace detail
    {
        class Crosstab : public Widget
        {
        public:
            Crosstab();
            ~Crosstab();

            void                    setRowGroup(const CrosstabGroupPtr &rowGroup);
            const CrosstabGroupPtr  getRowGroup();
            void                    setColumnGroup(const CrosstabGroupPtr &columnGroup);
            const CrosstabGroupPtr  getColumnGroup();
            void                    setCrosstabCell(const CrosstabCellPtr &crosstabCell);
            const CrosstabCellPtr   getCrosstabCell();

        private:

            // подтэги
            CrosstabGroupPtr    m_rowGroup;
            CrosstabGroupPtr    m_columnGroup;
            CrosstabCellPtr     m_crosstabCell;
        };
        typedef QSharedPointer<Crosstab> CrosstabPtr;
    }
}

#endif // CROSSTAB_HPP
