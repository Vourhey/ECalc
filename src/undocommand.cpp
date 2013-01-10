#include "undocommand.h"
#include "lineedit.h"

quint32 UndoCommand::count = 0;

UndoCommand::UndoCommand(LineEdit *le)
    : m_lineEdit(le)
{
    ++count;
    setText(QObject::tr("step %1").arg(count));
}

void UndoCommand::setUndoNumbers(const QStack<Number> &n)
{
    u_numbers = n;
}

void UndoCommand::setUndoPostfix(const QStack<CalcObject *> &p)
{
    u_postfix = p;
}

void UndoCommand::setRedoNumbers(const QStack<Number> &n)
{
    r_numbers = n;
}

void UndoCommand::setRedoPostfix(const QStack<CalcObject *> &p)
{
    r_postix = p;
}

void UndoCommand::undo()
{
    m_lineEdit->setStacks(u_numbers, u_postfix);
}

void UndoCommand::redo()
{
    m_lineEdit->setStacks(r_numbers, r_postix);
}
