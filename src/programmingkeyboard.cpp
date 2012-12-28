#include <QGridLayout>
#include <QtCore/qmath.h>
#include <QPushButton>
#include "programmingkeyboard.h"
#include "button.h"
#include "lineedit.h"

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

    andButton = Button::createButton(tr("AND"), this, SLOT(twoOperandSlot()),
                                     QKeySequence(), tr("Logical And"));
    orButton = Button::createButton(tr("OR"), this, SLOT(twoOperandSlot()),
                                    QKeySequence(), tr("Logical Or"));
    xorButton = Button::createButton(tr("XOR"), this, SLOT(twoOperandSlot()),
                                     QKeySequence(), tr("Logical Xor"));
    notButton = Button::createButton(tr("NOT"), this, SLOT(notSlot()),
                                     QKeySequence(), tr("Logical Not"));
    modButton = Button::createButton(tr("mod"), this, SLOT(twoOperandSlot()),
                                     QKeySequence(tr("|")), tr("Modulo"));

    logButton = Button::createButton(tr("log"), this, SLOT(logSlot()),
                                     QKeySequence(), tr("Logarihm to base 10"));
    lnButton = Button::createButton(tr("ln"), this, SLOT(logSlot()),
                                    QKeySequence(), tr("Logarihm to base e"));

    intButton = Button::createButton(tr("int"), this, SLOT(intFracSlot()),
                                     QKeySequence(), tr("Integer"));
    fracButton = Button::createButton(tr("frac"), this, SLOT(intFracSlot()),
                                      QKeySequence(), tr("Fraction"));

    factorialButton = Button::createButton(tr("x!"), this, SLOT(factorialSlot()),
                                           QKeySequence(tr("!")), tr("Factorial"));
    absButton = Button::createButton(tr("|x|"), this, SLOT(absSlot()),
                                     QKeySequence(), tr("Absolute value"));
    charButton = Button::createButton(tr("a\u0301"), this, SLOT(insertCodeOfChar()),
                                      QKeySequence(), tr("Insert character code"));
    onesButton = Button::createButton(tr("ones"), this, SLOT(onesSlot()),
                                      QKeySequence(), tr("One's complement"));
    twosButton = Button::createButton(tr("twos"), this, SLOT(twosSlot()),
                                      QKeySequence(), tr("Two's complement"));

    shlButton = Button::createButton(tr("<<"), this, SLOT(shlSlot()),
                                     QKeySequence(), tr("Shift left"));
    shrButton = Button::createButton(tr(">>"), this, SLOT(shrSlot()),
                                     QKeySequence(), tr("Shift right"));

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

    connect(lineEdit, SIGNAL(calculateAll()), SLOT(resultSlot()));
    connect(lineEdit, SIGNAL(numberModeChanged(int)), SLOT(enableAF(int)));
    enableAF(lineEdit->numberMode());
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
    if(lineEdit->waitOperand())
    {
        lineEdit->setNumber(Number());
        lineEdit->setWait(false);
    }

    Button *btn = qobject_cast<Button*>(sender());

    QString text = lineEdit->text();
    if(text == "0") text.chop(1);
    text.append(btn->text());
    lineEdit->setNumber(text);
}

static Number calculate(Number n1, Number n2, const QString &op)
{
    if(op == QObject::tr("AND"))
        return n1 & n2;
    else if(op == QObject::tr("OR"))
        return n1 | n2;
    else if(op == QObject::tr("XOR"))
        return n1 ^ n2;
    // else
    return n1 % n2; // mod
}

void ProgrammingKeyboard::twoOperandSlot()
{
    lineEdit->emitCalculateAll();

    Number num = lineEdit->getNumber();
    Button *btn = qobject_cast<Button*>(sender());
    QString operation = btn->text();

    if(!lineEdit->waitOperand())
    {
        if(!operatorStr.isEmpty())
        {
            num = calculate(sumSoFar, num, operatorStr);
            lineEdit->setNumber(num);
        }
    }
    else
        operatorStr = "";

    operatorStr = operation;
    sumSoFar = num;
    lineEdit->setOperator(operation);
    lineEdit->setWait(true);
}

void ProgrammingKeyboard::resultSlot()
{
    Number num = lineEdit->getNumber();
    if(!operatorStr.isEmpty())
    {
        num = calculate(sumSoFar, num, operatorStr);
        lineEdit->setNumber(num);
        sumSoFar = 0;
        operatorStr = "";
    }
}

void ProgrammingKeyboard::notSlot()
{
    Number n = lineEdit->getNumber();
    lineEdit->setNumber(~n);
//    else
//        ;   // соообщить об ошибке.
            // придумать механизм отправки ошибок
}

void ProgrammingKeyboard::intFracSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    QString t = btn->text();

    Number num = lineEdit->getNumber();

    if(t == tr("int"))  // выделяем целую часть
        lineEdit->setNumber(num.integer());
    else    // дробную
        lineEdit->setNumber(num.fraction());
}

void ProgrammingKeyboard::factorialSlot()
{
    Number num = lineEdit->getNumber();
    if(num.isUInteger())
    {
        quint64 t = 1;
        quint64 n = num.toUInt64();
        while(n > 1)
        {
            t *= n;
            --n;
        }
        lineEdit->setNumber(Number(t));
    }
    // else ### error message ###
    // ещё выводить сообщение об ошибке, если происходит переполнение
}

void ProgrammingKeyboard::insertCodeOfChar()
{
    if(!dialog)
    {
        dialog = new InsertCharDialog;
    }

    dialog->exec();
    lineEdit->setNumber(dialog->getCharCode());
}

void ProgrammingKeyboard::logSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    QString t = btn->text();

    Number num = lineEdit->getNumber();
    if(num <= 0)
        num = 1;    // позже нужно будет отдельно сообщать об ошибке

    if(t == tr("log"))  // десятичный log_10
    {
        num = log10(num.toDouble());
        lineEdit->setNumber(num);
    }
    else    // натуральный log_e
    {
        num = log(num.toDouble());
        lineEdit->setNumber(num);
    }
}

void ProgrammingKeyboard::absSlot()
{
    Number num = lineEdit->getNumber();
    if(num < 0) num = - num;
    lineEdit->setNumber(num);
}

// следующие функции работают только с quint64 (беззнаковым целым)
void ProgrammingKeyboard::onesSlot()
{
    // простое инвентирование
    Number num = lineEdit->getNumber();
    lineEdit->setNumber(~num);
}

void ProgrammingKeyboard::twosSlot()
{
    // инвертировать и прибавить 1
    Number num = lineEdit->getNumber();
    lineEdit->setNumber(~num + 1);
}

void ProgrammingKeyboard::shlSlot()
{
    Number num = lineEdit->getNumber();
    num = num << 1;
    lineEdit->setNumber(num);
}

void ProgrammingKeyboard::shrSlot()
{
    Number num = lineEdit->getNumber();
    num = num >> 1;
    lineEdit->setNumber(num);
}
