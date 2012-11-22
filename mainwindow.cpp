#include <QtGui>
#include "mainwindow.h"
#include "calculator.h"
#include "bineditor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    binEditor = 0;

    initActins();
    initMenu();

    setCentralWidget(new Calculator);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::initActins()
{
    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));

    showBinEditorAct = new QAction(tr("Show Bin Editor"), this);
    connect(showBinEditorAct, SIGNAL(triggered()), SLOT(showBinEditor()));
}

void MainWindow::initMenu()
{
    QMenuBar *mb = menuBar();

    QMenu *fileMenu = mb->addMenu(tr("File"));
    fileMenu->addAction(exitAct);

    QMenu *viewMenu = mb->addMenu(tr("View"));
    viewMenu->addAction(showBinEditorAct);
}

void MainWindow::showBinEditor()
{
    if(!binEditor)
        binEditor = new BinEditor;

    binEditor->show();
}
