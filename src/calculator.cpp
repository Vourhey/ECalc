#include <QVBoxLayout>
#include "calculator.h"
#include "lineedit.h"
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

void Calculator::changeMode(int mode)
{
    Q_UNUSED(mode)
}
