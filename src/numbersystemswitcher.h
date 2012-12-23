#ifndef NUMBERSYSTEMSWITCHER_H
#define NUMBERSYSTEMSWITCHER_H

#include <QWidget>

class QComboBox;
class QLabel;
class LineEdit;

class NumberSystemSwitcher : public QWidget
{
    Q_OBJECT
public:
    explicit NumberSystemSwitcher(LineEdit *le, QWidget *parent = 0);

private slots:
    void setNumber(qreal n);
    void updateFromAndTo(int i);
    
private:
    void updateLabel();

    QComboBox *comboBox;
    QLabel *label;
    LineEdit *lineEdit;

    quint64 m_number;
    qint8 from;
    qint8 to;
};

#endif // NUMBERSYSTEMSWITCHER_H
