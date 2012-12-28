#ifndef PROGRAMMINGKEYBOARDS_H
#define PROGRAMMINGKEYBOARDS_H

#include <QDialog>
#include "number.h"

class Button;
class LineEdit;
class InsertCharDialog;
class QLineEdit;
class QPushButton;

class ProgrammingKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit ProgrammingKeyboard(LineEdit *le, QWidget *parent = 0);

private slots:
    void digitSlot();
    void twoOperandSlot();
    void notSlot();
    void logSlot();
    void intFracSlot();
    void factorialSlot();
    void absSlot();
    void insertCodeOfChar();
    void onesSlot();
    void twosSlot();
    void shlSlot();
    void shrSlot();
    void enableAF(int b);
    void resultSlot();

private:
    Button *afButton[6];
    Button *andButton;
    Button *orButton;
    Button *xorButton;
    Button *notButton;
    Button *logButton;
    Button *lnButton;
    Button *intButton;
    Button *fracButton;
    Button *factorialButton;
    Button *absButton;
    Button *charButton;
    Button *modButton;
    Button *onesButton;
    Button *twosButton;
    Button *shlButton; // <<
    Button *shrButton; // >>

    QString operatorStr;
    Number  sumSoFar;

    LineEdit *lineEdit;
    InsertCharDialog *dialog;
};

// диалог вставки кода символа
class InsertCharDialog : public QDialog
{
    Q_OBJECT
public:
    InsertCharDialog(QWidget *parent = 0);

    Number getCharCode();

private slots:
    void enableButton(const QString &str);

private:
    QLineEdit   *le;
    QPushButton *cancelBtn;
    QPushButton *insertBtn;
};

#endif // PROGRAMMINGKEYBOARDS_H
