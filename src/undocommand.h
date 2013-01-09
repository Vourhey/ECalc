#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>
#include <QList>
#include "calcobject.h"

class UndoCommand : public QUndoCommand
{
public:
    UndoCommand();

    void undo();
    void redo();

private:
    QList<CalcObject*> postfix;
    QList<Number> numbers;

    static quint32 count;
};

#endif // UNDOCOMMAND_H
