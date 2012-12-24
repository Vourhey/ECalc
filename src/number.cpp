#include <QtCore/qmath.h>
#include "number.h"

Number::Number()
{
    m_number = 0;
    precision = 6;
    m_format = 'f';
}

Number::Number(int n)
{
    m_number = n;
    precision = 6;
    m_format = 'f';
}

Number::Number(qreal n)
{
    m_number = n;
    precision = 6;
    m_format = 'f';
}

Number::Number(quint64 n)
{
    m_number = static_cast<qreal>(n);
    precision = 6;
    m_format = 'f';
}

bool Number::isInteger() const
{
    quint64 tmp = static_cast<quint64>(m_number);
    quint64 zero = quint64((m_number - tmp) * qPow(10, precision));

    if(zero == 0)
        return true;

    return false;
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
        return QString::number(m_number, 'f', 0);
    return QString::number(m_number, m_format, precision);
}

qreal Number::toDouble() const
{
    return m_number;
}

quint64 Number::toUInt64() const
{
    return static_cast<quint64>(m_number);
}

// ### TODO ###

bool Number::operator !=(Number n)
{
    Q_UNUSED(n)
    return true;
}

bool Number::operator ==(Number n)
{
    Q_UNUSED(n)
    return true;
}

bool Number::operator >=(Number n)
{
    Q_UNUSED(n)
    return true;
}

Number Number::operator +(Number n)
{
    Q_UNUSED(n)
    return Number();
}

Number Number::operator -(Number n)
{
    Q_UNUSED(n)
    return Number();
}

Number Number::operator *(Number n)
{
    Q_UNUSED(n)
    return Number();
}

Number Number::operator /(Number n)
{
    Q_UNUSED(n)
    return Number();
}

Number Number::operator /=(Number n)
{
    Q_UNUSED(n)
    return Number();
}

Number Number::operator ~()
{
    return Number();
}

Number operator /(int i, Number n)
{
    Q_UNUSED(n)
    Q_UNUSED(i)
    return Number();
}
