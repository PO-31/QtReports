#pragma once
#ifndef VARIABLE_H
#define VARIABLE_H

#include "object.hpp"

namespace qtreports
{

namespace detail {

enum class VariableResetType : unsigned char
{
    None = 0,
    Report,
    Page,
    Column,
    Group
};

enum class VariableIncrementType : unsigned char
{
    None = 0,
    Report,
    Page,
    Column,
    Group
};

enum class VariableCalculation : unsigned char
{
    Count = 0,
    Sum,
    Average,
    Lowest,
    Highest
};

class Variable : public Object
{
public:
    Variable();

    const QVariant& getValue() const;

    const QString &getExpression() const;

    const QString& getClassName() const;

    const QString& getResetGroup() const;

    const QString& getIncrementGroup() const;

    VariableResetType getResetType() const;

    VariableIncrementType getIncrementType() const;

    VariableCalculation getCalculation() const;

    void setValue(const QVariant& value);

    void setExpression(const QString& expression);

    void setClassName(const QString& className);

    void setResetGroup(const QString& resetGroup);

    void setIncrementGroup(const QString& incrementGroup);

    void setResetType(VariableResetType resetType);

    void setIncrementType(VariableIncrementType incrementType);

    void setCalculation(VariableCalculation calculation);

private:
    QVariant                m_value;
    QString                 m_expression;
    QString                 m_className;
    QString                 m_resetGroup;
    QString                 m_incrementGroup;
    VariableResetType       m_resetType;
    VariableIncrementType   m_incrementType;
    VariableCalculation     m_calculation;
};

typedef QSharedPointer< Variable > VariablePtr;

}

}

#endif // VARIABLE_H
