#include <QtGui>
#include "mainwindow.h"
#include "calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    calc = new Calculator;

    initActins();
    initMenu();

    setCentralWidget(calc);
}

MainWindow::~MainWindow()
{    
}

void MainWindow::initActins()
{
    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    aboutAct = new QAction(tr("About"), this);
    aboutAct->setShortcut(QKeySequence::HelpContents);
    connect(aboutAct, SIGNAL(triggered()), SLOT(about()));

    aboutQtAct = new QAction(tr("About Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    basicAct = new QAction(tr("Basic"), this);
    basicAct->setData(1);
    connect(basicAct, SIGNAL(triggered()), SLOT(changeMode()));

    advanceAct = new QAction(tr("Advance"), this);
    advanceAct->setData(2);
    connect(advanceAct, SIGNAL(triggered()), SLOT(changeMode()));

    financicalAct = new QAction(tr("Financical"), this);
    financicalAct->setData(3);
    connect(financicalAct, SIGNAL(triggered()), SLOT(changeMode()));

    programmingAct = new QAction(tr("Programming"), this);
    programmingAct->setData(4);
    connect(programmingAct, SIGNAL(triggered()), SLOT(changeMode()));

    QActionGroup *ag = new QActionGroup(this);
    ag->addAction(basicAct);
    ag->addAction(advanceAct);
    ag->addAction(financicalAct);
    ag->addAction(programmingAct);
    basicAct->setChecked(true);
}

void MainWindow::initMenu()
{
    QMenuBar *mb = menuBar();

    QMenu *fileMenu = mb->addMenu(tr("File"));
    fileMenu->addAction(exitAct);

    QMenu *viewMenu = mb->addMenu(tr("View"));
    viewMenu->addAction(basicAct);
    viewMenu->addAction(advanceAct);
    viewMenu->addAction(financicalAct);
    viewMenu->addAction(programmingAct);

    QMenu *helpMenu = mb->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Calculator"),
                       tr("Calculator by Vourhey (v0.2)"));
}

void MainWindow::changeMode()
{
    QAction *act = qobject_cast<QAction*>(sender());
    int m = act->data().toInt();

    calc->setMode(m);
}
