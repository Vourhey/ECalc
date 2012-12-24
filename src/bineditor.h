#ifndef BINEDITOR_H
#define BINEDITOR_H

#include <QWidget>
#include <QLabel>
#include "number.h"

class LabelForBinEditor;
class LineEdit;

class BinEditor : public QWidget
{
    Q_OBJECT
public:
    explicit BinEditor(LineEdit *le, QWidget *parent = 0);

public slots:
    void setNumber(Number n);
    
private slots:
    void labelClickSlot(int d, const QString &text);

private:
    Number m_number;
    QVector<LabelForBinEditor*> labels;
    LineEdit *lineEdit;
};

// класс нужен для удобства создания BinEditor
// содержит степень
class LabelForBinEditor : public QLabel
{
    Q_OBJECT
public:
    explicit LabelForBinEditor(int d, const QString &t, QWidget *parent = 0)
        : QLabel(parent)
    { setText(t); m_degree = d; }

    ~LabelForBinEditor() {}

    int degree() const { return m_degree; }

signals:
    void clicked(int d, const QString &t);

protected:
    void mousePressEvent(QMouseEvent *)
    {
        QString t = text();

        if(t == tr("0")) setText(tr("1"));
        else setText(tr("0"));

        emit clicked(m_degree, t);
    }

private:
    int m_degree;
};

#endif // BINEDITOR_H
