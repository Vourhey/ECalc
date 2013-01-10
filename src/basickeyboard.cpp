#include <QtGui>
#include "basickeyboard.h"

class AddObj : public CalcObject
{
public:
    AddObj()
    {
        m_unary = false;
        m_op = QObject::tr("+");
        m_priority = 3;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 + n2;
    }
};

class MinusObj : public CalcObject
{
public:
    MinusObj()
    {
        m_unary = false;
        m_op = QObject::tr("-");
        m_priority = 3;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 - n2;
    }
};

class MultiplicationObj : public CalcObject
{
public:
    MultiplicationObj()
    {
        m_unary = false;
        m_op = QObject::tr("*");
        m_priority = 2;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 * n2;
    }
};

class DivideObj : public CalcObject
{
public:
    DivideObj()
    {
        m_unary = false;
        m_op = QObject::tr("\u00F7");
        m_priority = 2;
    }

    Number calc(Number n1, Number n2)
    {
        return n1 / n2;
    }
};

class SquareObj : public CalcObject
{
public:
    SquareObj()
    {
        m_unary = true;
        m_op = QObject::tr("\u221A");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return qSqrt(n1.toDouble());
    }
};

class PowerObj : public CalcObject
{
public:
    PowerObj()
    {
        m_unary = true;
        m_op = QObject::tr("x\u00B2");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return n1 * n1;
    }
};

class MinusOneDegreeObj : public CalcObject
{
public:
    MinusOneDegreeObj()
    {
        m_unary = true;
        m_op = QObject::tr("1/x");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return Number(1) / n1;
    }
};

class MinusUnaryObj : public CalcObject
{
public:
    MinusUnaryObj()
    {
        m_unary = true;
        m_op = QObject::tr("\u00B1");
        m_priority = 1;
    }

    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return -n1;
    }
};

class LeftBraceObj : public CalcObject
{
public:
    LeftBraceObj()
    {
        m_unary = false;
        m_op = QObject::tr("(");
        m_priority = 5;
    }

    // не нужно
    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return n1;
    }
};

class RightBraceObj : public CalcObject
{
public:
    RightBraceObj()
    {
        m_unary = false;
        m_op = QObject::tr(")");
        m_priority = 5;
    }

    // не нужно
    Number calc(Number n1, Number n2)
    {
        Q_UNUSED(n2)
        return n1;
    }
};

BasicKeyboard::BasicKeyboard(LineEdit *le, QWidget *parent) :
    QWidget(parent), m_lineEdit(le)
{
    initDefault();

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(0);

    mainLayout->addWidget(clearAllButton, 0, 0);
    mainLayout->addWidget(clearButton, 0, 1);
    mainLayout->addWidget(leftBraceButton, 0, 2);
    mainLayout->addWidget(rightBraceButton, 0, 3);
    mainLayout->addWidget(backspaceButton, 0, 4);

    int number = 1;
    for(int i = 3; i > 0; --i)
        for(int j = 0; j < 3; ++j)
        {
            mainLayout->addWidget(numberButton[number], i, j);
            ++number;
        }

    mainLayout->addWidget(numberButton[0], 4, 0);
    mainLayout->addWidget(pointButton, 4, 1);
    mainLayout->addWidget(minusUnaryButton, 4, 2);

    mainLayout->addWidget(divideButton, 1, 3);
    mainLayout->addWidget(multiplicationButton, 2, 3);
    mainLayout->addWidget(minusButton, 3, 3);
    mainLayout->addWidget(plusButton, 4, 3);
    mainLayout->addWidget(sqrtButton, 1, 4);
    mainLayout->addWidget(powerButton, 2, 4);
    mainLayout->addWidget(minusOneDegreeButton, 3, 4);
    mainLayout->addWidget(resultButton, 4, 4);

    setLayout(mainLayout);

    connect(m_lineEdit, SIGNAL(numberModeChanged(int)), SLOT(enableDigit(int)));
}


// выполняет начальную инициализацию
void BasicKeyboard::initDefault()
{
    backspaceButton = Button::createButton(tr("\u2190"), m_lineEdit, SLOT(backspace()),
                                           QKeySequence(Qt::Key_Backspace), tr("Backspace"));
    clearButton = Button::createButton(tr("C"), m_lineEdit, SLOT(clearSlot()),
                                       QKeySequence(Qt::Key_Delete), tr("Clear display"));
    clearAllButton = Button::createButton(tr("AC"), m_lineEdit, SLOT(clearAll()),
                                          QKeySequence(), tr("Clear All"));

    minusUnaryButton = Button::createButton(tr("\u00B1"), this, SLOT(operationSlot()),
                                         QKeySequence(Qt::Key_Percent), tr("Plus-minus"));
    minusUnaryButton->setCalcObject(new MinusUnaryObj);

    // цифры
    for(int i = 0; i < 10; ++i)
    {
        numberButton[i] = Button::createButton(QString::number(i), this, SLOT(digitButtonSlot()),
                                     QKeySequence(QString::number(i)));
    }

    pointButton = Button::createButton(tr("."), m_lineEdit, SLOT(addPoint()),
                                       QKeySequence("."));
    divideButton = Button::createButton(tr("\u00F7"), this, SLOT(operationSlot()),
                                        QKeySequence("/"), tr("Division"));
    divideButton->setCalcObject(new DivideObj);
    multiplicationButton = Button::createButton(tr("x"), this, SLOT(operationSlot()),
                                                QKeySequence("*"), tr("Multiplication"));
    multiplicationButton->setCalcObject(new MultiplicationObj);
    minusButton = Button::createButton(tr("-"), this, SLOT(operationSlot()),
                                       QKeySequence(Qt::Key_Minus), tr("Subtract"));
    minusButton->setCalcObject(new MinusObj);
    plusButton = Button::createButton(tr("+"), this, SLOT(operationSlot()),
                                      QKeySequence(Qt::Key_Plus), tr("Add"));
    plusButton->setCalcObject(new AddObj);
    sqrtButton = Button::createButton(tr("\u221A"), this, SLOT(operationSlot()),
                                      QKeySequence(tr("Ctrl+R")), tr("Root"));
    sqrtButton->setCalcObject(new SquareObj);
    powerButton = Button::createButton(tr("x\u00B2"), this, SLOT(operationSlot()),
                                       QKeySequence(tr("Ctrl+2")), tr("Square"));
    powerButton->setCalcObject(new PowerObj);
    minusOneDegreeButton = Button::createButton(tr("1/x"), this, SLOT(operationSlot()),
                                                QKeySequence(tr("Ctrl+I")), tr("Invert"));
    minusOneDegreeButton->setCalcObject(new MinusOneDegreeObj);
    resultButton = Button::createButton(tr("="), m_lineEdit, SLOT(calculate()),
                                        QKeySequence(Qt::Key_Return));
    leftBraceButton = Button::createButton(tr("("), this, SLOT(operationSlot()),
                                           QKeySequence("("));
    leftBraceButton->setCalcObject(new LeftBraceObj);
    rightBraceButton = Button::createButton(tr(")"), this, SLOT(operationSlot()),
                                           QKeySequence(")"));
    rightBraceButton->setCalcObject(new RightBraceObj);
}

void BasicKeyboard::digitButtonSlot()
{
    Button *btn = qobject_cast<Button*>(sender());

    m_lineEdit->addChar(btn->text().at(0));
}

void BasicKeyboard::operationSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    m_lineEdit->addOperator(btn->calcObject());
}

void BasicKeyboard::enableDigit(int b)
{
    if(b == 10)
    {
        for(int i=0; i<10; i++)
            numberButton[i]->setEnabled(true);
    }
    else if(b == 8)
    {
        for(int i=0; i<8; ++i)
            numberButton[i]->setEnabled(true);
        numberButton[8]->setEnabled(false);
        numberButton[9]->setEnabled(false);
    }
    else if(b == 2)
    {
        numberButton[0]->setEnabled(true);
        numberButton[1]->setEnabled(true);
        for(int i=2; i<10; ++i)
            numberButton[i]->setEnabled(false);
    }
}
