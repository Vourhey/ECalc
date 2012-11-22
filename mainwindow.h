#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QAction;
class BinEditor;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void showBinEditor();

private:
    void initMenu();
    void initActins();

    QAction *exitAct;
    QAction *showBinEditorAct;

    BinEditor *binEditor;
};

#endif // MAINWINDOW_H
