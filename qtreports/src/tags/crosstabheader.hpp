#ifndef CROSSTABHEADER_HPP
#define CROSSTABHEADER_HPP

#include "object.hpp"
#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        class CrosstabHeader : public Object
        {
        public:

            CrosstabHeader();
            ~CrosstabHeader();

            void                    setCellContents(const CellContentsPtr &cellContents);
            const CellContentsPtr   getCellContents();

        private:
            CellContentsPtr     m_cellContents;

        };
        typedef QSharedPointer<CrosstabHeader> CrosstabHeaderPtr;
    }
}

#endif // CROSSTABHEADER_HPP
