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
    size.rheight() += 15;
    size.rwidth() = qMax(size.height(), size.width());
    return size;
}
