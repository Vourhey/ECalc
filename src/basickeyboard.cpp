#include <QtGui>
#include "basickeyboard.h"
#include "lineedit.h"

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
    waitOperand = false;

    for(int i = 0; i < 10; ++i)
        sumOfMemory[i] = 0.0;

    backspaceButton = createButton(tr("\u2190"), SLOT(backspaceSlot()),
                                           QKeySequence(Qt::Key_Backspace));
    clearButton = createButton(tr("Clear"), SLOT(clearSlot()));
    clearAllButton = createButton(tr("Clear All"), SLOT(clearAllSlot()));

    percentButton = createButton(tr("%"), SLOT(unaryOperationSlot()));

    // цифры
    for(int i = 0; i < 10; ++i)
    {
        numberButton[i] = createButton(QString::number(i), SLOT(digitButtonSlot()),
                                     QKeySequence(QString::number(i)));
    }

    pointButton = new Button(tr("."));
    pointButton->setShortcut(QKeySequence(","));
    connect(pointButton, SIGNAL(clicked()), lineEdit, SLOT(setPoint()));

    divideButton = createButton(tr("\u00F7"), SLOT(twoOperandSlot()), QKeySequence("/"));
    multiplicationButton = createButton(tr("x"), SLOT(twoOperandSlot()), QKeySequence("*"));
    minusButton = createButton(tr("-"), SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Minus));
    plusButton = createButton(tr("+"), SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Plus));

    // TODO найти код символа радикала
    sqrtButton = createButton(tr("\u221A"), SLOT(unaryOperationSlot()));

    powerButton = createButton(tr("x\u00B2"), SLOT(unaryOperationSlot()));
    minusOneDegreeButton = createButton(tr("1/x"), SLOT(unaryOperationSlot()));
    resultButton = createButton(tr("="), SLOT(resultSlot()), QKeySequence(Qt::Key_Return));
}

Button *BasicKeyboard::createButton(const QString &text, const char *member, const QKeySequence &key)
{
    Button *btn = new Button(text);
    connect(btn, SIGNAL(clicked()), member);

    if(!key.isEmpty()) btn->setShortcut(key);
    return btn;
}

void BasicKeyboard::backspaceSlot()
{
    QString t = lineEdit->text();
    t.chop(1);
    if(t.isEmpty()) t = tr("0");
    lineEdit->setNumber(t.toDouble());
}

void BasicKeyboard::clearSlot()
{
    lineEdit->setNumber(0);
    waitOperand = false;
}

void BasicKeyboard::clearAllSlot()
{
    lineEdit->setNumber(0);
    lineEdit->resetOperator();
    sumSoFar = 0.0;
    waitOperand = false;
    additiveStr = "";
    multipliStr = "";
}


// ### TODO ###
void BasicKeyboard::digitButtonSlot()
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
    lineEdit->setNumber(text.toDouble());
}

// вспомогательная функция для подсчета
static qreal calculate(qreal op1, qreal op2, const QString &d)
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
    qreal number = lineEdit->getNumber();

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

            lineEdit->setNumber(number);
        }
        else
            multipliStr = "";

        additiveStr = operation;
        sumSoFar = number;
    }
    else // divide or multipli
    {
        if(waitOperand) // ещё один костыль
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
    waitOperand = true;
}

void BasicKeyboard::unaryOperationSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    qreal number = lineEdit->getNumber();

    QString operation = btn->text();

    if(operation == tr("\u221A"))
    {
        if(number >= 0.0)   // для пользователя ничего не произойдет
            number = sqrt(number);
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
        if(sumSoFar) number = sumSoFar * number / 100;
        else number /= 100;
    }

    lineEdit->setNumber(number);
}

void BasicKeyboard::resultSlot()
{
    qreal number = lineEdit->getNumber();

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
    waitOperand = true;
}
