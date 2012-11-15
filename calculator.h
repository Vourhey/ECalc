#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "button.h"

class QLineEdit;

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
    void clearMemory();
    void readMemory();
    void storeInMemory();
    void sumMemory();

private:
    Button *createButton(const QString &text, const char *member,
                         const QKeySequence &key = QKeySequence());

    QLineEdit * lineEdit;

    double sumOfMemory;
    double sumSoFar;
    double factorSoFar;
    QString additiveStr;
    QString multipliStr;
    bool waitOperand;
};

#endif // CALCULATOR_H
