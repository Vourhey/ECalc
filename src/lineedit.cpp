#include <QPainter>
#include "lineedit.h"

// модифицированное поле ввода
LineEdit::LineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    memory = false;
    m_waitOperand = false;

    setText(tr("0"));
    setAlignment(Qt::AlignRight);
    //setMaxLength(15);
    setReadOnly(true);

    QFont f = font();
    f.setPointSize(f.pointSize() + 8);
    setFont(f);
}

void LineEdit::setMemory(bool b)
{
    memory = b;
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
    setText(n.toString());
    displayed = n;
    emit numberChanged(n);
}

void LineEdit::setNumber(const QString &n)
{
    setText(n);
    displayed = n;
    emit numberChanged(n);
}

Number LineEdit::getNumber() const
{
    return displayed;
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

void LineEdit::paintEvent(QPaintEvent *e)
{
    QLineEdit::paintEvent(e);

    QPainter p(this);

    // координаты получены экспериментально

    if(memory)  // в углу рисуем букву М, если память не пуста
    {
        p.setFont(QFont("Arial", 8));
        p.drawText(5, 5, 15, 15, Qt::AlignCenter, tr("M"));
    }

    if(!m_operator.isEmpty())
    {
        p.setFont(QFont("Arial", 12));
        p.drawRect(5, height()-15, 11, 11);
        p.drawText(5, height()-15, 12, 12, Qt::AlignCenter, m_operator);
    }
}
