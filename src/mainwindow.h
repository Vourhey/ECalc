#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QList>

class QAction;
class QMenuBar;
class QVBoxLayout;
class QHBoxLayout;

class LineEdit;
class BasicKeyboard;
class AdvanceKeyboard;
class ProgrammingKeyboards;
class AdditionalProgrammingFuncs;
class TrigonometryFuncs;
class BinEditor;
class NumberSystemSwitcher;

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
    ProgrammingKeyboards *m_programmingKeyboard;
    AdditionalProgrammingFuncs *m_additionalFuncs;
    TrigonometryFuncs *m_trigonometryFuncs;
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
};

#endif // MAINWINDOW_H
