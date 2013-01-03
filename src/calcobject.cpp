#include "calcobject.h"

CalcObject::CalcObject()
{
}

bool CalcObject::isUnary() const
{
    return m_unary;
}

int CalcObject::priority() const
{
    return m_priority;
}

const QString &CalcObject::getOperator() const
{
    return m_op;
}
