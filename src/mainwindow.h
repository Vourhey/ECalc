#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

class QLabel;
class QAction;

class AboutDialog;
class Calculator;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
//  void closeEvent(QCloseEvent *);

private slots:
    void about();
    void clearMemory();
    void aboutToShowWriteMenu();
    void aboutToShowReadMenu();
    void addToMemory();
    void insertIntoLineEdit();

private:
    void initActins();
    void initMenu();
//    void restoreState();
//    void insertConst();

    Calculator *m_calc;

    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *basicAct;
    QAction *advanceAct;
    QAction *programmingAct;
    QAction *clearMemoryAct;
    QAction *addToMemoryAct;

    AboutDialog *aboutDialog;
    QList<QAction*> m_memory;
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
