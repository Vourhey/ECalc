#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "button.h"

class QGridLayout;
class LineEdit;
class BinEditor;
class NumberSystemSwitcher;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);
    
public slots:
    void setMode(int mode = 1); // Basic default
    
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
    void initDefault();
    Button *createButton(const QString &text, const char *member,
                         const QKeySequence &key = QKeySequence());
    void showMemory();

    // widgets
    LineEdit *lineEdit;

    Button *backspaceButton;
    Button *clearButton;
    Button *clearAllButton;
    Button *memoryReadButton;
    Button *memoryStoreButton;
    Button *memorySumButton;
    Button *percentButton;
    Button *numberButton[10];
    Button *pointButton;
    Button *plusMinusButton;
    Button *divideButton;
    Button *multiplicationButton;
    Button *minusButton;
    Button *plusButton;
    Button *sqrtButton;
    Button *powerButton;
    Button *minusOneDegreeButton;
    Button *resultButton;

    BinEditor *binEditor;
    NumberSystemSwitcher *numsysSwitcher;

    QGridLayout *mainLayout;

    // for calc
    qreal sumOfMemory[10];
    qreal sumSoFar;
    qreal factorSoFar;
    QString additiveStr;
    QString multipliStr;
    bool waitOperand;
};

#endif // CALCULATOR_H
