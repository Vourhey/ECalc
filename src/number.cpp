#include <QtCore/qmath.h>
#include "number.h"
#include <QDebug>

Number::Number()
{
    m_intNumber = 0;
    m_mode = 'i';
}

Number::Number(int n)
{
    if(n >= 0)
    {
        m_uintNumber = static_cast<quint64>(n);
        m_mode = 'u';
    }
    else
    {
        m_intNumber = n;
        m_mode = 'i';
    }
}

Number::Number(qreal n)
{
    setCurrent(n);
}

Number::Number(qint64 n)
{
    if(n >= 0)
    {
        m_uintNumber = static_cast<quint64>(n);
        m_mode = 'u';
    }
    else
    {
        m_intNumber = n;
        m_mode = 'i';
    }
}

Number::Number(quint64 n)
{
    m_uintNumber = n;
    m_mode = 'u';
}

Number::Number(const QString &n)
{
    setCurrent(n.toDouble());
}

// целое ли число
bool Number::isInteger() const
{
    return m_mode == 'i';
}

bool Number::isUInteger() const
{
    return m_mode == 'u';
}

bool Number::isDouble() const
{
    return m_mode == 'd';
}

// format и prec указываются только для double числа
// ### TODO
// а как внешние модули будут знать, что именно сейчас double???
// решить эту проблему
// ### TODO
// перевод дробных чисел в системы счисления, отличные от 10
QString Number::toString(int base, char format, int prec) const
{
    if(isDouble())
        return QString::number(m_realNumber, format, prec);
    if(isInteger())
        return QString::number(m_intNumber, base);
    // иначе
    return QString::number(m_uintNumber, base);
}

qreal Number::toDouble() const
{
    if(isDouble())
        return m_realNumber;
    if(isInteger())
        return static_cast<qreal>(m_intNumber);
    // иначе
    return static_cast<qreal>(m_uintNumber);
}

qint64 Number::toInt64() const
{
    if(isInteger())
        return m_intNumber;
    if(isUInteger())
        return static_cast<qint64>(m_uintNumber);
    return static_cast<qint64>(qFloor(m_realNumber));
}

quint64 Number::toUInt64() const
{
    if(isInteger())
        return static_cast<quint64>(m_intNumber);
    if(isUInteger())
        return m_uintNumber;
    return static_cast<quint64>(qFloor(m_realNumber));
}

Number Number::toNumber(const QString &s, int b)
{
    bool ok;
    QVariant v(s);
    if(v.canConvert(QVariant::ULongLong))
        return s.toULongLong(&ok, b);
    else if(v.canConvert(QVariant::Int))
        return s.toInt(&ok, b);
    return s.toDouble();    // возможны ошибки во всей функции
}

// Возвращает целую часть
Number Number::integer() const
{
    if(!isDouble())
        return *this;

    return static_cast<qint64>(m_realNumber);
}

// Возвращает дробную часть
Number Number::fraction() const
{
    Number b = *this;
    return b - integer();
}

void Number::setCurrent(qreal n)
{
    if((qCeil(n) - qFloor(n)) == 0)
    {
        if(n < 0)
        {
            m_intNumber = static_cast<qint64>(n);
            m_mode = 'i';
        }
        else    // unsigned
        {
            m_uintNumber = static_cast<quint64>(n);
            m_mode = 'u';
        }
    }
    else
    {
        m_mode = 'd';
        m_realNumber = n;
    }
}

qreal Number::current() const
{
    if(isDouble())
        return m_realNumber;
    if(isInteger())
        return static_cast<qreal>(m_intNumber);
    return static_cast<qreal>(m_uintNumber);
}

bool Number::operator !=(Number n)
{
    if(isUInteger() && n.isUInteger())
        return m_uintNumber != n.m_uintNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 != m2;
}

bool Number::operator ==(Number n)
{
    if(isUInteger() && n.isUInteger())
        return m_uintNumber == n.m_uintNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 == m2;
}

bool Number::operator < (Number n)
{
    if(isUInteger() && n.isUInteger())
        return m_uintNumber < n.m_uintNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 < m2;
}

bool Number::operator > (Number n)
{
    if(isUInteger() && n.isUInteger())
        return m_uintNumber > n.m_uintNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 > m2;
}

bool Number::operator >=(Number n)
{
    return ! operator < (n);
}

bool Number::operator <= (Number n)
{
    return ! operator > (n);
}

Number Number::operator +(Number n)
{
    if(isUInteger() && n.isUInteger())
        return m_uintNumber + n.m_uintNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 + m2;
}

Number Number::operator -(Number n)
{
    qreal m1 = current();
    qreal m2 = n.current();
    return m1 - m2;
}

Number Number::operator -()
{
    if(isDouble())
        return -m_realNumber;
    if(isInteger())
        return -m_intNumber;

    return static_cast<qint64>(-m_uintNumber);
}

Number Number::operator *(Number n)
{
    qreal m1, m2;
    m1 = current();
    m2 = n.current();
    return m1 * m2;
}

Number Number::operator /(Number n)
{
    qreal m1, m2;
    m1 = current();
    m2 = n.current();
    return m1 / m2;
}

Number Number::operator /=(Number n)
{
    *this = *this / n;
    return *this;
}

Number Number::operator ~()
{
    if(isUInteger())
        return ~m_uintNumber;
    return Number();
}

// TODO
/*
Number operator /(int i, Number n)
{
    qreal t = n.current();
    if(n.isInteger())
        t = i / n.m_intNumber;
    else
        t = i / n.m_realNumber;
    return Number(t);
}*/
