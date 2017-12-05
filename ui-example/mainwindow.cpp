#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectionbackground.h"

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
    ui->mAppStatus->setPixmap(errorStatus);

    QPixmap offlineStatus(mOfflineImagePath);
    ui->mTarget_1_Status->setPixmap(offlineStatus);
    ui->mTarget_2_Status->setPixmap(offlineStatus);
    ui->mTarget_3_Status->setPixmap(offlineStatus);


    mTarget_1_Index = 0;
    mTarget_2_Index = 0;
    mTarget_3_Index = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onProgressChanged(int event, int infor) {

    switch (event)
    {
    case EVNT_UD_APP_STATUS:
        if(infor == 1)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mAppStatus->setPixmap(errorStatus);
        }
        else if(infor == 2)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mAppStatus->setPixmap(errorStatus);
        }
        else
        {
            QPixmap errorStatus (mErrorImagePath);
            ui->mAppStatus->setPixmap(errorStatus);
        }
        break;

    case EVNT_UD_DEST_ADDR:
    {
        QByteArray array((const char*)&infor, 1);
        ui->mAddressDest->setText( "0x" + QString(array.toHex().toUpper()));
        break;
    }

    case EVNT_UD_START_ADDR:
    {
        QByteArray array((const char*)&infor, 1);
        ui->mAddressStart->setText( "0x" + QString(array.toHex().toUpper()));
        break;
    }

    case EVNT_UD_SERIAL_PORT:
    {
        QString comnumber = QString("%1").arg(infor, 0, 10, QChar('0'));
        ui->mAppComport->setText("COM" + comnumber);
        break;
    }

    case EVNT_UD_TARGET_1:
        break;

    case EVNT_UD_TARGET_2:
        break;

    case EVNT_UD_TARGET_3:
        break;

    default:
        break;
    }


}
