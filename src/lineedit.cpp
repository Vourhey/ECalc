#include <QtGui>
#include "lineedit.h"
#include "history.h"

QDebug operator<<(QDebug dbg, CalcObject *c)
{
    dbg.nospace() << c->getOperator();

    return dbg.space();
}

QDebug operator<<(QDebug dbg, Number n)
{
    dbg.nospace() << n.toString();

    return dbg.space();
}

// модифицированное поле ввода
LineEdit::LineEdit(QWidget *parent) :
    QLineEdit(parent), contextMenu(0)
{
//    m_history = new History(this, tr("log"));

    copyAct = new QAction(tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
    connect(copyAct, SIGNAL(triggered()), SLOT(copy()));

    pasteAct = new QAction(tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
    connect(pasteAct, SIGNAL(triggered()), SLOT(pasteSlot()));

    setText(tr("0"));
    setAlignment(Qt::AlignRight);
    setReadOnly(true);

    QFont f = font();
    f.setPointSize(f.pointSize() + 8);
    setFont(f);

    m_waitOperand = false;
    isDisplayed = false;
    setText(tr("0"));

//    setNumberMode();
}

void LineEdit::addChar(QChar c)
{
    if(m_waitOperand)
    {
        setText(tr("0"));
        m_waitOperand = false;
    }

    QString t = text();
    if(t == tr("0")) t = "";
    setText(t + c);
    isDisplayed = false;
}

void LineEdit::addPoint()
{
    QString t = text();
    if(!t.contains('.'))
        setText(t.append('.'));
}

// ### TODO ###
// переработать алгоритм
void LineEdit::addOperator(CalcObject *co)
{
    if(co->getOperator().at(0) == '(')
    {
        postfix.push(co);
        isDisplayed = false;
        return;
    }

    if(co->isUnary())
    {
        Number n;
        if(isDisplayed)
            n = m_numbers.pop();
        else
            n = Number(text());
        n = co->calc(n);
        m_numbers.push(n);
        setText(n.toString());
        isDisplayed = true;

        qDebug() << m_numbers;
        qDebug() << postfix;

        return;
    }

    if(m_waitOperand)   // пользователь просто меняет знак операции
    {
        if(!postfix.isEmpty())
            postfix.pop();
        postfix.push(co);
        m_operator = co->getOperator();
        repaint();
        return;
    }

    if(!isDisplayed)
        m_numbers.push(Number(text()));

    p_calc(co);

    m_waitOperand = true;
    setText(m_numbers.top().toString());
    repaint();

    qDebug() << m_numbers;
    qDebug() << postfix;
}

// Основано на обратной польской нотации
void LineEdit::p_calc(CalcObject *co)
{
    Number n;
    if(!postfix.isEmpty() && co->getOperator() == tr(")"))
    {
        CalcObject *c1 = postfix.pop();
        while(c1->getOperator().at(0) != '(')
        {
            n = oneOperation(c1);
            m_numbers.push(n);
            c1 = postfix.pop();
        }
        isDisplayed = true;
        return;
    }

    while(!postfix.isEmpty() && co->priority() >= postfix.top()->priority())
    {
        CalcObject *c1 = postfix.pop();

        n = oneOperation(c1);
        m_numbers.push(n);
    }
    postfix.push(co);
    m_operator = co->getOperator();
    isDisplayed = false;
}

Number LineEdit::oneOperation(CalcObject *co)
{
    Number n2 = m_numbers.pop();
    Number n1 = m_numbers.pop();
    return co->calc(n1, n2);
}

void LineEdit::calculate()
{
    // не могу объяснить, зачем условие.. так работает
    if(!isDisplayed)
        m_numbers.push(Number(text()));

    Number n;

    while(!postfix.isEmpty())
    {
        CalcObject *c1 = postfix.pop();
        n = oneOperation(c1);
        m_numbers.push(n);
    }

    clearAll();
    m_numbers.push(n);
    setText(n.toString());
    isDisplayed = true;
}

// очищаем только экран
void LineEdit::clearSlot()
{
    setText(tr("0"));
}

void LineEdit::clearAll()
{
    m_numbers.clear();
    postfix.clear();
    setText(tr("0"));
    m_waitOperand = true;
    isDisplayed = false;
    m_operator = "";
}

void LineEdit::insertNumber(Number n)
{
    setText(n.toString());
    m_waitOperand = false;
}

//LineEdit::~LineEdit()
//{
//    m_history->saveToFile();
//}

QAction *LineEdit::copyAction() const
{
    return copyAct;
}

QAction *LineEdit::pasteAction() const
{
    return pasteAct;
}

//void LineEdit::setOperator(const QString &op)
//{
//    m_operator = op;
//    m_history->addNumber(text());
//    m_history->addOperator(op);
//    repaint();
//}

//void LineEdit::resetOperator()
//{
//    m_operator = "";
//    m_history->result(text());
//    repaint();
//}

//// все, что должно отображаться, должно выводиться через эти функции
//void LineEdit::setNumber(Number n)
//{
//    if(n == displayed)
//        return;
//    setText(n.toString(m_numberMode).toUpper());
//    displayed = n;
//    emit numberChanged(n);
////    m_history->addNumber(text());
//}
///*
//void LineEdit::setNumber(const QString &n, int m)
//{
//    if(m != 0)
//        setNumberMode(m);
//    Number d = Number::toNumber(n, m_numberMode);
//    setNumber(d);
//}*/

//Number LineEdit::getNumber() const
//{
//    return displayed;
//}

///*
// * нужно для programming mode
// * 10 - decimal
// * 8  - octal
// * 16 - hexadecimal
// *
// * // todo
// * 2 - bin
// */
//void LineEdit::setNumberMode(int m)
//{
//    if(m == m_numberMode)
//        return;

//    if(m <= 0 || m > 16)
//        return;

//    m_numberMode = m;
//    emit numberModeChanged(m);
//    setNumber(displayed);
//}

//int LineEdit::numberMode() const
//{
//    return m_numberMode;
//}

//void LineEdit::setWait(bool b)
//{
//    m_waitOperand = b;
//}

//bool LineEdit::waitOperand() const
//{
//    return m_waitOperand;
//}

void LineEdit::pasteSlot()
{
    QClipboard *cl = qApp->clipboard();
    insertNumber(cl->text());
}

//QByteArray LineEdit::saveState() const
//{
//    QByteArray ba;
//    QDataStream stream (&ba, QIODevice::ReadWrite);

//    stream << displayed;
//    return ba;
//}

//void LineEdit::restoreState(const QByteArray &ba)
//{
//    Number num;
//    QDataStream stream (ba);
//    stream >> num;
//    setNumber(num);
//}

void LineEdit::contextMenuEvent(QContextMenuEvent *e)
{
    if(!contextMenu)
    {
        contextMenu = new QMenu(this);
        contextMenu->addAction(copyAct);
        contextMenu->addAction(pasteAct);
    }

    contextMenu->exec(e->globalPos());
}

void LineEdit::paintEvent(QPaintEvent *e)
{
    QLineEdit::paintEvent(e);

    QPainter p(this);

    // координаты получены экспериментально

    // ### TODO ###
    if(!m_operator.isEmpty())
    {
        p.setFont(QFont("Arial", 12));
        p.drawRect(5, height()-15, 11, 11);
        p.drawText(5, height()-15, 12, 12, Qt::AlignCenter, m_operator);
    }
}
