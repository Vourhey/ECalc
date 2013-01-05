#include <QVBoxLayout>
#include <QAction>
#include "calculator.h"
#include "basickeyboard.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent)
{
    m_lineEdit = new LineEdit;
    m_basicKeyboard = new BasicKeyboard(m_lineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_lineEdit);
    mainLayout->addWidget(m_basicKeyboard);
    setLayout(mainLayout);
}

LineEdit *Calculator::lineEdit() const
{
    return m_lineEdit;
}

void Calculator::changeMode()
{
    QAction *act = qobject_cast<QAction*>(sender());
    int mode = act->data().toInt();

    switch(mode)
    {
    case 1: // Basic
        break;
    case 2: // Advance
        break;
    case 3: // Programming
        break;
    }
}
