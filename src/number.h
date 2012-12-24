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
    Number(quint64 n);

    bool isInteger() const; // целое ли число

    QString toString() const;
    qreal toDouble() const;
    quint64 toUInt64() const;

    void setFormat(char f);

    void setPrecision(int p);
    int getPrecision() const;

    bool operator == (Number);
    bool operator >= (Number);
    bool operator != (Number);
    Number operator + (Number);
    Number operator - (Number);
    Number operator * (Number);
    Number operator / (Number);
    Number operator /= (Number);
    Number operator ~();

    friend Number operator / (int, Number);

private:
    int precision;  // округление
    qreal m_number; // собственно число
//    bool b_integer; // флаг, указывающий на целое число
    char m_format;  // формат представления числа
};

#endif // NUMBER_H
