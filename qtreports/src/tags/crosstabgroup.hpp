#ifndef CROSSTABGROUP_HPP
#define CROSSTABGROUP_HPP

#include "object.hpp"
#include "crosstabsection.h"

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

            CrosstabGroup(const GroupType &groupType = qtreports::detail::CrosstabGroup::ROW);
            ~CrosstabGroup();

            void                                            setGroupType(const qtreports::detail::CrosstabGroup::GroupType &groupType);
            qtreports::detail::CrosstabGroup::GroupType     getGroupType();
            void                                            setHeader(const CrosstabSectionPtr &header);
            const CrosstabSectionPtr                        getHeader();

        protected:

            GroupType m_groupType;
            CrosstabSectionPtr m_header;

        };
        typedef QSharedPointer<CrosstabGroup> CrosstabGroupPtr;
    }
}

#endif // CROSSTABGROUP_HPP
