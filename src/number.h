#ifndef NUMBER_H
#define NUMBER_H

#include <QtGlobal>
#include <QString>
#include <QIODevice>

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

    bool isInteger() const; // целое ли число
    bool isUInteger() const;
    bool isDouble() const;  // true если вещественное

    QString toString() const;
    static void setBase(int base);
    static void setFormat(char format);
    static void setPrecision(int prec);

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

    static Number toNumber(const QString &);

    friend QDataStream &operator<<(QDataStream &to, const Number &num);
    friend QDataStream &operator>>(QDataStream &from, Number &num);

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
    qint8 m_mode;

    static int m_base;
    static char m_format;
    static int m_precision;
};

#endif // NUMBER_H
