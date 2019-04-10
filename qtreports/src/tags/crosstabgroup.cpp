#include "crosstabgroup.hpp"

namespace qtreports
{
    namespace detail
    {
        CrosstabGroup::CrosstabGroup(GroupType groupType)
        {
            m_type = groupType;
            m_width = 0;
            m_height = 0;
        }

        CrosstabGroup::~CrosstabGroup()
        {

        }

        void CrosstabGroup::setType(GroupType groupType)
        {
            m_type = groupType;
        }

        CrosstabGroupType qtreports::detail::CrosstabGroup::getType()
        {
            return m_type;
        }

        void CrosstabGroup::setHeader(const CrosstabHeaderPtr &header)
        {
            m_header = header;
        }

        const CrosstabHeaderPtr qtreports::detail::CrosstabGroup::getHeader()
        {
            return m_header;
        }

        void CrosstabGroup::setWidth(int width)
        {
            m_width = width;
        }

        int CrosstabGroup::getWidth()
        {
            return m_width;
        }

        void CrosstabGroup::setHeight(int height)
        {
            m_height = height;
        }

        int CrosstabGroup::getHeight()
        {
            return m_height;
        }
    }
}
