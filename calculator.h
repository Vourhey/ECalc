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
    void clearMemory();
    void readMemory();
    void storeInMemory();
    void sumMemory();

private:
    QLineEdit * lineEdit;

    double sumOfMemory;
    double leftOperand;
    
};

#endif // CALCULATOR_H
