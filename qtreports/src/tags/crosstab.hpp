#pragma once
#ifndef CROSSTAB_HPP
#define CROSSTAB_HPP

#include "widget.hpp"
#include "crosstabgroup.hpp"
#include "crosstabsection.h"

namespace qtreports
{
    namespace detail
    {
        class Crosstab : public Widget
        {
        public:
            Crosstab();
            ~Crosstab();

            void                            setRowGroup(const CrosstabGroupPtr &rowGroup);
            const CrosstabGroupPtr          getRowGroup();
            void                            setColumnGroup(const CrosstabGroupPtr &columnGroup);
            const CrosstabGroupPtr          getColumnGroup();
            void                            setCrosstabCell(const CrosstabSectionPtr &crosstabCell);
            const CrosstabSectionPtr        getCrosstabCell();

        protected:
            CrosstabGroupPtr    m_rowGroup;
            CrosstabGroupPtr    m_columnGroup;
            CrosstabSectionPtr  m_crosstabCell;
        };
        typedef QSharedPointer<Crosstab> CrosstabPtr;
    }
}

#endif // CROSSTAB_HPP
