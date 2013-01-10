#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include <QStack>
#include "number.h"
#include "calcobject.h"

class QUndoStack;
class UndoCommand;

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);

    QAction *pasteAction() const;
    QAction *copyAction() const;

    void addChar(QChar c);    
    void addOperator(CalcObject *co);
    void insertNumber(Number n);

    Number getNumber() const;
    int numberMode() const;

    void setUndoStack(QUndoStack *undoStack);
    // далеко не самое удачное решение проблемы, но пусть пока так...
    void setStacks(const QStack<Number> &n, const QStack<CalcObject*> &p);

public slots:
    void calculate();   // =
    void clearSlot();
    void clearAll();
    void addPoint();
    void backspace();
    void setNumberMode(int m = 10);

//    ~LineEdit();
//    void setOperator(const QString &op);
//    void resetOperator();
//    void setNumber(Number n);
//    QByteArray saveState() const;
//    void restoreState(const QByteArray &ba);

signals:
    void numberChanged(Number n);
    void numberModeChanged(int base);

private slots:
    void pasteSlot();

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void paintEvent(QPaintEvent *);

private:
//    void p_calc(CalcObject *co);
    void setMyNumber(const QString &t);
    Number binaryOperation(CalcObject *co);
    UndoCommand *createUndo();
    void pushUndo(UndoCommand *c);

    QString m_operator;
    Number displayed;
    QStack<Number> m_numbers;
    QStack<CalcObject*> postfix;
    bool m_waitOperand;
    int m_numberMode;
    int countBrace; // счетчик скобочек

    QMenu *contextMenu;
    QAction *copyAct;
    QAction *pasteAct;

    QUndoStack *m_undoStack;
//    History *m_history;
};

#endif // LINEEDIT_H
