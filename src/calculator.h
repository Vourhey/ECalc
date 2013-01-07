#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "lineedit.h"

class BasicKeyboard;
class NumberSystemSwitcher;
class ProgrammingKeyboard;
class BinEditor;
class AdvanceKeyboard;

class QVBoxLayout;
class QHBoxLayout;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);

    LineEdit *lineEdit() const;

//    QByteArray saveState() const;
//    void restoreState(const QByteArray &ba);

public slots:
    void changeMode(int m = -1);

private:
    LineEdit *m_lineEdit;
    BasicKeyboard *m_basicKeyboard;
    ProgrammingKeyboard *m_programmingKeyboard;
    BinEditor *m_binEditor;
    NumberSystemSwitcher *m_numberSystemSwitcher;
    AdvanceKeyboard *m_advanceKeyboard;

    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;

    int m_mode; // текущий режим
};

#endif // CALCULATOR_H
