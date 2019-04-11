#include "variable.hpp"
using namespace qtreports;
using namespace detail;

Variable::Variable() :
    m_className("QString"),
    m_resetType(VariableResetType::Report),
    m_incrementType(VariableIncrementType::None),
    m_calculation(VariableCalculation::Count)
{

}

const QVariant& Variable::getValue() const
{
    return m_value;
}

const QString& Variable::getExpression() const
{
    return m_expression;
}

const QString& Variable::getClassName() const
{
    return m_className;
}

const QString& Variable::getResetGroup() const
{
    return m_resetGroup;
}

const QString& Variable::getIncrementGroup() const
{
    return m_incrementGroup;
}

VariableResetType Variable::getResetType() const
{
    return m_resetType;
}

VariableIncrementType Variable::getIncrementType() const
{
    return m_incrementType;
}

VariableCalculation Variable::getCalculation() const
{
    return m_calculation;
}

void Variable::setValue(const QVariant& value)
{
    m_value = value;
}

void Variable::setExpression(const QString& expression)
{
    m_expression = expression;
}

void Variable::setClassName(const QString& className)
{
    m_className = className;
}

void Variable::setResetGroup(const QString& resetGroup)
{
    m_resetGroup = resetGroup;
}

void Variable::setIncrementGroup(const QString& incrementGroup)
{
    m_incrementGroup = incrementGroup;
}

void Variable::setResetType(VariableResetType resetType)
{
    m_resetType = resetType;
}

void Variable::setIncrementType(VariableIncrementType incrementType)
{
    m_incrementType = incrementType;
}

void Variable::setCalculation(VariableCalculation calculation)
{
    m_calculation = calculation;
}
