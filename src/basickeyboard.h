#ifndef BASICKEYBOARD_H
#define BASICKEYBOARD_H

#include <QWidget>
#include "button.h"
#include "lineedit.h"

// клавиатуры занимаются только настройкой и отображением кнопочек
class BasicKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit BasicKeyboard(LineEdit *le, QWidget *parent = 0);


private slots:
    void backspaceSlot();
    void digitButtonSlot();
    void pointSlot();
    void operationSlot();
//    void twoOperandSlot(); // для + - * /
//    void unaryOperationSlot(); // для унарных операций
//    void resultSlot();
//    void enableDigit(int = 10);

private:
    void initDefault();

    LineEdit *m_lineEdit;

    Button *backspaceButton;
    Button *clearButton;
    Button *clearAllButton;
//    Button *percentButton;
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
};

#endif // BASICKEYBOARD_H
