#ifndef PROGRAMMINGKEYBOARDS_H
#define PROGRAMMINGKEYBOARDS_H

#include <QWidget>

class Button;
class LineEdit;

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

    LineEdit *lineEdit;
};

#endif // PROGRAMMINGKEYBOARDS_H
