#include <QVBoxLayout>
#include <QAction>
#include "calculator.h"
#include "basickeyboard.h"
#include "numbersystemswitcher.h"
#include "programmingkeyboard.h"
#include "bineditor.h"
#include "advancekeyboard.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent), m_mode(1)
{
    m_lineEdit = new LineEdit;
    m_basicKeyboard = new BasicKeyboard(m_lineEdit);

    m_numberSystemSwitcher = 0;
    m_programmingKeyboard  = 0;
    m_advanceKeyboard      = 0;
    m_binEditor            = 0;

    mainLayout = new QVBoxLayout;
    horizontalLayout = new QHBoxLayout;

    mainLayout->addWidget(m_lineEdit);
    horizontalLayout->addWidget(m_basicKeyboard);
    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);

    changeMode(1);
}

LineEdit *Calculator::lineEdit() const
{
    return m_lineEdit;
}

// если m == -1, то вызвано из меню
void Calculator::changeMode(int m)
{
    if(m == -1)
    {
        QAction *act = qobject_cast<QAction*>(sender());
        m = act->data().toInt();
    }

    if(m_mode == m)
        return;

    m_mode = m;

    // возвращаем к Basic
    if(m_numberSystemSwitcher)
    {
        mainLayout->removeWidget(m_numberSystemSwitcher);
        m_numberSystemSwitcher->hide();
    }
    if(m_binEditor)
    {
        mainLayout->removeWidget(m_binEditor);
        m_binEditor->hide();
    }
    if(m_programmingKeyboard)
    {
        horizontalLayout->removeWidget(m_programmingKeyboard);
        m_programmingKeyboard->hide();
    }
    if(m_advanceKeyboard)
    {
        horizontalLayout->removeWidget(m_advanceKeyboard);
        m_advanceKeyboard->hide();
    }

    switch(m_mode)
    {
    case 1: // Basic
        break;
    case 2: // Advance
        // ### TODO ###
        break;
    case 3: // Programming
        if(!m_numberSystemSwitcher)
            m_numberSystemSwitcher = new NumberSystemSwitcher(m_lineEdit);
        if(!m_binEditor)
            m_binEditor = new BinEditor(m_lineEdit);
        if(!m_programmingKeyboard)
            m_programmingKeyboard = new ProgrammingKeyboard(m_lineEdit);

        mainLayout->insertWidget(1, m_numberSystemSwitcher);
        mainLayout->insertWidget(2, m_binEditor);
        horizontalLayout->insertWidget(1, m_programmingKeyboard);

        m_numberSystemSwitcher->show();
        m_binEditor->show();
        m_programmingKeyboard->show();
        break;
    }
}
