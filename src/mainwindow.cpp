#include <QtGui>
#include "mainwindow.h"
#include "lineedit.h"
#include "basickeyboard.h"
#include "numbersystemswitcher.h"
#include "bineditor.h"
#include "advancekeyboard.h"
#include "programmingkeyboard.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setWindowTitle(tr("About ECalc"));
    lb = new QLabel(tr("Calculator with programming mode.<br>"
                       "v0.3<br>"
                       "This release corresponds to the number e = 2.7<br>"
                       "Source is availible at "
                       "<a href=\"https://github.com/Vourhey/ECalc\">https://github.com/Vourhey/ECalc</a> <br>"
                       "Project created 2012-11-14 by Vadim Manaenko"));
    lb->setTextFormat(Qt::RichText);
    lb->setAlignment(Qt::AlignCenter);

    closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), SLOT(accept()));

    QHBoxLayout *hbox = new QHBoxLayout;
    QVBoxLayout *vbox = new QVBoxLayout;

    hbox->addStretch();
    hbox->addWidget(closeButton);
    vbox->addWidget(lb);
    vbox->addLayout(hbox);

    setLayout(vbox);
}

// ===========================================

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), aboutDialog(0), m_mode(0)
{
    QCoreApplication::setApplicationName(tr("ECalc"));
    QCoreApplication::setOrganizationName(tr("VourheyApps"));
    QCoreApplication::setOrganizationDomain(tr("https://github.com/Vourhey/ECalc"));

    m_init();
    initLayout();
    initActins();
    initMenu();

    restoreState();
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

    QMenu *modeMenu = mb->addMenu(tr("Mode"));
    modeMenu->addAction(basicAct);
//    viewMenu->addAction(advanceAct);
    modeMenu->addAction(programmingAct);

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

void MainWindow::closeEvent(QCloseEvent *)
{
    QSettings settings;

    settings.beginGroup(tr("mainWindow"));
    settings.setValue(tr("mode"), m_mode);
    settings.setValue(tr("number"), m_lineEdit->saveState());
    settings.setValue(tr("position"), pos());
    settings.endGroup();

    if(m_mode == 1)
        ;   // save advance settings
    else if(m_mode == 2)
    {
        settings.beginGroup(tr("programmingMode"));
        settings.setValue(tr("numberSystemSwitcher"), m_numberSystemSwitcher->saveState());
        settings.endGroup();
    }
}

void MainWindow::restoreState()
{
    QSettings settings;

    settings.beginGroup(tr("mainWindow"));
    int mode = settings.value(tr("mode"), 0).toInt();
    QPoint pos = settings.value(tr("position")).toPoint();
    QByteArray ba = settings.value(tr("number"), QByteArray("\0\0\0\0\0\0\0\0u")).toByteArray();
    settings.endGroup();

    changeMode(mode);
    move(pos);
    m_lineEdit->restoreState(ba);

    if(mode == 1)
        ;   // ### todo
    else if(mode == 2)
    {
        settings.beginGroup(tr("programmingMode"));
        QByteArray b = settings.value(tr("numberSystemSwitcher"), QByteArray("\0\0\0\n")).toByteArray();
        settings.endGroup();

        m_numberSystemSwitcher->restoreState(b);
    }
}

void MainWindow::changeMode(int mode)
{
    if(mode == -1)
    {
        QAction *act = qobject_cast<QAction*>(sender());
        if(act == basicAct)
            mode = 0;
        else if(act == advanceAct)
            mode = 1;
        else
            mode = 2;
    }

    if(m_mode == mode)
        return; // уже выбран этот режим

    m_mode = mode;

    // возвращаем к Basic
    if(m_numberSystemSwitcher)
    {
        mainLayout->removeWidget(m_numberSystemSwitcher);
        m_numberSystemSwitcher->hide();
    }
    if(m_binEditor)
    {
        mainLayout->removeWidget(m_binEditor);
        m_binEditor->hide();
    }
    if(m_programmingKeyboard)
    {
        horizontalLayout->removeWidget(m_programmingKeyboard);
        m_programmingKeyboard->hide();
    }
    if(m_advanceKeyboard)
    {
        horizontalLayout->removeWidget(m_advanceKeyboard);
        m_advanceKeyboard->hide();
    }

    switch(m_mode)
    {
    case 1:     // Advance
        // ### TODO ###
        break;
    case 2:     // Programming
        if(!m_numberSystemSwitcher)
            m_numberSystemSwitcher = new NumberSystemSwitcher(m_lineEdit);
        if(!m_binEditor)
            m_binEditor = new BinEditor(m_lineEdit);
        if(!m_programmingKeyboard)
            m_programmingKeyboard = new ProgrammingKeyboard(m_lineEdit);

        mainLayout->insertWidget(1, m_numberSystemSwitcher);
        mainLayout->insertWidget(2, m_binEditor);
        horizontalLayout->insertWidget(1, m_programmingKeyboard);

        m_numberSystemSwitcher->show();
        m_binEditor->show();
        m_programmingKeyboard->show();
        break;
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
        nact->setData(m_lineEdit->numberMode());
        m_memory.append(nact);
    }
    else
    {
        act->setText(linetext);
        act->setData(m_lineEdit->numberMode());
    }
}

void MainWindow::insertIntoLineEdit()
{
    QAction *act = qobject_cast<QAction*>(sender());
    m_lineEdit->setNumber(act->text(), act->data().toInt());
}

void MainWindow::about()
{
    if(!aboutDialog)
    {
        aboutDialog = new AboutDialog;
    }

    aboutDialog->exec();
}
