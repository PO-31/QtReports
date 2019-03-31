#pragma once
#ifndef SUMMARY_HPP
#define SUMMARY_HPP
#include <QSharedPointer>

#include "section.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <summary>

        Класс, реализующий тэг <summary>
        */
        class Summary : public Section {

        public:
            Summary();
            ~Summary();

        private:

        };
        typedef QSharedPointer<Summary> SummaryPtr;

    }
}

#endif // SUMMARY_HPP
