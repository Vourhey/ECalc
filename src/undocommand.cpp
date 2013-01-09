#include "undocommand.h"

quint32 UndoCommand::count = 0;

UndoCommand::UndoCommand()
{
    ++count;
    setText(QObject::tr("step %1").arg(count));
}

void UndoCommand::undo()
{

}

void UndoCommand::redo()
{

}
