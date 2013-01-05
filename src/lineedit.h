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

    QAction *pasteAction() const;
    QAction *copyAction() const;

    void addChar(QChar c);    
    void addOperator(CalcObject *co);
    void insertNumber(Number n);

public slots:
    void calculate();   // =
    void clearSlot();
    void clearAll();
    void addPoint();

//    ~LineEdit();

//    void setOperator(const QString &op);
//    void resetOperator();

//    void setNumber(Number n);
////   void setNumber(const QString& n, int m = 0);
//    Number getNumber() const;

//    int numberMode() const;

//    QByteArray saveState() const;
//    void restoreState(const QByteArray &ba);

//signals:
//    void numberChanged(Number n);
//    void numberModeChanged(int base);

//public slots:
//    void setNumberMode(int m = 10);

private slots:
    void pasteSlot();

protected:
    void contextMenuEvent(QContextMenuEvent *);
    void paintEvent(QPaintEvent *);

private:
    void p_calc(CalcObject *co);
    Number oneOperation(CalcObject *co);

    QString m_operator;
    Number displayed;
    QStack<Number> m_numbers;
    QStack<CalcObject*> postfix;
    bool m_waitOperand;
    bool isDisplayed;   // если отображаемое число хранится на вершине стека
//    int m_numberMode;

    QMenu *contextMenu;
    QAction *copyAct;
    QAction *pasteAct;

//    History *m_history;
};

#endif // LINEEDIT_H
