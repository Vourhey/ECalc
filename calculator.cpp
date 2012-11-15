#include <QtGui>
#include "calculator.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent)
{
    sumOfMemory = 0.0;
    sumSoFar    = 0.0;
    factorSoFar = 0.0;
    waitOperand = false;

    QGridLayout *gridLayout = new QGridLayout;

    lineEdit = new QLineEdit(tr("0"));
    lineEdit->setAlignment(Qt::AlignRight);
    lineEdit->setMaxLength(15);
    lineEdit->setReadOnly(true);

    QFont f = lineEdit->font();
    f.setPointSize(f.pointSize() + 8);
    lineEdit->setFont(f);

    gridLayout->addWidget(lineEdit, 0, 0, 1, 6);

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceSlot()),
                                           QKeySequence(Qt::Key_Backspace));
    Button *clearButton = createButton(tr("Clear"), SLOT(clearSlot()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAllSlot()));

    gridLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    gridLayout->addWidget(clearButton, 1, 2, 1, 2);
    gridLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    Button *memoryClearButton = createButton(tr("MC"), SLOT(clearMemory()));
    Button *memoryReadButton = createButton(tr("MR"), SLOT(readMemory()));
    Button *memoryStoreButton = createButton(tr("MS"), SLOT(storeInMemory()));
    Button *memorySumButton = createButton(tr("M+"), SLOT(sumMemory()));

    gridLayout->addWidget(memoryClearButton, 2, 0);
    gridLayout->addWidget(memoryReadButton, 3, 0);
    gridLayout->addWidget(memoryStoreButton, 4, 0);
    gridLayout->addWidget(memorySumButton, 5, 0);

    // цифры
    int number = 1;
    for(int i = 4; i > 1; --i)
        for(int j = 1; j < 4; ++j)
        {
            Button *btn = createButton(QString::number(number), SLOT(digitButtonSlot()),
                                     QKeySequence(QString::number(number)));
            gridLayout->addWidget(btn, i, j);
            ++number;
            if(number == 10) break;
        }

    Button *zeroButton = createButton(tr("0"), SLOT(digitButtonSlot()), QKeySequence(Qt::Key_0));
    Button *pointButton = createButton(tr("."), SLOT(pointButtonSlot()), QKeySequence(","));
    Button *plusMinusButton = createButton(tr("\xB1"), SLOT(unaryOperationSlot()));

    gridLayout->addWidget(zeroButton, 5, 1);
    gridLayout->addWidget(pointButton, 5, 2);
    gridLayout->addWidget(plusMinusButton, 5, 3);

    Button *divideButton = createButton(tr("\xF7"), SLOT(twoOperandSlot()), QKeySequence("/"));
    Button *multiplicationButton = createButton(tr("x"), SLOT(twoOperandSlot()), QKeySequence("*"));
    Button *minusButton = createButton(tr("-"), SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Minus));
    Button *plusButton = createButton(tr("+"), SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Plus));

    Button *sqrtButton = createButton(tr("Sqrt"), SLOT(unaryOperationSlot()));
    Button *powerButton = createButton(tr("x\xB2"), SLOT(unaryOperationSlot()));
    Button *minusOneDegreeButton = createButton(tr("1/x"), SLOT(unaryOperationSlot()));
    Button *resultButton = createButton(tr("="), SLOT(resultSlot()), QKeySequence(Qt::Key_Enter));

    gridLayout->addWidget(divideButton, 2, 4);
    gridLayout->addWidget(multiplicationButton, 3, 4);
    gridLayout->addWidget(minusButton, 4, 4);
    gridLayout->addWidget(plusButton, 5, 4);
    gridLayout->addWidget(sqrtButton, 2, 5);
    gridLayout->addWidget(powerButton, 3, 5);
    gridLayout->addWidget(minusOneDegreeButton, 4, 5);
    gridLayout->addWidget(resultButton, 5, 5);

    setLayout(gridLayout);
}

Button *Calculator::createButton(const QString &text, const char *member, const QKeySequence &key)
{
    Button *btn = new Button(text);
    connect(btn, SIGNAL(clicked()), member);

    if(!key.isEmpty()) btn->setShortcut(key);
    return btn;
}

void Calculator::backspaceSlot()
{
    QString t = lineEdit->text();
    t.chop(1);
    if(t.isEmpty()) t = tr("0");
    lineEdit->setText(t);
}

void Calculator::clearSlot()
{
    lineEdit->setText(tr("0"));
    waitOperand = false;
}

void Calculator::clearAllSlot()
{
    lineEdit->setText(tr("0"));
    sumOfMemory = 0.0;
    sumSoFar = 0.0;
    waitOperand = false;
    additiveStr = "";
    multipliStr = "";
}

void Calculator::digitButtonSlot()
{
    if(waitOperand)
    {
        lineEdit->clear();
        waitOperand = false;
    }

    Button *btn = qobject_cast<Button*>(sender());

    QString text = lineEdit->text();
    if(text == "0") text.chop(1);
    text.append(btn->text());
    lineEdit->setText(text);
}

void Calculator::pointButtonSlot()
{
    QString text = lineEdit->text();
    if(!text.contains('.'))
        text.append('.');
    lineEdit->setText(text);
}

// вспомогательная функция для подсчета
static double calculate(double op1, double op2, const QString &d)
{
    if(d == QObject::tr("+"))
        return op1 + op2;
    if(d == QObject::tr("-"))
        return op1 - op2;
    if(d == QObject::tr("x"))
        return op1 * op2;

    // ну, других вариантов не остается
    return op1 / op2;
}

void Calculator::twoOperandSlot()
{
    double number = lineEdit->text().toDouble();

    Button *btn = qobject_cast<Button*>(sender());
    QString operation = btn->text();

    if(operation == tr("+") || operation == tr("-"))
    {
        if(!waitOperand)    // знаю, говнокод... зато работает
        {
            if(!multipliStr.isEmpty())
            {
                number = calculate(factorSoFar, number, multipliStr);
                multipliStr = "";
                factorSoFar = 0.0;
            }

            if(!additiveStr.isEmpty())
                number = calculate(sumSoFar, number, additiveStr);

            lineEdit->setText(QString::number(number));
        }

        additiveStr = operation;
        sumSoFar = number;
    }
    else // divide or multipli
    {
        multipliStr = operation;
        factorSoFar = number;
    }

    waitOperand = true;
}

void Calculator::unaryOperationSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    double number = lineEdit->text().toDouble();

    QString operation = btn->text();

    if(operation == tr("Sqrt"))
    {
        if(number >= 0.0)   // для пользователя ничего не произойдет
            number = sqrt(number);
    }
    else if(operation == tr("x\xB2"))
        number = number * number;
    else if(operation == tr("1/x"))
    {
        if(number != 0)
            number = 1 / number;
    }
    else if(operation == tr("\xB1"))
        number = -number;

    lineEdit->setText(QString::number(number));
}

void Calculator::resultSlot()
{
    double number = lineEdit->text().toDouble();

    if(!multipliStr.isEmpty())
    {
        number = calculate(factorSoFar, number, multipliStr);
        lineEdit->setText(QString::number(number));
        multipliStr = "";
        factorSoFar = 0.0;
    }

    if(!additiveStr.isEmpty())
    {
        number = calculate(sumSoFar, number, additiveStr);
        lineEdit->setText(QString::number(number));
        additiveStr = "";
        sumSoFar = 0.0;
    }

    waitOperand = true;
}

void Calculator::clearMemory()
{
    sumOfMemory = 0.0;
}

void Calculator::readMemory()
{
    lineEdit->setText(QString::number(sumOfMemory));
}

void Calculator::storeInMemory()
{
    sumOfMemory = lineEdit->text().toDouble();
}

void Calculator::sumMemory()
{
    sumOfMemory += lineEdit->text().toDouble();
}
