#include <QtGui>
#include "calculator.h"
#include "lineedit.h"

Calculator::Calculator(QWidget *parent) :
    QWidget(parent)
{
    sumSoFar    = 0.0;
    factorSoFar = 0.0;
    waitOperand = false;

    for(int i = 0; i < 10; ++i)
        sumOfMemory[i] = 0.0;

    QGridLayout *gridLayout = new QGridLayout;

    lineEdit = new LineEdit;
    gridLayout->addWidget(lineEdit, 0, 0, 1, 6);

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceSlot()),
                                           QKeySequence(Qt::Key_Backspace));
    Button *clearButton = createButton(tr("Clear"), SLOT(clearSlot()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAllSlot()));

    gridLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    gridLayout->addWidget(clearButton, 1, 2, 1, 2);
    gridLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    // следующие три кнопочки имееют дополнительное мени (popup)
    Button *memoryReadButton = createButton(tr("MR"), SLOT(readMemory()));
    memoryReadButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *mr = new QMenu(tr("MR"));
    connect(mr, SIGNAL(aboutToShow()), SLOT(memoryMenuShow())); // элементы выстраиваются согласно памяти
    memoryReadButton->setMenu(mr);

    Button *memoryStoreButton = createButton(tr("MS"), SLOT(storeInMemory()));
    memoryStoreButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *ms = new QMenu(tr("MS"));
    connect(ms, SIGNAL(aboutToShow()), SLOT(memoryMenuShow()));
    memoryStoreButton->setMenu(ms);

    Button *memorySumButton = createButton(tr("M+"), SLOT(sumMemory()));
    memorySumButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *m = new QMenu(tr("M-"));
    m->addAction(tr("M-"), this, SLOT(minusMemory()));
    memorySumButton->setMenu(m);

    Button *percentButton = createButton(tr("%"), SLOT(unaryOperationSlot()));

    gridLayout->addWidget(memoryReadButton, 2, 0);
    gridLayout->addWidget(memoryStoreButton, 3, 0);
    gridLayout->addWidget(memorySumButton, 4, 0);
    gridLayout->addWidget(percentButton, 5, 0);

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

void Calculator::twoOperandSlot()
{
    qreal number = lineEdit->text().toDouble();

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
        if(waitOperand) // ещё один костыль
            additiveStr = "";
        multipliStr = operation;
        factorSoFar = number;
    }

    lineEdit->setOperator(operation);
    waitOperand = true;
}

void Calculator::unaryOperationSlot()
{
    Button *btn = qobject_cast<Button*>(sender());
    qreal number = lineEdit->text().toDouble();

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
    else if(operation == tr("%"))
    {
        if(sumSoFar) number = sumSoFar * number / 100;
        else number /= 100;
    }

    lineEdit->setText(QString::number(number));
}

void Calculator::resultSlot()
{
    qreal number = lineEdit->text().toDouble();

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

    lineEdit->resetOperator();
    waitOperand = true;
}

void Calculator::memoryMenuShow()
{
    QMenu *m = qobject_cast<QMenu*>(sender());
    QString t = m->title();

    QList<QAction*> actList;

    if(t == tr("MR"))
        for(int i=0; i<10; i++)
        {
            QAction *act = new QAction(QString::number(sumOfMemory[i]), this);
            act->setData(QVariant(i));  // номер ячейки
            connect(act, SIGNAL(triggered()), this, SLOT(readMemory()));
            actList.append(act);
        }
    else
        for(int i=0; i<10; i++)
        {
            QAction *act = new QAction(QString::number(sumOfMemory[i]), this);
            act->setData(QVariant(i));
            connect(act, SIGNAL(triggered()), this, SLOT(storeInMemory()));
            actList.append(act);
        }

    m->clear();
    m->addActions(actList);
}

void Calculator::showMemory()
{
    if(sumOfMemory[0])
        lineEdit->setMemory(true);
    else
        lineEdit->setMemory(false);
    lineEdit->repaint();
    waitOperand = true;
}

void Calculator::readMemory()
{
    // поддерживаем все 10 регистров памяти для чтения ...
    QAction *act = qobject_cast<QAction*>(sender());
    int i = act ? act->data().toInt() : 0;
    lineEdit->setText(QString::number(sumOfMemory[i]));
}

void Calculator::storeInMemory()
{
    // ... и для сохранения ...
    QAction *act = qobject_cast<QAction*>(sender());
    int i = act ? act->data().toInt() : 0;
    sumOfMemory[i] = lineEdit->text().toDouble();
    showMemory();
}

void Calculator::sumMemory()
{
    // ... но складываем и вычитаем только первый регистр
    sumOfMemory[0] += lineEdit->text().toDouble();
    showMemory();
}

void Calculator::minusMemory()
{
    sumOfMemory[0] -= lineEdit->text().toDouble();
    showMemory();
}
