#include <QtGui>
#include "mainwindow.h"
#include "lineedit.h"
#include "basickeyboard.h"
#include "numbersystemswitcher.h"
#include "bineditor.h"
#include "trigonometryfuncs.h"
#include "additionalprogrammingfuncs.h"
#include "advancekeyboard.h"
#include "programmingkeyboards.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    m_init();
    initLayout();
    initActins();
    initMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::m_init()
{
    m_lineEdit = new LineEdit;
    m_basicKeyboard = new BasicKeyboard(m_lineEdit);

    m_advanceKeyboard = 0;
    m_programmingKeyboard = 0;
    m_additionalFuncs = 0;
    m_trigonometryFuncs = 0;
    m_binEditor = 0;
    m_numberSystemSwitcher = 0;
}

QMenuBar *MainWindow::menuBar()
{
    return qobject_cast<QMenuBar*>(mainLayout->menuBar());
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
    connect(basicAct, SIGNAL(triggered()), SLOT(changeMode()));

    advanceAct = new QAction(tr("Advance"), this);
    connect(advanceAct, SIGNAL(triggered()), SLOT(changeMode()));

    programmingAct = new QAction(tr("Programming"), this);
    connect(programmingAct, SIGNAL(triggered()), SLOT(changeMode()));

    QActionGroup *ag = new QActionGroup(this);
    ag->addAction(basicAct);
    ag->addAction(advanceAct);
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
//    viewMenu->addAction(advanceAct);
    viewMenu->addAction(programmingAct);

    QMenu *helpMenu = mb->addMenu(tr("Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::initLayout()
{
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(0);
    mainLayout->setMenuBar(new QMenuBar);

    mainLayout->addWidget(m_lineEdit);

    horizontalLayout = new QHBoxLayout;
    horizontalLayout->setSpacing(0);

    horizontalLayout->addWidget(m_basicKeyboard);

    mainLayout->addLayout(horizontalLayout);

    setLayout(mainLayout);
}

// ### TODO ###
void MainWindow::changeMode()
{
    QAction *act = qobject_cast<QAction*>(sender());

    bool b;
    if(act == basicAct) b = false;
    else b = true;

/*    if(!m_numberSystemSwitcher)
        m_numberSystemSwitcher = new NumberSystemSwitcher; */
    if(!m_binEditor)
        m_binEditor = new BinEditor(m_lineEdit);

    if(b)
    {
 /*       mainLayout->insertWidget(1, m_numberSystemSwitcher);
        mainLayout->insertWidget(2, m_binEditor);
        m_numberSystemSwitcher->show(); */
        mainLayout->insertWidget(1, m_binEditor);
        m_binEditor->show();
    }
    else
    {
 //       mainLayout->removeWidget(m_numberSystemSwitcher);
        mainLayout->removeWidget(m_binEditor);
 //       m_numberSystemSwitcher->hide();
        m_binEditor->hide();
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Calculator"),
                       tr("Calculator by Vourhey (v0.2)"));
}
