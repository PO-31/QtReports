#pragma once
#ifndef MEASURE_HPP
#define MEASURE_HPP

#include <QString>
#include <QSharedPointer>

#include "textwidget.hpp"

namespace qtreports
{
    namespace detail
    {
        class Measure : public TextWidget {
        public:
            Measure();
            ~Measure();

            void setClassName(const QString & name);
            void setCalculation(const QString & calculation);
            const QString getClassName() const;
            const QString getCalculation() const;
        private:
            QString m_className;
            QString m_calculation;
        };
        typedef QSharedPointer<Measure> MeasurePtr;
    }
}

#endif // MEASURE_HPP
