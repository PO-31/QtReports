#pragma once
#ifndef CROSSTABROWHEADER_HPP
#define CROSSTABROWHEADER_HPP

#include <QString>
#include <QSharedPointer>

#include "object.hpp"
#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        class CrosstabRowHeader: public Object {
        public:
            CrosstabRowHeader();
            ~CrosstabRowHeader();

            void setCellContents(const CellContentsPtr & cellContents);
            const CellContentsPtr getCellContents() const;

        private:
            CellContentsPtr m_cellContentsPtr;
        };
        typedef QSharedPointer<CrosstabRowHeader> CrosstabRowHeaderPtr;
    }
}

#endif // CROSSTABROWHEADER_HPP
