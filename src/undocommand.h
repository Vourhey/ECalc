#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>
#include <QStack>
#include "calcobject.h"

class LineEdit;

// ленивый вариант
class UndoCommand : public QUndoCommand
{
public:
    UndoCommand(LineEdit *le);

    void undo();
    void redo();

    void setUndoNumbers(const QStack<Number> &n);
    void setUndoPostfix(const QStack<CalcObject*> &p);

    void setRedoNumbers(const QStack<Number> &n);
    void setRedoPostfix(const QStack<CalcObject*> &p);

private:
    QStack<Number> u_numbers;
    QStack<CalcObject*> u_postfix;

    QStack<Number> r_numbers;
    QStack<CalcObject*> r_postix;

    LineEdit *m_lineEdit;
    static quint32 count;
};

#endif // UNDOCOMMAND_H
