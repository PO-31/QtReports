#ifndef CROSSTABGROUP_HPP
#define CROSSTABGROUP_HPP

#include "object.hpp"
#include "crosstabheader.hpp"

namespace qtreports
{
    namespace detail
    {
        class CrosstabGroup : public Object
        {
        public:

            enum GroupType {
                ROW = 0,
                COLUMN
            };

            explicit CrosstabGroup(GroupType groupType = qtreports::detail::CrosstabGroup::ROW);
            ~CrosstabGroup();

            void                        setType(GroupType groupType);
            GroupType                   getType();
            void                        setHeader(const CrosstabHeaderPtr &header);
            const CrosstabHeaderPtr     getHeader();
            void                        setWidth(int width);
            int                         getWidth();
            void                        setHeight(int height);
            int                         getHeight();

        protected:

            GroupType           m_type;

            //подтэги
            CrosstabHeaderPtr   m_header;

            //атрибуты
            int                 m_width;    // Используется типом ROW
            int                 m_height;   // Используется типом COLUMN

        };
        typedef QSharedPointer<CrosstabGroup> CrosstabGroupPtr;
        typedef qtreports::detail::CrosstabGroup::GroupType CrosstabGroupType;
    }
}

#endif // CROSSTABGROUP_HPP
