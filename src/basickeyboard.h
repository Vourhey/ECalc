#ifndef BASICKEYBOARD_H
#define BASICKEYBOARD_H

#include <QWidget>
#include "button.h"
#include "lineedit.h"

class QGridLayout;

class BasicKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit BasicKeyboard(LineEdit *le, QWidget *parent = 0);

private slots:
    void backspaceSlot();
    void clearSlot();
    void clearAllSlot();
    void digitButtonSlot();
    void twoOperandSlot(); // для + - * /
    void unaryOperationSlot(); // для унарных операций
    void resultSlot();
    void enableDigit(int = 10);

private:
    void initDefault();

    // widgets
    LineEdit *lineEdit;

    Button *backspaceButton;
    Button *clearButton;
    Button *clearAllButton;
    Button *percentButton;
    Button *numberButton[10];
    Button *pointButton;
    Button *divideButton;
    Button *multiplicationButton;
    Button *minusButton;
    Button *plusButton;
    Button *sqrtButton;
    Button *powerButton;
    Button *minusOneDegreeButton;
    Button *resultButton;

    QGridLayout *mainLayout;

    // for calc
    Number sumSoFar;
    Number factorSoFar;
    QString additiveStr;
    QString multipliStr;
};

#endif // BASICKEYBOARD_H
