#include "button.h"

Button::Button(const QString &text, QWidget *parent) :
    QToolButton(parent)
{
    setStyleSheet("text-align: left;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);
}

QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.height(), size.width());
    return size;
}

// облегчает жизнь. Одной функцией настраиваются все жизнено важные параметры
Button *Button::createButton(const QString &text, const QObject *obj,
                             const char *member, const QKeySequence &key,
                             const QString &tooltip)
{
    Button *btn = new Button(text);
    connect(btn, SIGNAL(clicked()), obj, member);

    if(!key.isEmpty()) btn->setShortcut(key);
    if(!tooltip.isEmpty()) btn->setToolTip(tooltip);
    return btn;
}

void Button::setCalcObject(CalcObject *co)
{
    m_co = co;
}

CalcObject *Button::calcObject() const
{
    return m_co;
}
