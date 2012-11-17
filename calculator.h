#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "button.h"

class LineEdit;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);
    
signals:
    
private slots:
    void backspaceSlot();
    void clearSlot();
    void clearAllSlot();
    void digitButtonSlot();
    void pointButtonSlot();
    void twoOperandSlot(); // для + - * /
    void unaryOperationSlot(); // для унарных операций
    void resultSlot();
    void readMemory();
    void storeInMemory();
    void sumMemory();
    void minusMemory();

    void memoryMenuShow();

private:
    Button *createButton(const QString &text, const char *member,
                         const QKeySequence &key = QKeySequence());
    void showMemory();

    LineEdit * lineEdit;

    qreal sumOfMemory[10];
    qreal sumSoFar;
    qreal factorSoFar;
    QString additiveStr;
    QString multipliStr;
    bool waitOperand;
};

#endif // CALCULATOR_H
