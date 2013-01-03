#include <QFile>
#include <QTextStream>
#include "history.h"

History::History(LineEdit *le, const QString &fileName)
{
    m_lineEdit = le;
    m_fileName = fileName;
}

void History::addNumber(const QString &n)
{
    currentLine.append(n);
}

void History::addOperator(const QString &op)
{
    currentLine.append(op);
}

void History::result(const QString &n)
{
    currentLine.append("=").append(n);
    m_history.append(currentLine);
    resetCurrentLine();
}

void History::resetCurrentLine()
{
    currentLine.clear();
}

void History::saveToFile()
{
    QFile out(m_fileName);
    out.open(QIODevice::WriteOnly);

    QTextStream stream(&out);

    foreach(QString str, m_history)
    {
        stream << str << '\n';
    }

    stream.flush();
}
