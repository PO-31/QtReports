#include "measure.hpp"

namespace qtreports
{
    namespace detail
    {
        Measure::Measure() {}
        Measure::~Measure() {}

        void Measure::setClassName(const QString &name)
        {
            m_className = name;
        }

        void Measure::setCalculation(const QString &calculation)
        {
            m_calculation = calculation;
        }

        const QString Measure::getClassName() const
        {
            return m_className;
        }

        const QString Measure::getCalculation() const
        {
            return m_calculation;
        }
    }
}
