#pragma once
#ifndef CROSSTABCOLUMNHEADER_HPP
#define CROSSTABCOLUMNHEADER_HPP

#include <QString>
#include <QSharedPointer>

#include "object.hpp"
#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        class CrosstabColumnHeader : public Object {
        public:
            CrosstabColumnHeader();
            ~CrosstabColumnHeader();

            void setCellContents(const CellContentsPtr & cellContents);
            const CellContentsPtr getCellContents() const;
        private:
            CellContentsPtr m_cellContentsPtr;
        };
        typedef QSharedPointer<CrosstabColumnHeader> CrosstabColumnHeaderPtr;
    }
}

#endif // CROSSTABCOLUMNHEADER_HPP
