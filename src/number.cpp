#include <QtCore/qmath.h>
#include "number.h"
#include <QDebug>

Number::Number()
{
    m_intNumber = 0;
    b_integer = true;
    precision = 6;
    m_format = 'g';
}

Number::Number(int n)
{
    m_intNumber = n;
    b_integer = true;
    precision = 6;
    m_format = 'g';
}

Number::Number(qreal n)
{
    if((qCeil(n) - qFloor(n)) == 0)
    {
        b_integer = true;
        m_intNumber = static_cast<quint64>(n);
    }
    else
    {
        b_integer = false;
        m_realNumber = n;
    }
    precision = 6;
    m_format = 'g';
}

Number::Number(quint64 n)
{
    m_intNumber = n;
    b_integer = true;
    precision = 6;
    m_format = 'g';
}

Number::Number(const QString &n)
{
    qreal t = n.toDouble();
    if((qCeil(t) - qFloor(t)) == 0)
    {
        b_integer = true;
        m_intNumber = n.toULongLong();
    }
    else
    {
        b_integer = false;
        m_realNumber = t;
    }
    precision = 6;
    m_format = 'g';
}

bool Number::isInteger() const
{
    return b_integer;
/*    if((qCeil(m_number) - qFloor(m_number)) == 0)
        return true;
    return false; */
}

/*
 * e - format as [-]9.9e[+|-]999
 * E - format as [-]9.9E[+|-]999
 * f - fixed (фиксированный, по умолчанию)
 * g - use e or f format, whichever is the most concise
 * G - use E or f format, whichever is the most concise
 */
void Number::setFormat(char f)
{
    if(f == 'e' || f == 'E' || f == 'f' || f == 'g' || f == 'G')
        m_format = f;
}

// если p < 0 ничего не произойдет
void Number::setPrecision(int p)
{
    if(p >= 0) precision = p;
}

int Number::getPrecision() const
{
    return precision;
}

QString Number::toString() const
{
    // ### TODO ###
    if(isInteger())
        return QString::number(toUInt64());
    return QString::number(m_realNumber, m_format, precision);
}

qreal Number::toDouble() const
{
    if(b_integer)
        return static_cast<qreal>(m_intNumber);
    return m_realNumber;
}

quint64 Number::toUInt64() const
{
    qDebug() << m_intNumber;
    if(b_integer)
        return m_intNumber;
    return static_cast<quint64>(qFloor(m_realNumber));
}

qreal Number::current()
{
    return b_integer ? static_cast<qreal>(m_intNumber) : m_realNumber;
}

bool Number::operator !=(Number n)
{
    if(b_integer && n.b_integer)
        return m_intNumber != n.m_intNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 != m2;
}

bool Number::operator ==(Number n)
{
    if(b_integer && n.b_integer)
        return m_intNumber == n.m_intNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 == m2;
}

bool Number::operator >=(Number n)
{
    if(b_integer && n.b_integer)
        return m_intNumber >= n.m_intNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 >= m2;
}

Number Number::operator +(Number n)
{
    if(b_integer && n.b_integer)
        return m_intNumber + n.m_intNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 + m2;
}

Number Number::operator -(Number n)
{
    if(b_integer && n.b_integer)
        return m_intNumber - n.m_intNumber;

    qreal m1 = current();
    qreal m2 = n.current();
    return m1 - m2;
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
    if(b_integer)
        return ~m_intNumber;
    return Number();
}

Number operator /(int i, Number n)
{
    qreal t;
    if(n.isInteger())
        t = i / n.m_intNumber;
    else
        t = i / n.m_realNumber;
    return Number(t);
}
