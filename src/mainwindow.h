#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class QLabel;

/*
class QAction;
class QMenuBar;
class QVBoxLayout;
class QHBoxLayout;

class LineEdit;
class BasicKeyboard;
class AdvanceKeyboard;
class ProgrammingKeyboard;
class BinEditor;
class NumberSystemSwitcher;
class AboutDialog;
*/

class Calculator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Calculator *m_calc;

    /*
protected:
    void closeEvent(QCloseEvent *);

private slots:
    void about();
    void changeMode(int = -1);
    void clearMemory();
    void aboutToShowWriteMenu();
    void aboutToShowReadMenu();
    void addToMemory();
    void insertIntoLineEdit();
    void insertConst();

private:
    void m_init();
    void initMenu();
    void initActins();
    void initLayout();
    void restoreState();
    QMenuBar *menuBar();

    LineEdit *m_lineEdit;
    BasicKeyboard *m_basicKeyboard;
    AdvanceKeyboard *m_advanceKeyboard;
    ProgrammingKeyboard *m_programmingKeyboard;
    BinEditor *m_binEditor;
    NumberSystemSwitcher *m_numberSystemSwitcher;

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *basicAct;
    QAction *advanceAct;
    QAction *programmingAct;
    QAction *clearMemoryAct;
    QAction *addToMemoryAct;

    QVBoxLayout *mainLayout;
    QHBoxLayout *horizontalLayout;

    QList<QAction*> m_memory;
    AboutDialog *aboutDialog;

    / * 0 - Basic
     * 1 - Advance
     * 2 - Programming
     * /
    int m_mode; */
};

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    AboutDialog(QWidget *parent = 0);

private:
    QLabel *lb;
    QPushButton *closeButton;
};

#endif // MAINWINDOW_H
