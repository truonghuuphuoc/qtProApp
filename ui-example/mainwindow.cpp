#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "connectionbackground.h"
#include "phnmessage.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

#ifdef _WIN32
  #include <windows.h>
#endif

#include "libxl.h"
#include "phnexcel.h"


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

    QString soundPath   = currentPath + "/system/sound/";

    QPixmap errorStatus (mErrorImagePath);
    ui->mAppStatus->setPixmap(errorStatus);

    QPixmap offlineStatus(mOfflineImagePath);

    //Zone 1
    mZone1_Target_1_Index = 0;
    mZone1_Target_2_Index = 0;
    mZone1_Target_3_Index = 0;

    memset(mZone1_Target_1_Value, 0x00, sizeof(mZone1_Target_1_Value));
    memset(mZone1_Target_2_Value, 0x00, sizeof(mZone1_Target_2_Value));
    memset(mZone1_Target_3_Value, 0x00, sizeof(mZone1_Target_3_Value));

    ui->mZone1_Target_1_Status->setPixmap(offlineStatus);
    ui->mZone1_Target_2_Status->setPixmap(offlineStatus);
    ui->mZone1_Target_3_Status->setPixmap(offlineStatus);

    //Zone 2
    mZone2_Target_1_Index = 0;
    mZone2_Target_2_Index = 0;
    mZone2_Target_3_Index = 0;

    memset(mZone2_Target_1_Value, 0x00, sizeof(mZone2_Target_1_Value));
    memset(mZone2_Target_2_Value, 0x00, sizeof(mZone2_Target_2_Value));
    memset(mZone2_Target_3_Value, 0x00, sizeof(mZone2_Target_3_Value));

    ui->mZone2_Target_1_Status->setPixmap(offlineStatus);
    ui->mZone2_Target_2_Status->setPixmap(offlineStatus);
    ui->mZone2_Target_3_Status->setPixmap(offlineStatus);


    //Zone 3
    mZone3_Target_1_Index = 0;
    mZone3_Target_2_Index = 0;
    mZone3_Target_3_Index = 0;

    memset(mZone3_Target_1_Value, 0x00, sizeof(mZone3_Target_1_Value));
    memset(mZone3_Target_2_Value, 0x00, sizeof(mZone3_Target_2_Value));
    memset(mZone3_Target_3_Value, 0x00, sizeof(mZone3_Target_3_Value));

    ui->mZone3_Target_1_Status->setPixmap(offlineStatus);
    ui->mZone3_Target_2_Status->setPixmap(offlineStatus);
    ui->mZone3_Target_3_Status->setPixmap(offlineStatus);


    mKqTotal        = 0;
    mKqGoi          = 0;
    mKqKha          = 0;
    mKqDat          = 0;
    mKqKhongDat     = 0;
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

            ui->mZone1_Target_1_Status->setPixmap(errorStatus);
            ui->mZone1_Target_2_Status->setPixmap(errorStatus);
            ui->mZone1_Target_3_Status->setPixmap(errorStatus);

            ui->mZone2_Target_1_Status->setPixmap(errorStatus);
            ui->mZone2_Target_2_Status->setPixmap(errorStatus);
            ui->mZone2_Target_3_Status->setPixmap(errorStatus);

            ui->mZone3_Target_1_Status->setPixmap(errorStatus);
            ui->mZone3_Target_2_Status->setPixmap(errorStatus);
            ui->mZone3_Target_3_Status->setPixmap(errorStatus);
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

            QPixmap offlineStatus (mOfflineImagePath);
            ui->mZone1_Target_1_Status->setPixmap(offlineStatus);
            ui->mZone1_Target_2_Status->setPixmap(offlineStatus);
            ui->mZone1_Target_3_Status->setPixmap(offlineStatus);

            ui->mZone2_Target_1_Status->setPixmap(offlineStatus);
            ui->mZone2_Target_2_Status->setPixmap(offlineStatus);
            ui->mZone2_Target_3_Status->setPixmap(offlineStatus);

            ui->mZone3_Target_1_Status->setPixmap(offlineStatus);
            ui->mZone3_Target_2_Status->setPixmap(offlineStatus);
            ui->mZone3_Target_3_Status->setPixmap(offlineStatus);
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

/****************************** ZONE 1 *************************************/
    case EVNT_UD_Z1_TARGET_1:


        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mZone1_Target_1_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mZone1_Target_1_Status->setPixmap(errorStatus);
        }
        else
        {

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mZone1_Target_1_Value[mZone1_Target_1_Index] = infor;

            if(mZone1_Target_1_Index == 0)
            {
                ui->mZone1_Target_1_ThirdValue->setText("0");
                ui->mZone1_Target_1_SecondValue->setText("0");

                mZone1_Target_1_Value[1] = 0;
                mZone1_Target_1_Value[2] = 0;

                ui->mZone1_Target_1_FirstValue->setText(valuenumber);

                mZone1_Target_1_Index = 1;
            }
            else if(mZone1_Target_1_Index == 1)
            {
                ui->mZone1_Target_1_SecondValue->setText(valuenumber);

                mZone1_Target_1_Index = 2;
            }
            else
            {
                ui->mZone1_Target_1_ThirdValue->setText(valuenumber);
                mZone1_Target_1_Index = 0;
            }

            int number = mZone1_Target_1_Value[0] + mZone1_Target_1_Value[1] + mZone1_Target_1_Value[2];

             valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

             ui->mZone1_Target_1_TotalValue->setText(valuenumber);
        }
        break;

    case EVNT_UD_Z1_TARGET_2:
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mZone1_Target_2_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mZone1_Target_2_Status->setPixmap(errorStatus);
        }
        else
        {

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mZone1_Target_2_Value[mZone1_Target_2_Index] = infor;

            if(mZone1_Target_2_Index == 0)
            {
                ui->mZone1_Target_2_ThirdValue->setText("0");
                ui->mZone1_Target_2_SecondValue->setText("0");


                mZone1_Target_2_Value[1] = 0;
                mZone1_Target_2_Value[2] = 0;

                ui->mZone1_Target_2_FirstValue->setText(valuenumber);

                mZone1_Target_2_Index = 1;
            }
            else if(mZone1_Target_2_Index == 1)
            {
                ui->mZone1_Target_2_SecondValue->setText(valuenumber);

                mZone1_Target_2_Index = 2;
            }
            else
            {
               ui->mZone1_Target_2_ThirdValue->setText(valuenumber);
                mZone1_Target_2_Index = 0;
            }

            int number = mZone1_Target_2_Value[0] + mZone1_Target_2_Value[1] + mZone1_Target_2_Value[2];

            valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

            ui->mZone1_Target_2_TotalValue->setText(valuenumber);
        }
        break;

    case EVNT_UD_Z1_TARGET_3:
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mZone1_Target_3_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mZone1_Target_3_Status->setPixmap(errorStatus);
        }
        else
        {

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mZone1_Target_3_Value[mZone1_Target_3_Index] = infor;

            if(mZone1_Target_3_Index == 0)
            {
                ui->mZone1_Target_3_ThirdValue->setText("0");
                ui->mZone1_Target_3_SecondValue->setText("0");


                mZone1_Target_3_Value[1] = 0;
                mZone1_Target_3_Value[2] = 0;

                ui->mZone1_Target_3_FirstValue->setText(valuenumber);

                mZone1_Target_3_Index = 1;
            }
            else if(mZone1_Target_3_Index == 1)
            {
                ui->mZone1_Target_3_SecondValue->setText(valuenumber);

                mZone1_Target_3_Index = 2;
            }
            else
            {
                ui->mZone1_Target_3_ThirdValue->setText(valuenumber);
                mZone1_Target_3_Index = 0;
            }

            int number = mZone1_Target_3_Value[0] + mZone1_Target_3_Value[1] + mZone1_Target_3_Value[2];

            valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

            ui->mZone1_Target_3_TotalValue->setText(valuenumber);
        }
        break;

/****************************** ZONE 2 *************************************/
    case EVNT_UD_Z2_TARGET_1:


        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mZone2_Target_1_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mZone2_Target_1_Status->setPixmap(errorStatus);
        }
        else
        {

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mZone2_Target_1_Value[mZone2_Target_1_Index] = infor;

            if(mZone2_Target_1_Index == 0)
            {
                ui->mZone2_Target_1_ThirdValue->setText("0");
                ui->mZone2_Target_1_SecondValue->setText("0");

                mZone2_Target_1_Value[1] = 0;
                mZone2_Target_1_Value[2] = 0;

                ui->mZone2_Target_1_FirstValue->setText(valuenumber);

                mZone2_Target_1_Index = 1;
            }
            else if(mZone2_Target_1_Index == 1)
            {
                ui->mZone2_Target_1_SecondValue->setText(valuenumber);

                mZone2_Target_1_Index = 2;
            }
            else
            {
                ui->mZone2_Target_1_ThirdValue->setText(valuenumber);
                mZone2_Target_1_Index = 0;
            }

            int number = mZone2_Target_1_Value[0] + mZone2_Target_1_Value[1] + mZone2_Target_1_Value[2];

             valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

             ui->mZone2_Target_1_TotalValue->setText(valuenumber);
        }
        break;

    case EVNT_UD_Z2_TARGET_2:
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mZone2_Target_2_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mZone2_Target_2_Status->setPixmap(errorStatus);
        }
        else
        {

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mZone2_Target_2_Value[mZone2_Target_2_Index] = infor;

            if(mZone2_Target_2_Index == 0)
            {
                ui->mZone2_Target_2_ThirdValue->setText("0");
                ui->mZone2_Target_2_SecondValue->setText("0");


                mZone2_Target_2_Value[1] = 0;
                mZone2_Target_2_Value[2] = 0;

                ui->mZone2_Target_2_FirstValue->setText(valuenumber);

                mZone2_Target_2_Index = 1;
            }
            else if(mZone2_Target_2_Index == 1)
            {
                ui->mZone2_Target_2_SecondValue->setText(valuenumber);

                mZone2_Target_2_Index = 2;
            }
            else
            {
                ui->mZone2_Target_2_ThirdValue->setText(valuenumber);
                mZone2_Target_2_Index = 0;
            }

            int number = mZone2_Target_2_Value[0] + mZone2_Target_2_Value[1] + mZone2_Target_2_Value[2];

            valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

            ui->mZone2_Target_2_TotalValue->setText(valuenumber);
        }
        break;

    case EVNT_UD_Z2_TARGET_3:
        if(infor == PHN_DEV_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mZone2_Target_3_Status->setPixmap(errorStatus);
        }
        else if(infor == PHN_DEV_ONLINE)
        {
            QPixmap errorStatus (mOnlineImagePath);
            ui->mZone2_Target_3_Status->setPixmap(errorStatus);
        }
        else
        {

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mZone2_Target_3_Value[mZone2_Target_3_Index] = infor;

            if(mZone2_Target_3_Index == 0)
            {
                ui->mZone2_Target_3_ThirdValue->setText("0");
                ui->mZone2_Target_3_SecondValue->setText("0");


                mZone2_Target_3_Value[1] = 0;
                mZone2_Target_3_Value[2] = 0;

                ui->mZone2_Target_3_FirstValue->setText(valuenumber);

                mZone2_Target_3_Index = 1;
            }
            else if(mZone2_Target_3_Index == 1)
            {
                ui->mZone2_Target_3_SecondValue->setText(valuenumber);

                mZone2_Target_3_Index = 2;
            }
            else
            {
                ui->mZone2_Target_3_ThirdValue->setText(valuenumber);
                mZone2_Target_3_Index = 0;
            }

            int number = mZone2_Target_3_Value[0] + mZone2_Target_3_Value[1] + mZone2_Target_3_Value[2];

            valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

            ui->mZone2_Target_3_TotalValue->setText(valuenumber);
        }
        break;

/****************************** ZONE 3 *************************************/
            case EVNT_UD_Z3_TARGET_1:


                if(infor == PHN_DEV_OFFLINE)
                {
                    QPixmap errorStatus (mOfflineImagePath);
                    ui->mZone3_Target_1_Status->setPixmap(errorStatus);
                }
                else if(infor == PHN_DEV_ONLINE)
                {
                    QPixmap errorStatus (mOnlineImagePath);
                    ui->mZone3_Target_1_Status->setPixmap(errorStatus);
                }
                else
                {

                    QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

                    mZone3_Target_1_Value[mZone3_Target_1_Index] = infor;

                    if(mZone3_Target_1_Index == 0)
                    {
                        ui->mZone3_Target_1_ThirdValue->setText("0");
                        ui->mZone3_Target_1_SecondValue->setText("0");

                        mZone3_Target_1_Value[1] = 0;
                        mZone3_Target_1_Value[2] = 0;

                        ui->mZone3_Target_1_FirstValue->setText(valuenumber);

                        mZone3_Target_1_Index = 1;
                    }
                    else if(mZone3_Target_1_Index == 1)
                    {
                        ui->mZone3_Target_1_SecondValue->setText(valuenumber);

                        mZone3_Target_1_Index = 2;
                    }
                    else
                    {
                        ui->mZone3_Target_1_ThirdValue->setText(valuenumber);
                        mZone3_Target_1_Index = 0;
                    }

                    int number = mZone3_Target_1_Value[0] + mZone3_Target_1_Value[1] + mZone3_Target_1_Value[2];

                     valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

                     ui->mZone3_Target_1_TotalValue->setText(valuenumber);
                }
                break;

            case EVNT_UD_Z3_TARGET_2:
                if(infor == PHN_DEV_OFFLINE)
                {
                    QPixmap errorStatus (mOfflineImagePath);
                    ui->mZone3_Target_2_Status->setPixmap(errorStatus);
                }
                else if(infor == PHN_DEV_ONLINE)
                {
                    QPixmap errorStatus (mOnlineImagePath);
                    ui->mZone3_Target_2_Status->setPixmap(errorStatus);
                }
                else
                {

                    QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

                    mZone3_Target_2_Value[mZone3_Target_2_Index] = infor;

                    if(mZone3_Target_2_Index == 0)
                    {
                        ui->mZone3_Target_2_ThirdValue->setText("0");
                        ui->mZone3_Target_2_SecondValue->setText("0");


                        mZone3_Target_2_Value[1] = 0;
                        mZone3_Target_2_Value[2] = 0;

                        ui->mZone3_Target_2_FirstValue->setText(valuenumber);

                        mZone3_Target_2_Index = 1;
                    }
                    else if(mZone3_Target_2_Index == 1)
                    {
                        ui->mZone3_Target_2_SecondValue->setText(valuenumber);

                        mZone3_Target_2_Index = 2;
                    }
                    else
                    {
                        ui->mZone3_Target_2_ThirdValue->setText(valuenumber);
                        mZone3_Target_2_Index = 0;
                    }

                    int number = mZone3_Target_2_Value[0] + mZone3_Target_2_Value[1] + mZone3_Target_2_Value[2];

                    valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

                    ui->mZone3_Target_2_TotalValue->setText(valuenumber);
                }
                break;

            case EVNT_UD_Z3_TARGET_3:
                if(infor == PHN_DEV_OFFLINE)
                {
                    QPixmap errorStatus (mOfflineImagePath);
                    ui->mZone3_Target_3_Status->setPixmap(errorStatus);
                }
                else if(infor == PHN_DEV_ONLINE)
                {
                    QPixmap errorStatus (mOnlineImagePath);
                    ui->mZone3_Target_3_Status->setPixmap(errorStatus);
                }
                else
                {

                    QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

                    mZone3_Target_3_Value[mZone3_Target_3_Index] = infor;

                    if(mZone3_Target_3_Index == 0)
                    {
                        ui->mZone3_Target_3_ThirdValue->setText("0");
                        ui->mZone3_Target_3_SecondValue->setText("0");


                        mZone3_Target_3_Value[1] = 0;
                        mZone3_Target_3_Value[2] = 0;

                        ui->mZone3_Target_3_FirstValue->setText(valuenumber);

                        mZone3_Target_3_Index = 1;
                    }
                    else if(mZone3_Target_3_Index == 1)
                    {
                        ui->mZone3_Target_3_SecondValue->setText(valuenumber);

                        mZone3_Target_3_Index = 2;
                    }
                    else
                    {
                        ui->mZone3_Target_3_ThirdValue->setText(valuenumber);
                        mZone3_Target_3_Index = 0;
                    }

                    int number = mZone3_Target_3_Value[0] + mZone3_Target_3_Value[1] + mZone3_Target_3_Value[2];

                    valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

                    ui->mZone3_Target_3_TotalValue->setText(valuenumber);
                }
                break;

    default:
        break;
    }

}

void MainWindow::on_mAppClean_clicked()
{

    //Zone 1
    mZone1_Target_1_Index = 0;
    mZone1_Target_2_Index = 0;
    mZone1_Target_3_Index = 0;

    memset(mZone1_Target_1_Value, 0x00, sizeof(mZone1_Target_1_Value));
    memset(mZone1_Target_2_Value, 0x00, sizeof(mZone1_Target_2_Value));
    memset(mZone1_Target_3_Value, 0x00, sizeof(mZone1_Target_3_Value));

    ui->mZone1_Target_1_FirstValue->setText("0");
    ui->mZone1_Target_2_FirstValue->setText("0");
    ui->mZone1_Target_3_FirstValue->setText("0");

    ui->mZone1_Target_1_SecondValue->setText("0");
    ui->mZone1_Target_2_SecondValue->setText("0");
    ui->mZone1_Target_3_SecondValue->setText("0");

    ui->mZone1_Target_1_ThirdValue->setText("0");
    ui->mZone1_Target_2_ThirdValue->setText("0");
    ui->mZone1_Target_3_ThirdValue->setText("0");

    ui->mZone1_Target_1_TotalValue->setText("0");
    ui->mZone1_Target_2_TotalValue->setText("0");
    ui->mZone1_Target_3_TotalValue->setText("0");

    //Zone 2
    mZone2_Target_1_Index = 0;
    mZone2_Target_2_Index = 0;
    mZone2_Target_3_Index = 0;

    memset(mZone2_Target_1_Value, 0x00, sizeof(mZone2_Target_1_Value));
    memset(mZone2_Target_2_Value, 0x00, sizeof(mZone2_Target_2_Value));
    memset(mZone2_Target_3_Value, 0x00, sizeof(mZone2_Target_3_Value));


    ui->mZone2_Target_1_FirstValue->setText("0");
    ui->mZone2_Target_2_FirstValue->setText("0");
    ui->mZone2_Target_3_FirstValue->setText("0");

    ui->mZone2_Target_1_SecondValue->setText("0");
    ui->mZone2_Target_2_SecondValue->setText("0");
    ui->mZone2_Target_3_SecondValue->setText("0");

    ui->mZone2_Target_1_ThirdValue->setText("0");
    ui->mZone2_Target_2_ThirdValue->setText("0");
    ui->mZone2_Target_3_ThirdValue->setText("0");

    ui->mZone2_Target_1_TotalValue->setText("0");
    ui->mZone2_Target_2_TotalValue->setText("0");
    ui->mZone2_Target_3_TotalValue->setText("0");

    //Zone 3
    mZone3_Target_1_Index = 0;
    mZone3_Target_2_Index = 0;
    mZone3_Target_3_Index = 0;

    memset(mZone3_Target_1_Value, 0x00, sizeof(mZone3_Target_1_Value));
    memset(mZone3_Target_2_Value, 0x00, sizeof(mZone3_Target_2_Value));
    memset(mZone3_Target_3_Value, 0x00, sizeof(mZone3_Target_3_Value));

    ui->mZone3_Target_1_FirstValue->setText("0");
    ui->mZone3_Target_2_FirstValue->setText("0");
    ui->mZone3_Target_3_FirstValue->setText("0");

    ui->mZone3_Target_1_SecondValue->setText("0");
    ui->mZone3_Target_2_SecondValue->setText("0");
    ui->mZone3_Target_3_SecondValue->setText("0");

    ui->mZone3_Target_1_ThirdValue->setText("0");
    ui->mZone3_Target_2_ThirdValue->setText("0");
    ui->mZone3_Target_3_ThirdValue->setText("0");

    ui->mZone3_Target_1_TotalValue->setText("0");
    ui->mZone3_Target_2_TotalValue->setText("0");
    ui->mZone3_Target_3_TotalValue->setText("0");
}

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::Directory);


    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                            "/home",
                                            QFileDialog::ShowDirsOnly
                                            | QFileDialog::DontResolveSymlinks);

    dir += "/report.xlsx";


    using namespace libxl;

    Book* book =  xlCreateXMLBook();//xlCreateBook() use for working with xls files

    Sheet* sheet = book->addSheet(QString("Kết quả").toStdWString().c_str());

    phnExcel::phnAddHeaderFile(book, sheet);
    phnExcel::phnAddDetailFile(ui->tableWidget, book, sheet);


    book->save(dir.toStdWString().c_str());

    book->release();

    ::ShellExecuteA(NULL, "open", dir.toStdString().c_str(), NULL, NULL, SW_SHOW);

}

void MainWindow::on_mTarget_1_Clean_clicked()
{
     mZone1_Target_1_Index = 0;
     memset(mZone1_Target_1_Value, 0x00, sizeof(mZone1_Target_1_Value));

     ui->mZone1_Target_1_FirstValue->setText("0");
     ui->mZone1_Target_1_SecondValue->setText("0");
     ui->mZone1_Target_1_ThirdValue->setText("0");
     ui->mZone1_Target_1_TotalValue->setText("0");
}

void MainWindow::on_mTarget_2_Clean_clicked()
{
    mZone1_Target_2_Index = 0;
    memset(mZone1_Target_2_Value, 0x00, sizeof(mZone1_Target_2_Value));

    ui->mZone1_Target_2_FirstValue->setText("0");
    ui->mZone1_Target_2_SecondValue->setText("0");
    ui->mZone1_Target_2_ThirdValue->setText("0");
    ui->mZone1_Target_2_TotalValue->setText("0");
}

void MainWindow::on_mTarget_3_Clean_clicked()
{
    mZone1_Target_3_Index = 0;
    memset(mZone1_Target_3_Value, 0x00, sizeof(mZone1_Target_3_Value));

    ui->mZone1_Target_3_FirstValue->setText("0");
    ui->mZone1_Target_3_SecondValue->setText("0");
    ui->mZone1_Target_3_ThirdValue->setText("0");
    ui->mZone1_Target_3_TotalValue->setText("0");
}

void MainWindow::on_mInofor1_Add_clicked()
{
    if(ui->mInfor1_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        //randomnNumber();

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        //Ten
        QTableWidgetItem *stt = new QTableWidgetItem(ui->mInfor1_Name->text());
        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 0, stt);

        //Be
        stt = new QTableWidgetItem("1");
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, stt);

        //BS4 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_1_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 2, stt);

        //BS4 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_1_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 3, stt);


        //BS4 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_1_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 4, stt);

        //BS7 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_2_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 5, stt);

        //BS7 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_2_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 6, stt);


        //BS7 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_2_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 7, stt);

        //BS8 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_3_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 8, stt);

        //BS8 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_3_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 9, stt);


        //BS8 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone1_Target_3_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 10, stt);

        int total = 0;
        for(int index =0; index < 3; index ++)
        {
            total += mZone1_Target_1_Value[index];
            total += mZone1_Target_2_Value[index];
            total += mZone1_Target_3_Value[index];
        }

        mKqTotal += 1;

        //Tong
        stt = new QTableWidgetItem( QString("%1").arg(total, 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 11, stt);

        if(total >= 72)
        {
            mKqGoi += 1;
            stt = new QTableWidgetItem("Giỏi");
        }
        else if(total >= 59)
        {
            mKqKha += 1;
            stt = new QTableWidgetItem("Khá");
        }
        else if(total >= 45)
        {
            mKqDat += 1;
            stt = new QTableWidgetItem("Đạt");
        }
        else
        {
            mKqKhongDat += 1;
            stt = new QTableWidgetItem("Không đạt");
        }

        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 12, stt);

        ui->mKqGoi->setText(QString().sprintf("%.2f %", mKqGoi*100/mKqTotal));
        ui->mKqKha->setText(QString().sprintf("%.2f %", mKqKha*100/mKqTotal));
        ui->mKqDat->setText(QString().sprintf("%.2f %", mKqDat*100/mKqTotal));
        ui->mKqKhongDat->setText(QString().sprintf("%.2f %", mKqKhongDat*100/mKqTotal));


        //clear data
        ui->mInfor1_Name->setText("");

        on_mTarget_1_Clean_clicked();
        on_mTarget_2_Clean_clicked();
        on_mTarget_3_Clean_clicked();
    }
}


void MainWindow::on_mZone2_Target_1_Clean_clicked()
{
    mZone2_Target_1_Index = 0;
    memset(mZone2_Target_1_Value, 0x00, sizeof(mZone2_Target_1_Value));

    ui->mZone2_Target_1_FirstValue->setText("0");
    ui->mZone2_Target_1_SecondValue->setText("0");
    ui->mZone2_Target_1_ThirdValue->setText("0");
    ui->mZone2_Target_1_TotalValue->setText("0");
}

void MainWindow::on_mZone2_Target_2_Clean_clicked()
{
    mZone2_Target_2_Index = 0;
    memset(mZone2_Target_2_Value, 0x00, sizeof(mZone2_Target_2_Value));

    ui->mZone2_Target_2_FirstValue->setText("0");
    ui->mZone2_Target_2_SecondValue->setText("0");
    ui->mZone2_Target_2_ThirdValue->setText("0");
    ui->mZone2_Target_2_TotalValue->setText("0");
}

void MainWindow::on_mZone2_Target_3_Clean_clicked()
{
    mZone2_Target_3_Index = 0;
    memset(mZone2_Target_1_Value, 0x00, sizeof(mZone2_Target_1_Value));

    ui->mZone2_Target_3_FirstValue->setText("0");
    ui->mZone2_Target_3_SecondValue->setText("0");
    ui->mZone2_Target_3_ThirdValue->setText("0");
    ui->mZone2_Target_3_TotalValue->setText("0");
}

void MainWindow::on_mInofor2_Add_clicked()
{
    if(ui->mInfor2_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        //Ten
        QTableWidgetItem *stt = new QTableWidgetItem(ui->mInfor2_Name->text());
        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 0, stt);

        //Be
        stt = new QTableWidgetItem("2");
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, stt);

        //BS4 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_1_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 2, stt);

        //BS4 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_1_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 3, stt);


        //BS4 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_1_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 4, stt);

        //BS7 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_2_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 5, stt);

        //BS7 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_2_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 6, stt);


        //BS7 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_2_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 7, stt);

        //BS8 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_3_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 8, stt);

        //BS8 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_3_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 9, stt);


        //BS8 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone2_Target_3_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 10, stt);

        int total = 0;
        for(int index =0; index < 3; index ++)
        {
            total += mZone2_Target_1_Value[index];
            total += mZone2_Target_2_Value[index];
            total += mZone2_Target_3_Value[index];
        }

        mKqTotal += 1;

        //Tong
        stt = new QTableWidgetItem( QString("%1").arg(total, 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 11, stt);

        if(total >= 72)
        {
            mKqGoi += 1;
            stt = new QTableWidgetItem("Giỏi");
        }
        else if(total >= 59)
        {
            mKqKha += 1;
            stt = new QTableWidgetItem("Khá");
        }
        else if(total >= 45)
        {
            mKqDat += 1;
            stt = new QTableWidgetItem("Đạt");
        }
        else
        {
            mKqKhongDat += 1;
            stt = new QTableWidgetItem("Không đạt");
        }

        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 12, stt);

        ui->mKqGoi->setText(QString().sprintf("%.2f %", mKqGoi*100/mKqTotal));
        ui->mKqKha->setText(QString().sprintf("%.2f %", mKqKha*100/mKqTotal));
        ui->mKqDat->setText(QString().sprintf("%.2f %", mKqDat*100/mKqTotal));
        ui->mKqKhongDat->setText(QString().sprintf("%.2f %", mKqKhongDat*100/mKqTotal));


        //clear data
        ui->mInfor2_Name->setText("");

        on_mZone2_Target_1_Clean_clicked();
        on_mZone2_Target_2_Clean_clicked();
        on_mZone2_Target_3_Clean_clicked();
    }
}

void MainWindow::on_mZone3_Target_1_Clean_clicked()
{
    mZone3_Target_1_Index = 0;
    memset(mZone3_Target_1_Value, 0x00, sizeof(mZone3_Target_1_Value));

    ui->mZone3_Target_1_FirstValue->setText("0");
    ui->mZone3_Target_1_SecondValue->setText("0");
    ui->mZone3_Target_1_ThirdValue->setText("0");
    ui->mZone3_Target_1_TotalValue->setText("0");
}

void MainWindow::on_mZone3_Target_2_Clean_clicked()
{
    mZone3_Target_2_Index = 0;
    memset(mZone3_Target_2_Value, 0x00, sizeof(mZone3_Target_2_Value));

    ui->mZone3_Target_2_FirstValue->setText("0");
    ui->mZone3_Target_2_SecondValue->setText("0");
    ui->mZone3_Target_2_ThirdValue->setText("0");
    ui->mZone3_Target_2_TotalValue->setText("0");
}

void MainWindow::on_mZone3_Target_3_Clean_clicked()
{
    mZone3_Target_3_Index = 0;
    memset(mZone3_Target_3_Value, 0x00, sizeof(mZone3_Target_3_Value));

    ui->mZone3_Target_3_FirstValue->setText("0");
    ui->mZone3_Target_3_SecondValue->setText("0");
    ui->mZone3_Target_3_ThirdValue->setText("0");
    ui->mZone3_Target_3_TotalValue->setText("0");
}

void MainWindow::on_mInofor3_Add_clicked()
{
    if(ui->mInfor3_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        //Ten
        QTableWidgetItem *stt = new QTableWidgetItem(ui->mInfor3_Name->text());
        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 0, stt);

        //Be
        stt = new QTableWidgetItem("3");
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, stt);

        //BS4 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_1_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 2, stt);

        //BS4 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_1_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 3, stt);


        //BS4 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_1_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 4, stt);

        //BS7 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_2_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 5, stt);

        //BS7 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_2_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 6, stt);


        //BS7 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_2_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 7, stt);

        //BS8 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_3_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 8, stt);

        //BS8 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_3_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 9, stt);


        //BS8 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mZone3_Target_3_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 10, stt);

        int total = 0;
        for(int index =0; index < 3; index ++)
        {
            total += mZone3_Target_1_Value[index];
            total += mZone3_Target_2_Value[index];
            total += mZone3_Target_3_Value[index];
        }

        mKqTotal += 1;

        //Tong
        stt = new QTableWidgetItem( QString("%1").arg(total, 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 11, stt);

        if(total >= 72)
        {
            mKqGoi += 1;
            stt = new QTableWidgetItem("Giỏi");
        }
        else if(total >= 59)
        {
            mKqKha += 1;
            stt = new QTableWidgetItem("Khá");
        }
        else if(total >= 45)
        {
            mKqDat += 1;
            stt = new QTableWidgetItem("Đạt");
        }
        else
        {
            mKqKhongDat += 1;
            stt = new QTableWidgetItem("Không đạt");
        }

        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 12, stt);

        ui->mKqGoi->setText(QString().sprintf("%.2f %", mKqGoi*100/mKqTotal));
        ui->mKqKha->setText(QString().sprintf("%.2f %", mKqKha*100/mKqTotal));
        ui->mKqDat->setText(QString().sprintf("%.2f %", mKqDat*100/mKqTotal));
        ui->mKqKhongDat->setText(QString().sprintf("%.2f %", mKqKhongDat*100/mKqTotal));


        //clear data
        ui->mInfor3_Name->setText("");

        on_mZone3_Target_1_Clean_clicked();
        on_mZone3_Target_2_Clean_clicked();
        on_mZone3_Target_3_Clean_clicked();
    }
}
