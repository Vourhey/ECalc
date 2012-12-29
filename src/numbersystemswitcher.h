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

    QByteArray saveState() const;
    void restoreState(const QByteArray &ba);

private slots:
    void setNumber(Number n);
    void updateFromAndTo(int i);
    void changeIndex(int n);
    
private:
    void updateLabel();
    void setFromTo(int n);

    QComboBox *comboBox;
    QLabel *label;
    LineEdit *lineEdit;

    Number m_number;
    qint8 from;
    qint8 to;
};

#endif // NUMBERSYSTEMSWITCHER_H
