#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>
#include <QQueue>
#include <QtCore>
#include <QThread>
#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

#define PHN_NUMBER_ZONE  6

typedef enum
{
    PHN_ZONE_1  = 0x00,
    PHN_ZONE_2  = 0x01,
    PHN_ZONE_3  = 0x02,
    PHN_ZONE_4  = 0x03,
    PHN_ZONE_5  = 0x04,
    PHN_ZONE_6  = 0x05,
}phnEnumZone_t;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString mErrorImagePath;
    QString mOfflineImagePath;
    QString mOnlineImagePath;

    QLabel *mZone_Status_Label[PHN_NUMBER_ZONE][3];

    /*UI
     * 0: Value 1
     * 1: Value 2
     * 2: Value 3
     * 3: Value Total
     */
    QLabel *mZone_Value_Label[PHN_NUMBER_ZONE][3][4];

    /*Information
     * Zone
     * Target
     * Value
     */
    uint8_t mZone_Index[PHN_NUMBER_ZONE][3];
    uint8_t mZone_Value[PHN_NUMBER_ZONE][3][3];

    float   mKqTotal;
    float   mKqGoi;
    float   mKqKha;
    float   mKqDat;
    float   mKqKhongDat;

    void randomnNumber(void);
    void UpdateZoneStatus(int zone, int target, int infor);
    void ClearZoneInformation(int zone);
    void AddScoreToTableView(uint8_t zone, QString name);

public slots:
   void onProgressChanged(int event, int id, int infor);
private slots:
   void on_mAppClean_clicked();
   void on_pushButton_clicked();

   void on_m_Zone_1_Clear_clicked();
   void on_m_Zone_2_Clear_clicked();
   void on_m_Zone_3_Clear_clicked();
   void on_m_Zone_4_Clear_clicked();
   void on_m_Zone_5_Clear_clicked();
   void on_m_Zone_6_Clear_clicked();

   void on_m_Zone_1_Add_clicked();
   void on_m_Zone_2_Add_clicked();
   void on_m_Zone_3_Add_clicked();
   void on_m_Zone_4_Add_clicked();
   void on_m_Zone_5_Add_clicked();
   void on_m_Zone_6_Add_clicked();
};

#endif // MAINWINDOW_H
