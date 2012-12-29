#include <QtGui/QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QLocale>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF_8"));

    QApplication a(argc, argv);

#ifdef QT_NO_DEBUG
    // только в Release режиме
    QTranslator myTranslator;
    myTranslator.load("translations/ecalc_" + QLocale::system().name());
    a.installTranslator(&myTranslator);
#endif

    MainWindow w;
    w.show();
    
    return a.exec();
}
