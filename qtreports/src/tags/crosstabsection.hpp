#ifndef CROSSTABSECTION_H
#define CROSSTABSECTION_H

#include "object.hpp"
#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        class CrosstabSection : public Object
        {
        public:
            CrosstabSection();
            ~CrosstabSection();

            void                    setCellContents(const CellContentsPtr &cellContents);
            const CellContentsPtr   getCellContents();

        protected:
            CellContentsPtr m_cellContents;
        };
        typedef QSharedPointer<CrosstabSection> CrosstabSectionPtr;
    }
}
#endif // CROSSTABSECTION_H
