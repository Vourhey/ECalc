#include "button.h"

Button::Button(const QString &text, const QKeySequence &key, QWidget *parent) :
    QToolButton(parent)
{
    setStyleSheet("text-align: left;");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setText(text);

    if(!key.isEmpty())
        setShortcut(key);
}

QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;
    size.rwidth() = qMax(size.height(), size.width());
    return size;
}
