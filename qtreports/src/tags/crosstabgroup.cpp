#include "crosstabgroup.hpp"

qtreports::detail::CrosstabGroup::CrosstabGroup(const GroupType &groupType)
{
    m_groupType = groupType;
}

qtreports::detail::CrosstabGroup::~CrosstabGroup()
{

}

void qtreports::detail::CrosstabGroup::setGroupType(const qtreports::detail::CrosstabGroup::GroupType &groupType)
{
    m_groupType = groupType;
}

qtreports::detail::CrosstabGroup::GroupType qtreports::detail::CrosstabGroup::getGroupType()
{
    return m_groupType;
}

void qtreports::detail::CrosstabGroup::setHeader(const qtreports::detail::CrosstabSectionPtr &header)
{
    m_header = header;
}

const qtreports::detail::CrosstabSectionPtr qtreports::detail::CrosstabGroup::getHeader()
{
    return m_header;
}
