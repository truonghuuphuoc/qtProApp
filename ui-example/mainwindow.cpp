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

    mSoundPath          = currentPath + "/system/sound/";
    mPlayer = NULL;
    mPlayList = NULL;

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

    QString _zone;
    QString _target;
    QString _index;
    QString _score;
    bool    isSoundPlay = false;

    switch (event)
    {
    case EVNT_UD_APP_STATUS:
        if(infor == APP_STATUS_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mAppStatus->setPixmap(errorStatus);

            ui->mTarget_1_Status->setPixmap(errorStatus);
            ui->mTarget_2_Status->setPixmap(errorStatus);
            ui->mTarget_3_Status->setPixmap(errorStatus);
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
            ui->mTarget_1_Status->setPixmap(offlineStatus);
            ui->mTarget_2_Status->setPixmap(offlineStatus);
            ui->mTarget_3_Status->setPixmap(offlineStatus);
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
            _target = mSoundPath + "bia_1.mp3";

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mTarget_1_Value[mTarget_1_Index] = infor;

            _index = mSoundPath + "lan_" + QString("%1").arg(mTarget_1_Index + 1, 0, 10, QChar('0')) + ".mp3";
            _score = mSoundPath + valuenumber + ".mp3";

            isSoundPlay = true;

            if(mTarget_1_Index == 0)
            {
                ui->mTarget_1_ThirdValue->setText("0");
                ui->mTarget_1_SecondValue->setText("0");

                mTarget_1_Value[1] = 0;
                mTarget_1_Value[2] = 0;

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
            _target = mSoundPath + "bia_2.mp3";

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mTarget_2_Value[mTarget_2_Index] = infor;

            _index = mSoundPath + "lan_" + QString("%1").arg(mTarget_2_Index + 1, 0, 10, QChar('0')) + ".mp3";
            _score = mSoundPath + valuenumber + ".mp3";

            isSoundPlay = true;

            if(mTarget_2_Index == 0)
            {
                ui->mTarget_2_ThirdValue->setText("0");
                ui->mTarget_2_SecondValue->setText("0");


                mTarget_2_Value[1] = 0;
                mTarget_2_Value[2] = 0;

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
            _target = mSoundPath + "bia_3.mp3";

            QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

            mTarget_3_Value[mTarget_3_Index] = infor;

            _index = mSoundPath + "lan_" + QString("%1").arg(mTarget_3_Index + 1, 0, 10, QChar('0')) + ".mp3";
            _score = mSoundPath + valuenumber + ".mp3";

            isSoundPlay = true;

            if(mTarget_3_Index == 0)
            {
                ui->mTarget_3_ThirdValue->setText("0");
                ui->mTarget_3_SecondValue->setText("0");


                mTarget_3_Value[1] = 0;
                mTarget_3_Value[2] = 0;

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

    if(isSoundPlay)
    {
        if(mPlayList != NULL)
        {
            mPlayList->clear();
            delete mPlayList;
            mPlayList = NULL;
        }

       if(mPlayer != NULL)
       {
          mPlayer->stop();

          delete  mPlayer;
       }


       mPlayer = new QMediaPlayer(this);
       mPlayList = new QMediaPlaylist(mPlayer);

       mPlayer->setPlaylist(mPlayList);

       _zone = mSoundPath + "zone_1.mp3";

       mPlayList->addMedia(QUrl::fromLocalFile(_zone));
       mPlayList->addMedia(QUrl::fromLocalFile(_target));
       mPlayList->addMedia(QUrl::fromLocalFile(_index));
       mPlayList->addMedia(QUrl::fromLocalFile(_score));
       // ...
       mPlayList->setCurrentIndex(0);
      //mPlayer->setMedia(QUrl::fromLocalFile(_target));
       qDebug() << _target;
       mPlayer->setVolume(60);
       mPlayer->play();
    }

}

void MainWindow::on_mAppClean_clicked()
{
    mTarget_1_Index = 0;
    mTarget_2_Index = 0;
    mTarget_3_Index = 0;

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

    qDebug()<< dir;
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
        randomnNumber();

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
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_1_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 2, stt);

        //BS4 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_1_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 3, stt);


        //BS4 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_1_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 4, stt);

        //BS7 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_2_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 5, stt);

        //BS7 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_2_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 6, stt);


        //BS7 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_2_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 7, stt);

        //BS8 - Lan 1
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_3_Value[0], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 8, stt);

        //BS8 - Lan 2
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_3_Value[1], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 9, stt);


        //BS8 - Lan 3
        stt = new QTableWidgetItem( QString("%1").arg(mTarget_3_Value[2], 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 10, stt);

        int total = 0;
        for(int index =0; index < 3; index ++)
        {
            total += mTarget_1_Value[index];
            total += mTarget_2_Value[index];
            total += mTarget_3_Value[index];
        }

        //Tong
        stt = new QTableWidgetItem( QString("%1").arg(total, 0, 10, QChar('0')));
        stt->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 11, stt);

        if(total > 50)
        {
            stt = new QTableWidgetItem("Giỏi");
        }
        else if(total > 40)
        {
            stt = new QTableWidgetItem("Khá");
        }
        else if(total > 30)
        {
            stt = new QTableWidgetItem("Trung bình");
        }
        else
        {
            stt = new QTableWidgetItem("Không đạt");
        }

        stt->setTextAlignment(Qt::AlignVCenter);
        ui->tableWidget->setItem(row, 12, stt);
    }
}

void MainWindow::randomnNumber()
{

    QString valuenumber; // = QString("%1").arg(infor, 0, 10, QChar('0'));
    uint8_t total[3];

    memset(total, 0x00, sizeof(total));

    for(int index =0; index < 3; index ++)
    {
        mTarget_1_Value[index] = rand() % 10 + 1;
        mTarget_2_Value[index] = rand() % 10 + 1;
        mTarget_3_Value[index] = rand() % 10 + 1;

        total[0] +=  mTarget_1_Value[index];
        total[1] +=  mTarget_2_Value[index];
        total[2] +=  mTarget_3_Value[index];
    }


    //1
    valuenumber = QString("%1").arg(mTarget_1_Value[0], 0, 10, QChar('0'));
    ui->mTarget_1_FirstValue->setText(valuenumber);

    valuenumber = QString("%1").arg(mTarget_1_Value[1], 0, 10, QChar('0'));
    ui->mTarget_1_SecondValue->setText(valuenumber);

    valuenumber = QString("%1").arg(mTarget_1_Value[2], 0, 10, QChar('0'));
    ui->mTarget_1_ThirdValue->setText(valuenumber);

    valuenumber = QString("%1").arg(total[0], 0, 10, QChar('0'));
    ui->mTarget_1_TotalValue->setText(valuenumber);

    //2
    valuenumber = QString("%1").arg(mTarget_2_Value[0], 0, 10, QChar('0'));
    ui->mTarget_2_FirstValue->setText(valuenumber);

    valuenumber = QString("%1").arg(mTarget_2_Value[1], 0, 10, QChar('0'));
    ui->mTarget_2_SecondValue->setText(valuenumber);

    valuenumber = QString("%1").arg(mTarget_2_Value[2], 0, 10, QChar('0'));
    ui->mTarget_2_ThirdValue->setText(valuenumber);

    valuenumber = QString("%1").arg(total[1], 0, 10, QChar('0'));
    ui->mTarget_2_TotalValue->setText(valuenumber);

    //3
    valuenumber = QString("%1").arg(mTarget_3_Value[0], 0, 10, QChar('0'));
    ui->mTarget_3_FirstValue->setText(valuenumber);

    valuenumber = QString("%1").arg(mTarget_3_Value[1], 0, 10, QChar('0'));
    ui->mTarget_3_SecondValue->setText(valuenumber);

    valuenumber = QString("%1").arg(mTarget_3_Value[2], 0, 10, QChar('0'));
    ui->mTarget_3_ThirdValue->setText(valuenumber);

    valuenumber = QString("%1").arg(total[2], 0, 10, QChar('0'));
    ui->mTarget_3_TotalValue->setText(valuenumber);

}

