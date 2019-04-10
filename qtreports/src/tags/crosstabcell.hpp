#ifndef CROSSTABSECTION_H
#define CROSSTABSECTION_H

#include "object.hpp"
#include "cellcontents.hpp"

namespace qtreports
{
    namespace detail
    {
        class CrosstabCell : public Object
        {
        public:

            CrosstabCell();
            ~CrosstabCell();

            void                    setCellContents(const CellContentsPtr &cellContents);
            const CellContentsPtr   getCellContents();
            void                    setWidth(int width);
            int                     getWidth();
            void                    setHeight(int height);
            int                     getHeight();
        private:

            // подтэги
            CellContentsPtr     m_cellContents;

            //атрибуты
            int                 m_width;
            int                 m_height;
        };
        typedef QSharedPointer<CrosstabCell> CrosstabCellPtr;
    }
}
#endif // CROSSTABSECTION_H
