#ifndef HISTORY_H
#define HISTORY_H

#include "lineedit.h"
#include <QStringList>

class History
{
public:
    History(LineEdit *le, const QString &fileName);

    void addNumber(const QString &n);
    void addOperator(const QString &op);
    void result(const QString &n);
    void resetCurrentLine();

    void saveToFile();

private:
    LineEdit *m_lineEdit;
    QStringList m_history;
    QString currentLine;
    QString m_fileName;
};

#endif // HISTORY_H
