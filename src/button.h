#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>
#include "calcobject.h"

class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(const QString &text, QWidget *parent = 0);
    
    QSize sizeHint() const;
    void setCalcObject(CalcObject *co);
    CalcObject *calcObject() const;

    static Button *createButton(const QString &text, const QObject *obj,
                                const char *member,
                                const QKeySequence &key = QKeySequence(),
                                const QString &tooltip = QString());

private:
    CalcObject *m_co;
};

#endif // BUTTON_H
