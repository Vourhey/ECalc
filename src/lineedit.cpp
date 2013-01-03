#include <QtGui>
#include "lineedit.h"
#include "history.h"

// модифицированное поле ввода
LineEdit::LineEdit(QWidget *parent) :
    QLineEdit(parent) //, contextMenu(0), copyAct(0), pasteAct(0)
{
    m_waitOperand = false;
//    m_history = new History(this, tr("log"));

//    copyAct = new QAction(tr("Copy"), this);
//    copyAct->setShortcut(QKeySequence::Copy);
//    connect(copyAct, SIGNAL(triggered()), SLOT(copy()));

//    pasteAct = new QAction(tr("Paste"), this);
//    pasteAct->setShortcut(QKeySequence::Paste);
//    connect(pasteAct, SIGNAL(triggered()), SLOT(pasteSlot()));

    setText(tr("0"));
    setAlignment(Qt::AlignRight);
    //setMaxLength(15);
    setReadOnly(true);

    QFont f = font();
    f.setPointSize(f.pointSize() + 8);
    setFont(f);

    addChar('0');

//    setNumberMode();
}

void LineEdit::addChar(QChar c)
{
    if(m_waitOperand)
    {
        setText(tr(""));
        m_waitOperand = false;
    }

    QString t = text();
    if(t == tr("0")) t = "";
    setText(t + c);
}

void LineEdit::addOperator(CalcObject *co)
{
    m_numbers.push(Number(text()));
    postfix.push(co);
    m_waitOperand = true;
}

void LineEdit::calculate()
{
    m_numbers.push(Number(text()));
    if(postfix.isEmpty())
       return;
    CalcObject *co = postfix.pop();
    Number n;

    if(co->isUnary())
        n = co->calc(m_numbers.pop());
    else
    {
        Number n2 = m_numbers.pop();
        Number n1 = m_numbers.pop();
        n = co->calc(n1, n2);
    }

    clearAll();
    m_numbers.push(n);
    setText(n.toString());
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
    m_waitOperand = false;
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

//QAction *LineEdit::copyAction() const
//{
//    return copyAct;
//}

//QAction *LineEdit::pasteAction() const
//{
//    return pasteAct;
//}

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

//void LineEdit::setPoint()
//{
//    if(!text().contains('.'))
//        setText(text().append('.'));
//}

//void LineEdit::emitCalculateAll()
//{
//    emit calculateAll();
//}

//void LineEdit::pasteSlot()
//{
//    QClipboard *cl = qApp->clipboard();
//    setNumber(cl->text());
//}

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

//void LineEdit::contextMenuEvent(QContextMenuEvent *e)
//{
//    if(!contextMenu)
//    {
//        contextMenu = new QMenu(this);
//        contextMenu->addAction(copyAct);
//        contextMenu->addAction(pasteAct);
//    }

//    contextMenu->exec(e->globalPos());
//}

//void LineEdit::paintEvent(QPaintEvent *e)
//{
//    QLineEdit::paintEvent(e);

//    QPainter p(this);

//    // координаты получены экспериментально

//    // ### TODO ###
//    if(!m_operator.isEmpty())
//    {
//        p.setFont(QFont("Arial", 12));
//        p.drawRect(5, height()-15, 11, 11);
//        p.drawText(5, height()-15, 12, 12, Qt::AlignCenter, m_operator);
//    }
//}
