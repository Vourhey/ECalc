#ifndef CALCOBJECT_H
#define CALCOBJECT_H

#include "number.h"
#include <QString>

// представляет оператор
// Базовый для всех операций
class CalcObject
{
public:
    CalcObject();
    bool isUnary() const;
    int priority() const; // приоритет операции
    const QString &getOperator() const;
    virtual Number calc(Number n1, Number n2 = Number()) = 0;

protected:
    bool m_unary;
    QString m_op;
    int m_priority;
};

#endif // CALCOBJECT_H
