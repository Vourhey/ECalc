#include <QtGui>
#include "calculator.h"
#include "lineedit.h"
#include "bineditor.h"
#include "numbersystemswitcher.h"

/*
  Схема интерфейса
  +------------------------------------+
  | lineEdit                           |
  +------------------------------------+
  +------------------------------------+
  | виджет перевода величин            | // пока в планах
  | (появляется в advance mode)        |
  +------------------------------------+
  +------------------------------------+
  | виджет перевода из одной системы   |
  | счисления в другую (в programming) |
  +------------------------------------+
  +------------------------------------+
  | BinEditor (двоичный редактор)      |
  | появляется в programming           |
  +------------------------------------+
  +-----------+ +--------+ +-----------+
  | backspace | |  clear | | clear all |
  +-----------+ +--------+ +-----------+
  +----------------------+ +-----------+
  | standart buttons     | | option    |
  |                      | | functions |
  +----------------------+ +-----------+
  */

Calculator::Calculator(QWidget *parent) :
    QWidget(parent)
{
    initDefault();

    mainLayout = new QGridLayout;

    mainLayout->addWidget(lineEdit, 0, 0, 1, 6);

    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 4, 1, 2);

    mainLayout->addWidget(memoryReadButton, 3, 0);
    mainLayout->addWidget(memoryStoreButton, 4, 0);
    mainLayout->addWidget(memorySumButton, 5, 0);
    mainLayout->addWidget(percentButton, 6, 0);

    int number = 1;
    for(int i = 5; i > 2; --i)
        for(int j = 1; j < 4; ++j)
        {
            mainLayout->addWidget(numberButton[number], i, j);
            ++number;
        }

    mainLayout->addWidget(numberButton[0], 6, 1);
    mainLayout->addWidget(pointButton, 6, 2);
    mainLayout->addWidget(plusMinusButton, 6, 3);

    mainLayout->addWidget(divideButton, 3, 4);
    mainLayout->addWidget(multiplicationButton, 4, 4);
    mainLayout->addWidget(minusButton, 5, 4);
    mainLayout->addWidget(plusButton, 6, 4);
    mainLayout->addWidget(sqrtButton, 3, 5);
    mainLayout->addWidget(powerButton, 4, 5);
    mainLayout->addWidget(minusOneDegreeButton, 5, 5);
    mainLayout->addWidget(resultButton, 6, 5);

    setMode(); // Basic

    setLayout(mainLayout);
}

// выполняет начальную инициализацию
void Calculator::initDefault()
{
    sumSoFar    = 0.0;
    factorSoFar = 0.0;
    waitOperand = false;

    for(int i = 0; i < 10; ++i)
        sumOfMemory[i] = 0.0;

    lineEdit = new LineEdit;

    // выделиться память при необходимости
    binEditor = 0;
    numsysSwitcher = 0;

    backspaceButton = createButton(tr("Backspace"), SLOT(backspaceSlot()),
                                           QKeySequence(Qt::Key_Backspace));
    clearButton = createButton(tr("Clear"), SLOT(clearSlot()));
    clearAllButton = createButton(tr("Clear All"), SLOT(clearAllSlot()));

    // следующие три кнопочки имееют дополнительное мени (popup)
    memoryReadButton = createButton(tr("MR"), SLOT(readMemory()));
    memoryReadButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *mr = new QMenu(tr("MR"));
    connect(mr, SIGNAL(aboutToShow()), SLOT(memoryMenuShow())); // элементы выстраиваются согласно памяти
    memoryReadButton->setMenu(mr);

    memoryStoreButton = createButton(tr("MS"), SLOT(storeInMemory()));
    memoryStoreButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *ms = new QMenu(tr("MS"));
    connect(ms, SIGNAL(aboutToShow()), SLOT(memoryMenuShow()));
    memoryStoreButton->setMenu(ms);

    memorySumButton = createButton(tr("M+"), SLOT(sumMemory()));
    memorySumButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *m = new QMenu(tr("M-"));
    m->addAction(tr("M-"), this, SLOT(minusMemory()));
    memorySumButton->setMenu(m);

    percentButton = createButton(tr("%"), SLOT(unaryOperationSlot()));

    // цифры
    for(int i = 0; i < 10; ++i)
        numberButton[i] = createButton(QString::number(i), SLOT(digitButtonSlot()),
                                     QKeySequence(QString::number(i)));

    pointButton = createButton(tr("."), SLOT(pointButtonSlot()), QKeySequence(","));
    plusMinusButton = createButton(tr("\xB1"), SLOT(unaryOperationSlot()));

    divideButton = createButton(tr("\xF7"), SLOT(twoOperandSlot()), QKeySequence("/"));
    multiplicationButton = createButton(tr("x"), SLOT(twoOperandSlot()), QKeySequence("*"));
    minusButton = createButton(tr("-"), SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Minus));
    plusButton = createButton(tr("+"), SLOT(twoOperandSlot()), QKeySequence(Qt::Key_Plus));

    sqrtButton = createButton(tr("Sqrt"), SLOT(unaryOperationSlot()));
    powerButton = createButton(tr("x\xB2"), SLOT(unaryOperationSlot()));
    minusOneDegreeButton = createButton(tr("1/x"), SLOT(unaryOperationSlot()));
    resultButton = createButton(tr("="), SLOT(resultSlot()), QKeySequence(Qt::Key_Return));
}

void Calculator::setMode(int mode)
{
    mainLayout->removeWidget(binEditor);
    mainLayout->removeWidget(numsysSwitcher);
    mainLayout->removeWidget(lineEdit);
    if(binEditor) binEditor->hide();
    if(numsysSwitcher) numsysSwitcher->hide();

    switch(mode)
    {
    case 1: // basic        
        mainLayout->addWidget(lineEdit, 0,0,1,6);
        break;
    case 2: // advance
        mainLayout->addWidget(lineEdit, 0,0,1,6);

        if(!numsysSwitcher) numsysSwitcher = new NumberSystemSwitcher;
        numsysSwitcher->show();
        mainLayout->addWidget(numsysSwitcher, 2,0,1,6);
        break;
    case 3: // financical
        mainLayout->addWidget(lineEdit, 0,0,1,6);
        break;
    case 4: // programming
        mainLayout->addWidget(lineEdit, 0,0,1,6);

        if(!binEditor) binEditor = new BinEditor;
        binEditor->show();
        mainLayout->addWidget(binEditor, 2,0,1,6);
        break;
    }
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
        if(!multipliStr.isEmpty())
        {
            number = calculate(factorSoFar, number, multipliStr);
            lineEdit->setText(QString::number(number));
        }
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
