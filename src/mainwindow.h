#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class Calculator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();
    void changeMode();

private:
    void initMenu();
    void initActins();

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *basicAct;
    QAction *advanceAct;
    QAction *financicalAct;
    QAction *programmingAct;

    Calculator *calc;
};

#endif // MAINWINDOW_H
