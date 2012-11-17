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

protected:
    void paintEvent(QPaintEvent *);

private:
    bool memory;
    QString m_operator;
};

#endif // LINEEDIT_H
