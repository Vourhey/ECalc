#include "mainwindow.h"
#include "calculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setCentralWidget(new Calculator);
}

MainWindow::~MainWindow()
{
    
}
