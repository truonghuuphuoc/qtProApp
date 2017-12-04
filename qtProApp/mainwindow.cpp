#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette pal = window()->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    window()->setPalette(pal);

    QString currentPath = QCoreApplication::applicationDirPath();
    mErrorImagePath     = currentPath + "/system/image/red.png";
    mOfflineImagePath   = currentPath + "/system/image/yellow.png";
    mOnlineImagePath    = currentPath + "/system/image/green.png";

    QPixmap errorStatus (mErrorImagePath);
    ui->label->setPixmap(errorStatus);

    QPixmap offlineStatus(mOfflineImagePath);
    ui->label_3->setPixmap(offlineStatus);
    ui->label_9->setPixmap(offlineStatus);
    ui->label_14->setPixmap(offlineStatus);
}

MainWindow::~MainWindow()
{
    delete ui;
}
