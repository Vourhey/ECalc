#ifndef NUMBER_H
#define NUMBER_H

#include <QtGlobal>
#include <QString>

// Представляет число
// упрощает работу с целыми и дробными числами в разных системах счисления
class Number
{
public:
    Number();
    Number(qreal n);
    Number(int n);
    Number(qint64 n);
    Number(quint64 n);
    Number(const QString &n);

    bool isInteger() const; // целое ли число
    bool isUInteger() const;
    bool isDouble() const;  // true если вещественное

    QString toString(int base = 10, char format = 'f', int prec = 6) const;
    qreal toDouble() const;
    qint64 toInt64() const;
    quint64 toUInt64() const;

    Number integer() const;
    Number fraction() const;

    bool operator == (Number);
    bool operator >= (Number);
    bool operator <= (Number);
    bool operator != (Number);
    bool operator < (Number);
    bool operator > (Number);
    Number operator + (Number);
    Number operator - (Number);
    Number operator - ();
    Number operator * (Number);
    Number operator / (Number);
    Number operator /= (Number);
    Number operator ~();
    Number operator &(Number);
    Number operator |(Number);
    Number operator ^(Number);
    Number operator %(Number);
    Number operator << (Number);
    Number operator >> (Number);

    static Number toNumber(const QString &, int = 10);

private:
    void setCurrent(qreal n);
    qreal current() const;
    union
    {
        qreal m_realNumber;     // вещественное число
        qint64 m_intNumber;     // целое со знаком
        quint64 m_uintNumber;   // целое без знака
    };
    /*
     * i - integer
     * u - unsigned int
     * d - double
     */
    char m_mode; // флаг, указывающий на целое число
};

#endif // NUMBER_H
