#ifndef CROSSTAB_H
#define CROSSTAB_H
//убрать позже
#include "widget.hpp"

namespace qtreports
{
    namespace detail
    {
    /*! @~russian
    @brief Класс, реализующий тэг <crosstab>

    Класс, реализующий тэг <crosstab>. В данный момент находится в разработке.
    */
        class Crosstab : public Widget
        {
        public:
            Crosstab();
            ~Crosstab();

        };
        typedef QSharedPointer< Crosstab > CrosstabPtr;
    }
}
#endif // CROSSTAB_H
