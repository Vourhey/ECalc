#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEdit(QWidget *parent = 0);

    void setMemory(bool b);
    void setOperator(const QString &op);
    void resetOperator();

    void setNumber(qreal n);
    void setNumber(const QString& n);
    qreal getNumber() const;

    void setWait(bool b);
    bool waitOperand() const;

signals:
    void numberChanged(qreal n);

public slots:
    void setPoint();

protected:
    void paintEvent(QPaintEvent *);

private:
    bool memory;
    QString m_operator;
    qreal displayed;
    bool m_waitOperand;
};

#endif // LINEEDIT_H
