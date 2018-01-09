#include "mainwindow.h"

#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

#include "connectionbackground.h"
#include "phnsysconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.showMaximized();

    ConnectionBackground *workerThread = new ConnectionBackground;

    phnSysConfig::phnSysConfig_ReadConfig(QCoreApplication::applicationDirPath());

    workerThread->setAddress(phnSysConfig::mRecvAddess, phnSysConfig::mTransAddress);

    // Connect our signal and slot
    QObject::connect(workerThread, SIGNAL(progressChanged(int, int)),&w,
                         SLOT(onProgressChanged(int, int)));

    // Setup callback for cleanup when it finishes
    QObject::connect(workerThread, SIGNAL(finished()),
           workerThread, SLOT(deleteLater()));

    // Run, Forest, run!
    workerThread->start(); // This invokes WorkerThread::run in a new thread

    return a.exec();
}
