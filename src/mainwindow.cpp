#include <QtGui>
#include "mainwindow.h"
#include "lineedit.h"
#include "basickeyboard.h"
#include "numbersystemswitcher.h"
#include "bineditor.h"
#include "trigonometryfuncs.h"
#include "advancekeyboard.h"
#include "programmingkeyboard.h"

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

    clearMemoryAct = new QAction(tr("Clear memory"), this);
    connect(clearMemoryAct, SIGNAL(triggered()), SLOT(clearMemory()));

    addToMemoryAct = new QAction(tr("New item"), this);
    connect(addToMemoryAct, SIGNAL(triggered()), SLOT(addToMemory()));
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

    QMenu *memoryMenu = mb->addMenu(tr("Memory"));

    QMenu *writeToMenu = memoryMenu->addMenu(tr("Write to"));
    connect(writeToMenu, SIGNAL(aboutToShow()), SLOT(aboutToShowWriteMenu()));
    QMenu *readFromMenu = memoryMenu->addMenu(tr("Read from"));
    connect(readFromMenu, SIGNAL(aboutToShow()), SLOT(aboutToShowReadMenu()));

    memoryMenu->addAction(clearMemoryAct);

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

    if(!m_numberSystemSwitcher)
        m_numberSystemSwitcher = new NumberSystemSwitcher(m_lineEdit);
    if(!m_binEditor)
        m_binEditor = new BinEditor(m_lineEdit);
    if(!m_programmingKeyboard)
        m_programmingKeyboard = new ProgrammingKeyboard(m_lineEdit);

    if(b)
    {
        mainLayout->insertWidget(1, m_numberSystemSwitcher);
        mainLayout->insertWidget(2, m_binEditor);
        horizontalLayout->insertWidget(1, m_programmingKeyboard);
        m_numberSystemSwitcher->show();
        m_binEditor->show();
        m_programmingKeyboard->show();
    }
    else
    {
        mainLayout->removeWidget(m_numberSystemSwitcher);
        mainLayout->removeWidget(m_binEditor);
        horizontalLayout->removeWidget(m_programmingKeyboard);
        m_numberSystemSwitcher->hide();
        m_binEditor->hide();
        m_programmingKeyboard->hide();
    }
}

void MainWindow::clearMemory()
{
    foreach(QAction *act, m_memory)
        delete act;
    m_memory.clear();
}

void MainWindow::aboutToShowWriteMenu()
{
    QMenu *m = qobject_cast<QMenu*>(sender());

    m->clear();

    foreach(QAction *act, m_memory)
    {
        act->disconnect();
        connect(act, SIGNAL(triggered()), SLOT(addToMemory()));
        m->addAction(act);
    }

    m->addSeparator();
    m->addAction(addToMemoryAct);
}

void MainWindow::aboutToShowReadMenu()
{
    QMenu *m = qobject_cast<QMenu*>(sender());

    m->clear();

    foreach(QAction *act, m_memory)
    {
        act->disconnect();
        connect(act, SIGNAL(triggered()), SLOT(insertIntoLineEdit()));
        m->addAction(act);
    }
}

void MainWindow::addToMemory()
{
    QAction *act = qobject_cast<QAction*>(sender());
    QString linetext = m_lineEdit->text();

    if(act == addToMemoryAct)
    {
        QAction *nact = new QAction(linetext, this);
        nact->setData(linetext.toDouble());
        m_memory.append(nact);
    }
    else
    {
        act->setText(linetext);
        act->setData(linetext.toDouble());
    }
}

void MainWindow::insertIntoLineEdit()
{
    QAction *act = qobject_cast<QAction*>(sender());
    m_lineEdit->setNumber(act->data().toDouble());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Calculator"),
                       tr("Calculator by Vourhey (v0.2)"));
}
