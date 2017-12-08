#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectionbackground.h"
#include "phnmessage.h"

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

    memset(mTarget_1_Value, 0x00, sizeof(mTarget_1_Value));
    memset(mTarget_2_Value, 0x00, sizeof(mTarget_2_Value));
    memset(mTarget_3_Value, 0x00, sizeof(mTarget_3_Value));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onProgressChanged(int event, int infor) {

    switch (event)
    {
    case EVNT_UD_APP_STATUS:
        if(infor == APP_STATUS_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mAppStatus->setPixmap(errorStatus);
        }
        else if(infor == APP_STATUS_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mAppStatus->setPixmap(errorStatus);
        }
        else
        {
            QPixmap errorStatus (mErrorImagePath);
            ui->mAppStatus->setPixmap(errorStatus);
            ui->mAppComport->setText("");
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
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mTarget_1_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mTarget_1_Status->setPixmap(errorStatus);
        }
        else
        {
            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mTarget_1_Value[mTarget_1_Index] = infor;

            if(mTarget_1_Index == 0)
            {
                ui->mTarget_1_ThirdValue->setText("0");
                ui->mTarget_1_SecondValue->setText("0");

                ui->mTarget_1_FirstValue->setText(valuenumber);

                mTarget_1_Index = 1;
            }
            else if(mTarget_1_Index == 1)
            {
                ui->mTarget_1_SecondValue->setText(valuenumber);

                mTarget_1_Index = 2;
            }
            else
            {
               ui->mTarget_1_ThirdValue->setText(valuenumber);
                mTarget_1_Index = 0;
            }

            int number = mTarget_1_Value[0] + mTarget_1_Value[1] + mTarget_1_Value[2];

             valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

             ui->mTarget_1_TotalValue->setText(valuenumber);
        }
        break;

    case EVNT_UD_TARGET_2:
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mTarget_2_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mTarget_2_Status->setPixmap(errorStatus);
        }
        else
        {
            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mTarget_2_Value[mTarget_2_Index] = infor;

            if(mTarget_2_Index == 0)
            {
                ui->mTarget_2_ThirdValue->setText("0");
                ui->mTarget_2_SecondValue->setText("0");

                ui->mTarget_2_FirstValue->setText(valuenumber);

                mTarget_2_Index = 1;
            }
            else if(mTarget_2_Index == 1)
            {
                ui->mTarget_2_SecondValue->setText(valuenumber);

                mTarget_2_Index = 2;
            }
            else
            {
               ui->mTarget_2_ThirdValue->setText(valuenumber);
                mTarget_2_Index = 0;
            }

            int number = mTarget_2_Value[0] + mTarget_2_Value[1] + mTarget_2_Value[2];

            valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

            ui->mTarget_2_TotalValue->setText(valuenumber);
        }
        break;

    case EVNT_UD_TARGET_3:
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mTarget_3_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mTarget_3_Status->setPixmap(errorStatus);
        }
        else
        {
            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mTarget_3_Value[mTarget_3_Index] = infor;

            if(mTarget_3_Index == 0)
            {
                ui->mTarget_3_ThirdValue->setText("0");
                ui->mTarget_3_SecondValue->setText("0");

                ui->mTarget_3_FirstValue->setText(valuenumber);

                mTarget_3_Index = 1;
            }
            else if(mTarget_3_Index == 1)
            {
                ui->mTarget_3_SecondValue->setText(valuenumber);

                mTarget_3_Index = 2;
            }
            else
            {
                ui->mTarget_3_ThirdValue->setText(valuenumber);
                mTarget_3_Index = 0;
            }

            int number = mTarget_3_Value[0] + mTarget_3_Value[1] + mTarget_3_Value[2];

             valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

             ui->mTarget_3_TotalValue->setText(valuenumber);
        }
        break;

    default:
        break;
    }


}

void MainWindow::on_mAppClean_clicked()
{
    mTarget_1_Index = 0;
    mTarget_2_Index = 0;
    mTarget_2_Index = 0;

    ui->mTarget_1_FirstValue->setText("0");
    ui->mTarget_2_FirstValue->setText("0");
    ui->mTarget_3_FirstValue->setText("0");

    ui->mTarget_1_SecondValue->setText("0");
    ui->mTarget_2_SecondValue->setText("0");
    ui->mTarget_3_SecondValue->setText("0");

    ui->mTarget_1_ThirdValue->setText("0");
    ui->mTarget_2_ThirdValue->setText("0");
    ui->mTarget_3_ThirdValue->setText("0");

    ui->mTarget_1_TotalValue->setText("0");
    ui->mTarget_2_TotalValue->setText("0");
    ui->mTarget_3_TotalValue->setText("0");

    memset(mTarget_1_Value, 0x00, sizeof(mTarget_1_Value));
    memset(mTarget_2_Value, 0x00, sizeof(mTarget_2_Value));
    memset(mTarget_3_Value, 0x00, sizeof(mTarget_3_Value));
}

void MainWindow::on_mTarget_1_Clean_clicked()
{
     mTarget_1_Index = 0;
     memset(mTarget_1_Value, 0x00, sizeof(mTarget_1_Value));

     ui->mTarget_1_FirstValue->setText("0");
     ui->mTarget_1_SecondValue->setText("0");
     ui->mTarget_1_ThirdValue->setText("0");
     ui->mTarget_1_TotalValue->setText("0");
}

void MainWindow::on_mTarget_2_Clean_clicked()
{
    mTarget_2_Index = 0;
    memset(mTarget_2_Value, 0x00, sizeof(mTarget_2_Value));

    ui->mTarget_2_FirstValue->setText("0");
    ui->mTarget_2_SecondValue->setText("0");
    ui->mTarget_2_ThirdValue->setText("0");
    ui->mTarget_2_TotalValue->setText("0");
}

void MainWindow::on_mTarget_3_Clean_clicked()
{
    mTarget_3_Index = 0;
    memset(mTarget_3_Value, 0x00, sizeof(mTarget_3_Value));

    ui->mTarget_3_FirstValue->setText("0");
    ui->mTarget_3_SecondValue->setText("0");
    ui->mTarget_3_ThirdValue->setText("0");
    ui->mTarget_3_TotalValue->setText("0");
}
