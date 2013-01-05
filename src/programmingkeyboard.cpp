#include <QGridLayout>
#include <QtCore/qmath.h>
#include <QPushButton>
#include "programmingkeyboard.h"
#include "button.h"
#include "lineedit.h"
#include "calcobject.h"

InsertCharDialog::InsertCharDialog(QWidget *parent)
    : QDialog (parent)
{
    le =  new QLineEdit;
    le->setMaxLength(1);    // только один символ
    connect(le, SIGNAL(textEdited(QString)), SLOT(enableButton(QString)));

    cancelBtn = new QPushButton(tr("Cancel"));
    connect(cancelBtn, SIGNAL(clicked()), SLOT(reject()));

    insertBtn = new QPushButton(tr("Insert"));
    connect(insertBtn, SIGNAL(clicked()), SLOT(accept()));
    enableButton(le->text());

    QVBoxLayout *vbox = new QVBoxLayout;
    QHBoxLayout *hbox = new QHBoxLayout;

    hbox->addWidget(cancelBtn);
    hbox->addWidget(insertBtn);

    vbox->addWidget(le);
    vbox->addLayout(hbox);

    setLayout(vbox);
}

Number InsertCharDialog::getCharCode()
{
    QString t = le->text();
    QChar c = t[0];
    return Number(c.unicode());
}

void InsertCharDialog::enableButton(const QString &str)
{
    if(str.isEmpty())
        insertBtn->setEnabled(false);
    else
        insertBtn->setEnabled(true);
}

// ======================================================================

class ANDObj : public CalcObject
{
public:
    ANDObj()
    {
        m_unary = false;
        m_op = QObject::tr("&");
        m_priority = 4;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 & n2;
    }
};

class ORObj : public CalcObject
{
public:
    ORObj()
    {
        m_unary = false;
        m_op = QObject::tr("|");
        m_priority = 4;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 | n2;
    }
};

class XORObj : public CalcObject
{
public:
    XORObj()
    {
        m_unary = false;
        m_op = QObject::tr("^");
        m_priority = 4;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 ^ n2;
    }
};

class NOTObj : public CalcObject
{
public:
    NOTObj()
    {
        m_unary = true;
        m_op = QObject::tr("~");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return ~n1;
    }
};

class LogObj : public CalcObject
{
public:
    LogObj()
    {
        m_unary = true;
        m_op = QObject::tr("log");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        if(n1 <= 0)
            n1 = 1;    // позже нужно будет отдельно сообщать об ошибке
        return log10(n1.toDouble());
    }
};

class LnObj : public CalcObject
{
public:
    LnObj()
    {
        m_unary = true;
        m_op = QObject::tr("ln");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        if(n1 <= 0)
            n1 = 1;
        return log(n1.toDouble());
    }
};

class ModObj : public CalcObject
{
public:
    ModObj()
    {
        m_unary = false;
        m_op = QObject::tr("%");
        m_priority = 2;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 % n2;
    }
};

class IntObj : public CalcObject
{
public:
    IntObj()
    {
        m_unary = true;
        m_op = QObject::tr("int");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return n1.integer();
    }
};

class FracObj : public CalcObject
{
public:
    FracObj()
    {
        m_unary = true;
        m_op = QObject::tr("frac");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return n1.fraction();
    }
};

class FactorialObj : public CalcObject
{
public:
    FactorialObj()
    {
        m_unary = true;
        m_op = QObject::tr("!");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        if(n1.isUInteger())
        {
            quint64 t = 1;
            quint64 n = n1.toUInt64();
            while(n > 1)
            {
                t *= n;
                --n;
            }
            return Number(t);
        }
        // else ### error message ###
        // ещё выводить сообщение об ошибке, если происходит переполнение
        return Number(0);
    }
};

class AbsObj : public CalcObject
{
public:
    AbsObj()
    {
        m_unary = true;
        m_op = QObject::tr("|x|");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return n1 > 0 ? n1 : -n1;
    }
};

class OnesObj : public CalcObject
{
public:
    OnesObj()
    {
        m_unary = true;
        m_op = QObject::tr("ones");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        // простое инвентирование
        return ~n1;
    }
};

class TwosObj : public CalcObject
{
public:
    TwosObj()
    {
        m_unary = true;
        m_op = QObject::tr("twos");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return (~n1 + 1);
    }
};

class ShlObj : public CalcObject
{
public:
    ShlObj()
    {
        m_unary = true;
        m_op = QObject::tr("shl");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return (n1 << 1);
    }
};

class ShrObj : public CalcObject
{
public:
    ShrObj()
    {
        m_unary = true;
        m_op = QObject::tr("shr");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return (n1 >> 1);
    }
};

ProgrammingKeyboard::ProgrammingKeyboard(LineEdit *le, QWidget *parent) :
    QWidget(parent), lineEdit(le), dialog(0)
{
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);

    afButton[0] = Button::createButton(tr("A"), this, SLOT(digitSlot()));
    afButton[1] = Button::createButton(tr("B"), this, SLOT(digitSlot()));
    afButton[2] = Button::createButton(tr("C"), this, SLOT(digitSlot()));
    afButton[3] = Button::createButton(tr("D"), this, SLOT(digitSlot()));
    afButton[4] = Button::createButton(tr("E"), this, SLOT(digitSlot()));
    afButton[5] = Button::createButton(tr("F"), this, SLOT(digitSlot()));

    andButton = Button::createButton(tr("AND"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Logical And"));
    andButton->setCalcObject(new ANDObj);
    orButton = Button::createButton(tr("OR"), this, SLOT(operationSlot()),
                                    QKeySequence(), tr("Logical Or"));
    orButton->setCalcObject(new ORObj);
    xorButton = Button::createButton(tr("XOR"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Logical Xor"));
    xorButton->setCalcObject(new XORObj);
    notButton = Button::createButton(tr("NOT"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Logical Not"));
    notButton->setCalcObject(new NOTObj);
    modButton = Button::createButton(tr("mod"), this, SLOT(operationSlot()),
                                     QKeySequence(tr("|")), tr("Modulo"));
    modButton->setCalcObject(new ModObj);
    logButton = Button::createButton(tr("log"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Logarihm to base 10"));
    logButton->setCalcObject(new LogObj);
    lnButton = Button::createButton(tr("ln"), this, SLOT(operationSlot()),
                                    QKeySequence(), tr("Logarihm to base e"));
    lnButton->setCalcObject(new LnObj);
    intButton = Button::createButton(tr("int"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Integer"));
    intButton->setCalcObject(new IntObj);
    fracButton = Button::createButton(tr("frac"), this, SLOT(operationSlot()),
                                      QKeySequence(), tr("Fraction"));
    fracButton->setCalcObject(new FracObj);
    factorialButton = Button::createButton(tr("x!"), this, SLOT(operationSlot()),
                                           QKeySequence(tr("!")), tr("Factorial"));
    factorialButton->setCalcObject(new FactorialObj);
    absButton = Button::createButton(tr("|x|"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Absolute value"));
    absButton->setCalcObject(new AbsObj);
    charButton = Button::createButton(tr("a\u0301"), this, SLOT(insertCodeOfChar()),
                                      QKeySequence(), tr("Insert character code"));
    onesButton = Button::createButton(tr("ones"), this, SLOT(operationSlot()),
                                      QKeySequence(), tr("One's complement"));
    onesButton->setCalcObject(new OnesObj);
    twosButton = Button::createButton(tr("twos"), this, SLOT(operationSlot()),
                                      QKeySequence(), tr("Two's complement"));
    twosButton->setCalcObject(new TwosObj);
    shlButton = Button::createButton(tr("<<"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Shift left"));
    shlButton->setCalcObject(new ShlObj);
    shrButton = Button::createButton(tr(">>"), this, SLOT(operationSlot()),
                                     QKeySequence(), tr("Shift right"));
    shrButton->setCalcObject(new ShrObj);

    gridLayout->addWidget(afButton[3], 0, 0);
    gridLayout->addWidget(afButton[2], 1, 0);
    gridLayout->addWidget(afButton[1], 2, 0);
    gridLayout->addWidget(afButton[0], 3, 0);
    gridLayout->addWidget(andButton, 4, 0);
    gridLayout->addWidget(afButton[5], 0, 1);
    gridLayout->addWidget(afButton[4], 1, 1);
    gridLayout->addWidget(notButton, 2, 1);
    gridLayout->addWidget(xorButton, 3, 1);
    gridLayout->addWidget(orButton, 4, 1);
    gridLayout->addWidget(logButton, 0, 2);
    gridLayout->addWidget(lnButton, 1, 2);
    gridLayout->addWidget(intButton, 2, 2);
    gridLayout->addWidget(fracButton, 3, 2);
    gridLayout->addWidget(factorialButton, 4, 2);
    gridLayout->addWidget(absButton, 0, 3);
    gridLayout->addWidget(charButton, 1, 3);
    gridLayout->addWidget(modButton, 2, 3);
    gridLayout->addWidget(onesButton, 3, 3);
    gridLayout->addWidget(shlButton, 4, 3);
    gridLayout->addWidget(twosButton, 3, 4);
    gridLayout->addWidget(shrButton, 4, 4);

    setLayout(gridLayout);

 //   connect(lineEdit, SIGNAL(numberModeChanged(int)), SLOT(enableAF(int)));
    enableAF(10);   // ### TODO ###
}

void ProgrammingKeyboard::enableAF(int b)
{
    if(b == 16)
    {
        for(int i=0; i<6; ++i)
            afButton[i]->setEnabled(true);
    }
    else
    {
        for(int i=0; i<6; ++i)
            afButton[i]->setEnabled(false);
    }
}

void ProgrammingKeyboard::digitSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    lineEdit->addChar(btn->text().at(0));
}

void ProgrammingKeyboard::operationSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    lineEdit->addOperator(btn->calcObject());
}

void ProgrammingKeyboard::insertCodeOfChar()
{
    if(!dialog)
    {
        dialog = new InsertCharDialog;
    }

    dialog->exec();
    lineEdit->insertNumber(dialog->getCharCode());
}
