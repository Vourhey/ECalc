#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include "lineedit.h"

class BasicKeyboard;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    explicit Calculator(QWidget *parent = 0);

    LineEdit *lineEdit() const;

public slots:
    void changeMode();

private:
    LineEdit *m_lineEdit;
    BasicKeyboard *m_basicKeyboard;
};

#endif // CALCULATOR_H
