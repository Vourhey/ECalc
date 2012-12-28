#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QList>

class QAction;
class QMenuBar;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;

class LineEdit;
class BasicKeyboard;
class AdvanceKeyboard;
class ProgrammingKeyboard;
class BinEditor;
class NumberSystemSwitcher;
class AboutDialog;

// It's not child of QMainWindow!
class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();
    void changeMode();
    void clearMemory();
    void aboutToShowWriteMenu();
    void aboutToShowReadMenu();
    void addToMemory();
    void insertIntoLineEdit();

private:
    void m_init();
    void initMenu();
    void initActins();
    void initLayout();
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
