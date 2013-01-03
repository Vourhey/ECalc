#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include <QStack>
#include "number.h"
#include "calcobject.h"

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);

    void addChar(QChar c);
    void addOperator(CalcObject *co);
    void insertNumber(Number n);

public slots:
    void calculate();   // =
    void clearSlot();
    void clearAll();

//    ~LineEdit();

//    QAction *pasteAction() const;
//    QAction *copyAction() const;

//    void setOperator(const QString &op);
//    void resetOperator();

//    void setNumber(Number n);
////   void setNumber(const QString& n, int m = 0);
//    Number getNumber() const;

//    int numberMode() const;

//    void setWait(bool b);
//    bool waitOperand() const;

//    void emitCalculateAll();

//    QByteArray saveState() const;
//    void restoreState(const QByteArray &ba);

//signals:
//    void numberChanged(Number n);
//    void numberModeChanged(int base);
//    void calculateAll();    // emited when result button press

//public slots:
//    void setPoint();
//    void setNumberMode(int m = 10);

//private slots:
//    void pasteSlot();

//protected:
//    void contextMenuEvent(QContextMenuEvent *);
//    void paintEvent(QPaintEvent *);

private:
//    QString m_operator;
    Number displayed;
    QStack<Number> m_numbers;
    QStack<CalcObject*> postfix;
    bool m_waitOperand;
//    int m_numberMode;

//    QMenu *contextMenu;
//    QAction *copyAct;
//    QAction *pasteAct;

//    History *m_history;
};

#endif // LINEEDIT_H
