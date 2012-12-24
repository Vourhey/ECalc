#include <QtGui>
#include "basickeyboard.h"

BasicKeyboard::BasicKeyboard(LineEdit *le, QWidget *parent) :
    QWidget(parent), lineEdit(le)
{
    initDefault();

    mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);

    mainLayout->addWidget(clearAllButton, 0, 0, 1, 2);
    mainLayout->addWidget(clearButton, 0, 2, 1, 2);
    mainLayout->addWidget(backspaceButton, 0, 4, 1, 1);

    int number = 1;
    for(int i = 3; i > 0; --i)
        for(int j = 0; j < 3; ++j)
        {
            mainLayout->addWidget(numberButton[number], i, j);
            ++number;
        }

    mainLayout->addWidget(numberButton[0], 4, 0);
    mainLayout->addWidget(pointButton, 4, 1);
    mainLayout->addWidget(percentButton, 4, 2);

    mainLayout->addWidget(divideButton, 1, 3);
    mainLayout->addWidget(multiplicationButton, 2, 3);
    mainLayout->addWidget(minusButton, 3, 3);
    mainLayout->addWidget(plusButton, 4, 3);
    mainLayout->addWidget(sqrtButton, 1, 4);
    mainLayout->addWidget(powerButton, 2, 4);
    mainLayout->addWidget(minusOneDegreeButton, 3, 4);
    mainLayout->addWidget(resultButton, 4, 4);

    setLayout(mainLayout);
}

// выполняет начальную инициализацию
void BasicKeyboard::initDefault()
{
    sumSoFar    = 0.0;
    factorSoFar = 0.0;

    backspaceButton = Button::createButton(tr("\u2190"), this, SLOT(backspaceSlot()),
                                           QKeySequence(Qt::Key_Backspace));
    clearButton = Button::createButton(tr("Clear"), this, SLOT(clearSlot()));
    clearAllButton = Button::createButton(tr("Clear All"), this, SLOT(clearAllSlot()));

    percentButton = Button::createButton(tr("%"), this, SLOT(unaryOperationSlot()));

    // цифры
    for(int i = 0; i < 10; ++i)
    {
        numberButton[i] = Button::createButton(QString::number(i), this, SLOT(digitButtonSlot()),
                                     QKeySequence(QString::number(i)));
    }

    pointButton = new Button(tr("."));
    pointButton->setShortcut(QKeySequence(","));
    connect(pointButton, SIGNAL(clicked()), lineEdit, SLOT(setPoint()));

    divideButton = Button::createButton(tr("\u00F7"), this, SLOT(twoOperandSlot()), QKeySequence("/"));
    multiplicationButton = Button::createButton(tr("x"), this, SLOT(twoOperandSlot()), QKeySequence("*"));
    minusButton = Button::createButton(tr("-"), this, SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Minus));
    plusButton = Button::createButton(tr("+"), this, SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Plus));

    // TODO найти код символа радикала
    sqrtButton = Button::createButton(tr("\u221A"), this, SLOT(unaryOperationSlot()));

    powerButton = Button::createButton(tr("x\u00B2"), this, SLOT(unaryOperationSlot()));
    minusOneDegreeButton = Button::createButton(tr("1/x"), this, SLOT(unaryOperationSlot()));
    resultButton = Button::createButton(tr("="), this, SLOT(resultSlot()), QKeySequence(Qt::Key_Return));
}

void BasicKeyboard::backspaceSlot()
{
    QString t = lineEdit->text();
    t.chop(1);
    if(t.isEmpty()) t = tr("0");
    lineEdit->setNumber(t);
}

void BasicKeyboard::clearSlot()
{
    lineEdit->setNumber(Number());
    lineEdit->setWait(false);
}

void BasicKeyboard::clearAllSlot()
{
    lineEdit->setNumber(Number());
    lineEdit->resetOperator();
    lineEdit->setWait(false);
    sumSoFar = 0.0;
    additiveStr = "";
    multipliStr = "";
}


// ### TODO ###
void BasicKeyboard::digitButtonSlot()
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

// вспомогательная функция для подсчета
static Number calculate(Number op1, Number op2, const QString &d)
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

void BasicKeyboard::twoOperandSlot()
{
    Number number = lineEdit->getNumber();

    Button *btn = qobject_cast<Button*>(sender());
    QString operation = btn->text();

    if(operation == tr("+") || operation == tr("-"))
    {
        if(!lineEdit->waitOperand())    // знаю, говнокод... зато работает
        {
            if(!multipliStr.isEmpty())
            {
                number = calculate(factorSoFar, number, multipliStr);
                multipliStr = "";
                factorSoFar = 0.0;
            }

            if(!additiveStr.isEmpty())
                number = calculate(sumSoFar, number, additiveStr);

            lineEdit->setNumber(number);
        }
        else
            multipliStr = "";

        additiveStr = operation;
        sumSoFar = number;
    }
    else // divide or multipli
    {
        if(lineEdit->waitOperand()) // ещё один костыль
            additiveStr = "";
     /*   if(!multipliStr.isEmpty())
        {
            number = calculate(factorSoFar, number, multipliStr);
            lineEdit->setNumber(number);
        } */
        multipliStr = operation;
        factorSoFar = number;
    }

    lineEdit->setOperator(operation);
    lineEdit->setWait(true);
}

void BasicKeyboard::unaryOperationSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    Number number = lineEdit->getNumber();

    QString operation = btn->text();

    if(operation == tr("\u221A"))
    {
        if(number >= 0.0)   // для пользователя ничего не произойдет
            number = sqrt(number.toDouble());
    }
    else if(operation == tr("x\u00B2"))
        number = number * number;
    else if(operation == tr("1/x"))
    {
        if(number != 0)
            number = 1 / number;
    }
    else if(operation == tr("%"))
    {
        if(sumSoFar != 0) number = number * sumSoFar / 100;
        else number /= 100;
    }

    lineEdit->setNumber(number);
}

void BasicKeyboard::resultSlot()
{
    Number number = lineEdit->getNumber();

    if(!multipliStr.isEmpty())
    {
        number = calculate(factorSoFar, number, multipliStr);
        lineEdit->setNumber(number);
        multipliStr = "";
        factorSoFar = 0.0;
    }

    if(!additiveStr.isEmpty())
    {
        number = calculate(sumSoFar, number, additiveStr);
        lineEdit->setNumber(number);
        additiveStr = "";
        sumSoFar = 0.0;
    }

    lineEdit->resetOperator();
    lineEdit->setWait(true);
}
