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
    Number(const QString &n);

    bool isInteger() const; // целое ли число
    bool isUInteger() const;
    bool isDouble() const;  // true если вещественное

    QString toString(int base = 10, char format = 'g', int prec = 9) const;
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
};

#endif // NUMBER_H
