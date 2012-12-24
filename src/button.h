#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton
{
    Q_OBJECT
public:
    explicit Button(const QString &text, QWidget *parent = 0);
    
    QSize sizeHint() const;

    static Button *createButton(const QString &text, const QObject *obj,
                                const char *member,
                                const QKeySequence &key = QKeySequence(),
                                const QString &tooltip = QString());
};

#endif // BUTTON_H
