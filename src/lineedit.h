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
    void setNumber(const QString& n);
    Number getNumber() const;

    void setWait(bool b);
    bool waitOperand() const;

signals:
    void numberChanged(Number n);

public slots:
    void setPoint();

protected:
    void paintEvent(QPaintEvent *);

private:
    QString m_operator;
    Number displayed;
    bool m_waitOperand;
};

#endif // LINEEDIT_H
