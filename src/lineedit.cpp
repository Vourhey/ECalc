#include <QPainter>
#include "lineedit.h"

// модифицированное поле ввода
LineEdit::LineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    m_waitOperand = false;

    setText(tr("0"));
    setAlignment(Qt::AlignRight);
    //setMaxLength(15);
    setReadOnly(true);

    QFont f = font();
    f.setPointSize(f.pointSize() + 8);
    setFont(f);

    setNumberMode();
}

void LineEdit::setOperator(const QString &op)
{
    m_operator = op;
    repaint();
}

void LineEdit::resetOperator()
{
    m_operator = "";
    repaint();
}

// все, что должно отображаться, должно выводиться через эти функции
void LineEdit::setNumber(Number n)
{
    setText(n.toString(m_numberMode).toUpper());
    displayed = n;
    emit numberChanged(n);
}

void LineEdit::setNumber(const QString &n, int m)
{
    if(m != 0)
        setNumberMode(m);
    displayed = Number::toNumber(n, m_numberMode);
    setText(n);
    emit numberChanged(displayed);
}

Number LineEdit::getNumber() const
{
    return displayed;
}

/*
 * нужно для programming mode
 * 10 - decimal
 * 8  - octal
 * 16 - hexadecimal
 *
 * // todo
 * 2 - bin
 */
void LineEdit::setNumberMode(int m)
{
    if(m == m_numberMode)
        return;

    if(m <= 0 || m > 16)
        return;

    m_numberMode = m;
    emit numberModeChanged(m);
    setNumber(displayed);
}

int LineEdit::numberMode() const
{
    return m_numberMode;
}

void LineEdit::setWait(bool b)
{
    m_waitOperand = b;
}

bool LineEdit::waitOperand() const
{
    return m_waitOperand;
}

void LineEdit::setPoint()
{
    if(!text().contains('.'))
        setText(text().append('.'));
}

void LineEdit::emitCalculateAll()
{
    emit calculateAll();
}

QByteArray LineEdit::saveState() const
{
    QByteArray ba;
    QDataStream stream (&ba, QIODevice::ReadWrite);

    stream << displayed;
    return ba;
}

void LineEdit::restoreState(const QByteArray &ba)
{
    Number num;
    QDataStream stream (ba);
    stream >> num;
    setNumber(num);
}

void LineEdit::paintEvent(QPaintEvent *e)
{
    QLineEdit::paintEvent(e);

    QPainter p(this);

    // координаты получены экспериментально

    // ### TODO ###
    if(!m_operator.isEmpty())
    {
        p.setFont(QFont("Arial", 12));
        p.drawRect(5, height()-15, 11, 11);
        p.drawText(5, height()-15, 12, 12, Qt::AlignCenter, m_operator);
    }
}
