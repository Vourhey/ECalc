#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>
#include "number.h"

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);

    void setOperator(const QString &op);
    void resetOperator();

    void setNumber(Number n);
    void setNumber(const QString& n, int m = 0);
    Number getNumber() const;

    int numberMode() const;

    void setWait(bool b);
    bool waitOperand() const;

    void emitCalculateAll();

signals:
    void numberChanged(Number n);
    void numberModeChanged(int base);
    void calculateAll();    // emited when result button press

public slots:
    void setPoint();
    void setNumberMode(int m = 10);

protected:
    void paintEvent(QPaintEvent *);

private:
    QString m_operator;
    Number displayed;
    bool m_waitOperand;
    int m_numberMode;
};

#endif // LINEEDIT_H
