#pragma once
#ifndef CROSSTAB_HPP
#define CROSSTAB_HPP

#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {
        class Crosstab : public Widget
        {
        public:
            Crosstab();
            ~Crosstab();
        };
        typedef QSharedPointer<Crosstab> CrosstabPtr;
    }
}

#endif // CROSSTAB_HPP
