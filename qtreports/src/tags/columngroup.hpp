#pragma once
#ifndef COLUMNGROUP_HPP
#define COLUMNGROUP_HPP

#include <QString>
#include <QSharedPointer>

#include "section.hpp"
#include "crosstabcolumnheader.hpp"

namespace qtreports
{
    namespace detail
    {
        class ColumnGroup : public Section {

        public:
            ColumnGroup();
            ~ColumnGroup();

            void setCrosstabColumnHeader(const CrosstabColumnHeaderPtr & crosstabColumnHeader);
            const CrosstabColumnHeaderPtr getCrosstabColumnHeader() const;
        private:
            CrosstabColumnHeaderPtr m_crosstabColumnHeaderPtr;
        };
        typedef QSharedPointer<ColumnGroup> ColumnGroupPtr;
    }
}

#endif // COLUMNGROUP_HPP
