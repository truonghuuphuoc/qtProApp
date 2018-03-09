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

    //UI Zone 1
    mZone_Status_Label[PHN_ZONE_1][0]   = ui->m_Zone_1_T1_Status;
    mZone_Status_Label[PHN_ZONE_1][1]   = ui->m_Zone_1_T2_Status;
    mZone_Status_Label[PHN_ZONE_1][2]   = ui->m_Zone_1_T3_Status;

    mZone_Value_Label[PHN_ZONE_1][0][0] = ui->m_Zone_1_T1_Value_1;
    mZone_Value_Label[PHN_ZONE_1][0][1] = ui->m_Zone_1_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_1][0][2] = ui->m_Zone_1_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_1][0][3] = ui->m_Zone_1_T1_Value_Total;

    mZone_Value_Label[PHN_ZONE_1][1][0] = ui->m_Zone_1_T2_Value_1;
    mZone_Value_Label[PHN_ZONE_1][1][1] = ui->m_Zone_1_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_1][1][2] = ui->m_Zone_1_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_1][1][3] = ui->m_Zone_1_T2_Value_Total;

    mZone_Value_Label[PHN_ZONE_1][2][0] = ui->m_Zone_1_T3_Value_1;
    mZone_Value_Label[PHN_ZONE_1][2][1] = ui->m_Zone_1_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_1][2][2] = ui->m_Zone_1_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_1][2][3] = ui->m_Zone_1_T3_Value_Total;

    //UI Zone 2
    mZone_Status_Label[PHN_ZONE_2][0]   = ui->m_Zone_2_T1_Status;
    mZone_Status_Label[PHN_ZONE_2][1]   = ui->m_Zone_2_T2_Status;
    mZone_Status_Label[PHN_ZONE_2][2]   = ui->m_Zone_2_T3_Status;

    mZone_Value_Label[PHN_ZONE_2][0][0] = ui->m_Zone_2_T1_Value_1;
    mZone_Value_Label[PHN_ZONE_2][0][1] = ui->m_Zone_2_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_2][0][2] = ui->m_Zone_2_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_2][0][3] = ui->m_Zone_2_T1_Value_Total;

    mZone_Value_Label[PHN_ZONE_2][1][0] = ui->m_Zone_2_T2_Value_1;
    mZone_Value_Label[PHN_ZONE_2][1][1] = ui->m_Zone_2_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_2][1][2] = ui->m_Zone_2_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_2][1][3] = ui->m_Zone_2_T2_Value_Total;

    mZone_Value_Label[PHN_ZONE_2][2][0] = ui->m_Zone_2_T3_Value_1;
    mZone_Value_Label[PHN_ZONE_2][2][1] = ui->m_Zone_2_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_2][2][2] = ui->m_Zone_2_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_2][2][3] = ui->m_Zone_2_T3_Value_Total;


    //UI Zone 3
    mZone_Status_Label[PHN_ZONE_3][0]   = ui->m_Zone_3_T1_Status;
    mZone_Status_Label[PHN_ZONE_3][1]   = ui->m_Zone_3_T2_Status;
    mZone_Status_Label[PHN_ZONE_3][2]   = ui->m_Zone_3_T3_Status;

    mZone_Value_Label[PHN_ZONE_3][0][0] = ui->m_Zone_3_T1_Value_1;
    mZone_Value_Label[PHN_ZONE_3][0][1] = ui->m_Zone_3_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_3][0][2] = ui->m_Zone_3_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_3][0][3] = ui->m_Zone_3_T1_Value_Total;

    mZone_Value_Label[PHN_ZONE_3][1][0] = ui->m_Zone_3_T2_Value_1;
    mZone_Value_Label[PHN_ZONE_3][1][1] = ui->m_Zone_3_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_3][1][2] = ui->m_Zone_3_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_3][1][3] = ui->m_Zone_3_T2_Value_Total;

    mZone_Value_Label[PHN_ZONE_3][2][0] = ui->m_Zone_3_T3_Value_1;
    mZone_Value_Label[PHN_ZONE_3][2][1] = ui->m_Zone_3_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_3][2][2] = ui->m_Zone_3_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_3][2][3] = ui->m_Zone_3_T3_Value_Total;

    //UI Zone 4
    mZone_Status_Label[PHN_ZONE_4][0]   = ui->m_Zone_4_T1_Status;
    mZone_Status_Label[PHN_ZONE_4][1]   = ui->m_Zone_4_T2_Status;
    mZone_Status_Label[PHN_ZONE_4][2]   = ui->m_Zone_4_T3_Status;

    mZone_Value_Label[PHN_ZONE_4][0][0] = ui->m_Zone_4_T1_Value_1;
    mZone_Value_Label[PHN_ZONE_4][0][1] = ui->m_Zone_4_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_4][0][2] = ui->m_Zone_4_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_4][0][3] = ui->m_Zone_4_T1_Value_Total;

    mZone_Value_Label[PHN_ZONE_4][1][0] = ui->m_Zone_4_T2_Value_1;
    mZone_Value_Label[PHN_ZONE_4][1][1] = ui->m_Zone_4_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_4][1][2] = ui->m_Zone_4_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_4][1][3] = ui->m_Zone_4_T2_Value_Total;

    mZone_Value_Label[PHN_ZONE_4][2][0] = ui->m_Zone_4_T3_Value_1;
    mZone_Value_Label[PHN_ZONE_4][2][1] = ui->m_Zone_4_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_4][2][2] = ui->m_Zone_4_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_4][2][3] = ui->m_Zone_4_T3_Value_Total;

    //UI Zone 5
    mZone_Status_Label[PHN_ZONE_5][0]   = ui->m_Zone_5_T1_Status;
    mZone_Status_Label[PHN_ZONE_5][1]   = ui->m_Zone_5_T2_Status;
    mZone_Status_Label[PHN_ZONE_5][2]   = ui->m_Zone_5_T3_Status;

    mZone_Value_Label[PHN_ZONE_5][0][0] = ui->m_Zone_5_T1_Value_1;
    mZone_Value_Label[PHN_ZONE_5][0][1] = ui->m_Zone_5_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_5][0][2] = ui->m_Zone_5_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_5][0][3] = ui->m_Zone_5_T1_Value_Total;

    mZone_Value_Label[PHN_ZONE_5][1][0] = ui->m_Zone_5_T2_Value_1;
    mZone_Value_Label[PHN_ZONE_5][1][1] = ui->m_Zone_5_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_5][1][2] = ui->m_Zone_5_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_5][1][3] = ui->m_Zone_5_T2_Value_Total;

    mZone_Value_Label[PHN_ZONE_5][2][0] = ui->m_Zone_5_T3_Value_1;
    mZone_Value_Label[PHN_ZONE_5][2][1] = ui->m_Zone_5_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_5][2][2] = ui->m_Zone_5_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_5][2][3] = ui->m_Zone_5_T3_Value_Total;

    //UI Zone 6
    mZone_Status_Label[PHN_ZONE_6][0]   = ui->m_Zone_6_T1_Status;
    mZone_Status_Label[PHN_ZONE_6][1]   = ui->m_Zone_6_T2_Status;
    mZone_Status_Label[PHN_ZONE_6][2]   = ui->m_Zone_6_T3_Status;

    mZone_Value_Label[PHN_ZONE_6][0][0] = ui->m_Zone_6_T1_Value_1;
    mZone_Value_Label[PHN_ZONE_6][0][1] = ui->m_Zone_6_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_6][0][2] = ui->m_Zone_6_T1_Value_2;
    mZone_Value_Label[PHN_ZONE_6][0][3] = ui->m_Zone_6_T1_Value_Total;

    mZone_Value_Label[PHN_ZONE_6][1][0] = ui->m_Zone_6_T2_Value_1;
    mZone_Value_Label[PHN_ZONE_6][1][1] = ui->m_Zone_6_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_6][1][2] = ui->m_Zone_6_T2_Value_2;
    mZone_Value_Label[PHN_ZONE_6][1][3] = ui->m_Zone_6_T2_Value_Total;

    mZone_Value_Label[PHN_ZONE_6][2][0] = ui->m_Zone_6_T3_Value_1;
    mZone_Value_Label[PHN_ZONE_6][2][1] = ui->m_Zone_6_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_6][2][2] = ui->m_Zone_6_T3_Value_2;
    mZone_Value_Label[PHN_ZONE_6][2][3] = ui->m_Zone_6_T3_Value_Total;

    //Inforamtion
    for(int zone = 0; zone < PHN_NUMBER_ZONE; zone ++)
    {
        for(int trg =0; trg < 3; trg ++)
        {
            mZone_Index[zone][trg]      = 0;
            mZone_Value[zone][trg][0]   = 0;
            mZone_Value[zone][trg][1]   = 0;
            mZone_Value[zone][trg][2]   = 0;
        }
    }

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


void MainWindow::UpdateZoneStatus(int zone, int target, int infor)
{
    if(infor == PHN_DEV_OFFLINE)
    {
        QPixmap errorStatus (mOfflineImagePath);
        mZone_Status_Label[zone][target]->setPixmap(errorStatus);
    }
    else if(infor == PHN_DEV_ONLINE)
    {
        QPixmap errorStatus (mOnlineImagePath);
        mZone_Status_Label[zone][target]->setPixmap(errorStatus);
    }
    else
    {

        QString valuenumber = QString("%1").arg(infor, 0, 10, QChar('0'));

        mZone_Value[zone][target][mZone_Index[zone][target]] = infor;

        if(mZone_Index[zone][target] == 0)
        {
            mZone_Value_Label[zone][target][1]->setText("0");
            mZone_Value_Label[zone][target][2]->setText("0");

            mZone_Value[zone][target][1] = 0;
            mZone_Value[zone][target][2] = 0;

            mZone_Value_Label[zone][target][0]->setText(valuenumber);

            mZone_Index[zone][target] = 1;
        }
        else if(mZone_Index[zone][target] == 1)
        {
            mZone_Value_Label[zone][target][1]->setText(valuenumber);

            mZone_Index[zone][target] = 2;
        }
        else
        {
            mZone_Value_Label[zone][target][2]->setText(valuenumber);
            mZone_Index[zone][target] = 0;
        }

        int number = mZone_Value[zone][target][0] + mZone_Value[zone][target][1] + mZone_Value[zone][target][2];

         valuenumber = QString("%1").arg(number, 0, 10, QChar('0'));

        mZone_Value_Label[zone][target][3]->setText(valuenumber);
    }
}

void MainWindow::onProgressChanged(int event, int infor) {

    switch (event)
    {
    case EVNT_UD_APP_STATUS:
        if(infor == APP_STATUS_OFFLINE)
        {
            QPixmap errorStatus (mOfflineImagePath);
            ui->mAppStatus->setPixmap(errorStatus);

            for(int zone = 0; zone < PHN_NUMBER_ZONE; zone ++)
            {
                for(int trg =0; trg < 3; trg ++)
                {
                    mZone_Status_Label[PHN_ZONE_3][trg]->setPixmap(errorStatus);
                }
            }
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

            for(int zone = 0; zone < PHN_NUMBER_ZONE; zone ++)
            {
                for(int trg =0; trg < 3; trg ++)
                {
                    mZone_Status_Label[PHN_ZONE_3][trg]->setPixmap(offlineStatus);
                }
            }
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
    {
        UpdateZoneStatus(PHN_ZONE_1, 0, infor);
        break;
    }

    case EVNT_UD_Z1_TARGET_2:
    {
        UpdateZoneStatus(PHN_ZONE_1, 1, infor);
        break;
    }

    case EVNT_UD_Z1_TARGET_3:
    {
        UpdateZoneStatus(PHN_ZONE_1, 2, infor);
        break;
    }

/****************************** ZONE 2 *************************************/
    case EVNT_UD_Z2_TARGET_1:
    {
        UpdateZoneStatus(PHN_ZONE_2, 0, infor);
        break;
    }

    case EVNT_UD_Z2_TARGET_2:
    {
        UpdateZoneStatus(PHN_ZONE_2, 1, infor);
        break;
    }

    case EVNT_UD_Z2_TARGET_3:
    {
        UpdateZoneStatus(PHN_ZONE_2, 2, infor);
        break;
    }

/****************************** ZONE 3 *************************************/
    case EVNT_UD_Z3_TARGET_1:
    {
        UpdateZoneStatus(PHN_ZONE_3, 0, infor);
        break;
    }

    case EVNT_UD_Z3_TARGET_2:
    {
        UpdateZoneStatus(PHN_ZONE_3, 1, infor);
        break;
    }

    case EVNT_UD_Z3_TARGET_3:
    {
        UpdateZoneStatus(PHN_ZONE_3, 2, infor);
        break;
    }

/****************************** ZONE 4 *************************************/
    case EVNT_UD_Z4_TARGET_1:
    {
        UpdateZoneStatus(PHN_ZONE_4, 0, infor);
        break;
    }

    case EVNT_UD_Z4_TARGET_2:
    {
        UpdateZoneStatus(PHN_ZONE_4, 1, infor);
        break;
    }

    case EVNT_UD_Z4_TARGET_3:
    {
        UpdateZoneStatus(PHN_ZONE_4, 2, infor);
        break;
    }

/****************************** ZONE 5 *************************************/
    case EVNT_UD_Z5_TARGET_1:
    {
        UpdateZoneStatus(PHN_ZONE_5, 0, infor);
        break;
    }

    case EVNT_UD_Z5_TARGET_2:
    {
        UpdateZoneStatus(PHN_ZONE_5, 1, infor);
        break;
    }

    case EVNT_UD_Z5_TARGET_3:
    {
        UpdateZoneStatus(PHN_ZONE_5, 2, infor);
        break;
    }

/****************************** ZONE 6 *************************************/
    case EVNT_UD_Z6_TARGET_1:
    {
        UpdateZoneStatus(PHN_ZONE_6, 0, infor);
        break;
    }

    case EVNT_UD_Z6_TARGET_2:
    {
        UpdateZoneStatus(PHN_ZONE_6, 1, infor);
        break;
    }

    case EVNT_UD_Z6_TARGET_3:
    {
        UpdateZoneStatus(PHN_ZONE_6, 2, infor);
        break;
    }
    default:
        break;
    }

}

void MainWindow::on_mAppClean_clicked()
{
    on_m_Zone_1_Clear_clicked();
    on_m_Zone_2_Clear_clicked();
    on_m_Zone_3_Clear_clicked();
    on_m_Zone_4_Clear_clicked();
    on_m_Zone_5_Clear_clicked();
    on_m_Zone_6_Clear_clicked();
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


/**************** Clear Zone Code ***********************/

void MainWindow::ClearZoneInformation(int zone)
{
    for(int trg =0; trg < 3; trg ++)
    {
        mZone_Index[zone][trg]      = 0;
        mZone_Value[zone][trg][0]   = 0;
        mZone_Value[zone][trg][1]   = 0;
        mZone_Value[zone][trg][2]   = 0;

        mZone_Value_Label[zone][trg][0]->setText("0");
        mZone_Value_Label[zone][trg][1]->setText("0");
        mZone_Value_Label[zone][trg][2]->setText("0");
        mZone_Value_Label[zone][trg][3]->setText("0");
    }
}
void MainWindow::on_m_Zone_1_Clear_clicked()
{

    ClearZoneInformation(PHN_ZONE_1);

    //clear name
    ui->m_Zone_1_Name->setText("");
}

void MainWindow::on_m_Zone_2_Clear_clicked()
{
    ClearZoneInformation(PHN_ZONE_2);

    //clear name
    ui->m_Zone_2_Name->setText("");
}

void MainWindow::on_m_Zone_3_Clear_clicked()
{
    ClearZoneInformation(PHN_ZONE_3);
    //clear name
    ui->m_Zone_3_Name->setText("");
}

void MainWindow::on_m_Zone_4_Clear_clicked()
{
    ClearZoneInformation(PHN_ZONE_4);
    //clear name
    ui->m_Zone_4_Name->setText("");
}

void MainWindow::on_m_Zone_5_Clear_clicked()
{
    ClearZoneInformation(PHN_ZONE_5);

    //clear name
    ui->m_Zone_5_Name->setText("");
}

void MainWindow::on_m_Zone_6_Clear_clicked()
{
    ClearZoneInformation(PHN_ZONE_6);

    //clear name
    ui->m_Zone_6_Name->setText("");
}




/**************** Add Code ***********************/

void MainWindow::AddScoreToTableView(uint8_t zone, QString name)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    //Ten
    QTableWidgetItem *stt = new QTableWidgetItem(name);
    stt->setTextAlignment(Qt::AlignVCenter);
    ui->tableWidget->setItem(row, 0, stt);

    //Be
    stt = new QTableWidgetItem( QString("%1").arg(zone + 1, 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 1, stt);

    //BS4 - Lan 1
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][0][0], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 2, stt);

    //BS4 - Lan 2
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][0][1], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 3, stt);


    //BS4 - Lan 3
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][0][2], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 4, stt);

    //BS7 - Lan 1
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][1][0], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 5, stt);

    //BS7 - Lan 2
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][1][1], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 6, stt);


    //BS7 - Lan 3
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][1][2], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 7, stt);

    //BS8 - Lan 1
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][2][0], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 8, stt);

    //BS8 - Lan 2
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][2][1], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 9, stt);


    //BS8 - Lan 3
    stt = new QTableWidgetItem( QString("%1").arg(mZone_Value[zone][2][2], 0, 10, QChar('0')));
    stt->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 10, stt);

    int total = 0;
    for(int index =0; index < 3; index ++)
    {
        total += mZone_Value[zone][0][index];
        total += mZone_Value[zone][1][index];
        total += mZone_Value[zone][2][index];
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
}

void MainWindow::on_m_Zone_1_Add_clicked()
{
    if(ui->m_Zone_1_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        AddScoreToTableView(PHN_ZONE_1, ui->m_Zone_1_Name->text());

        on_m_Zone_1_Clear_clicked();

    }
}

void MainWindow::on_m_Zone_2_Add_clicked()
{
    if(ui->m_Zone_2_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        AddScoreToTableView(PHN_ZONE_2, ui->m_Zone_2_Name->text());

        on_m_Zone_2_Clear_clicked();

    }
}

void MainWindow::on_m_Zone_3_Add_clicked()
{
    if(ui->m_Zone_3_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        AddScoreToTableView(PHN_ZONE_3, ui->m_Zone_3_Name->text());

        on_m_Zone_3_Clear_clicked();

    }
}

void MainWindow::on_m_Zone_4_Add_clicked()
{
    if(ui->m_Zone_4_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        AddScoreToTableView(PHN_ZONE_4, ui->m_Zone_4_Name->text());

        on_m_Zone_4_Clear_clicked();

    }
}

void MainWindow::on_m_Zone_5_Add_clicked()
{
    if(ui->m_Zone_5_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        AddScoreToTableView(PHN_ZONE_5, ui->m_Zone_5_Name->text());

        on_m_Zone_5_Clear_clicked();

    }
}

void MainWindow::on_m_Zone_6_Add_clicked()
{
    if(ui->m_Zone_6_Name->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Thông Tin");
        msgBox.setText("Hãy nhập Họ & Tên vào ô Thông Tin");
        msgBox.exec();
    }
    else
    {
        AddScoreToTableView(PHN_ZONE_6, ui->m_Zone_6_Name->text());

        on_m_Zone_6_Clear_clicked();

    }
}
