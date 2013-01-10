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
    void digitButtonSlot();
    void operationSlot();
    void enableDigit(int b);

private:
    void initDefault();

    LineEdit *m_lineEdit;

    Button *backspaceButton;
    Button *clearButton;
    Button *clearAllButton;
    Button *minusUnaryButton;
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
    Button *leftBraceButton;
    Button *rightBraceButton;
};

#endif // BASICKEYBOARD_H
