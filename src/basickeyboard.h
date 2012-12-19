#ifndef BASICKEYBOARD_H
#define BASICKEYBOARD_H

#include <QWidget>
#include "button.h"

class QGridLayout;
class LineEdit;

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
    void pointButtonSlot();
    void twoOperandSlot(); // для + - * /
    void unaryOperationSlot(); // для унарных операций
    void resultSlot();

private:
    void initDefault();
    Button *createButton(const QString &text, const char *member,
                         const QKeySequence &key = QKeySequence());

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
    qreal sumOfMemory[10];
    qreal sumSoFar;
    qreal factorSoFar;
    QString additiveStr;
    QString multipliStr;
    bool waitOperand;
};

#endif // BASICKEYBOARD_H
