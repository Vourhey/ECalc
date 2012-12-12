#ifndef NUMBERSYSTEMSWITCHER_H
#define NUMBERSYSTEMSWITCHER_H

#include <QWidget>

class QComboBox;
class QLabel;

class NumberSystemSwitcher : public QWidget
{
    Q_OBJECT
public:
    explicit NumberSystemSwitcher(QWidget *parent = 0);

public slots:
    void setNumber(quint64 n);

private slots:
    void updateFromAndTo(int i);
    
private:
    void updateLabel();

    QComboBox *comboBox;
    QLabel *label;

    quint64 m_number;
    qint8 from;
    qint8 to;
};

#endif // NUMBERSYSTEMSWITCHER_H
