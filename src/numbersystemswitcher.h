#ifndef NUMBERSYSTEMSWITCHER_H
#define NUMBERSYSTEMSWITCHER_H

#include <QWidget>
#include "lineedit.h"

class QComboBox;
class QLabel;

class NumberSystemSwitcher : public QWidget
{
    Q_OBJECT
public:
    explicit NumberSystemSwitcher(LineEdit *le, QWidget *parent = 0);

private slots:
    void setNumber(Number n);
    void updateFromAndTo(int i);
    
private:
    void updateLabel();

    QComboBox *comboBox;
    QLabel *label;
    LineEdit *lineEdit;

    Number m_number;
    qint8 from;
    qint8 to;
};

#endif // NUMBERSYSTEMSWITCHER_H
