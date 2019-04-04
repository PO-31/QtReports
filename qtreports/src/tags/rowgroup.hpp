#pragma once
#ifndef ROWGROUP_HPP
#define ROWGROUP_HPP

#include <QString>
#include <QSharedDataPointer>

#include "crosstabrowheader.hpp"
#include "section.hpp"

namespace qtreports
{
    namespace detail
    {
        class RowGroup : public Section {
        public:
            RowGroup();
            ~RowGroup();

            void setCrosstabRowHeader(const CrosstabRowHeaderPtr & crosstabRowHeader);
            const CrosstabRowHeaderPtr getCrosstabRowHeader() const;
        private:
            CrosstabRowHeaderPtr m_crosstabRowHeaderPtr;
        };
        typedef QSharedPointer<RowGroup> RowGroupPtr;
    }
}

#endif // ROWGROUP_HPP
