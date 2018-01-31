#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>
#include <QQueue>
#include <QtCore>
#include <QThread>
#include <QMainWindow>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

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

    //Zone 1
    uint8_t mZone1_Target_1_Index;
    uint8_t mZone1_Target_2_Index;
    uint8_t mZone1_Target_3_Index;

    uint8_t mZone1_Target_1_Value[3];
    uint8_t mZone1_Target_2_Value[3];
    uint8_t mZone1_Target_3_Value[3];


    //Zone 2
    uint8_t mZone2_Target_1_Index;
    uint8_t mZone2_Target_2_Index;
    uint8_t mZone2_Target_3_Index;

    uint8_t mZone2_Target_1_Value[3];
    uint8_t mZone2_Target_2_Value[3];
    uint8_t mZone2_Target_3_Value[3];

    //Zone 3
    uint8_t mZone3_Target_1_Index;
    uint8_t mZone3_Target_2_Index;
    uint8_t mZone3_Target_3_Index;

    uint8_t mZone3_Target_1_Value[3];
    uint8_t mZone3_Target_2_Value[3];
    uint8_t mZone3_Target_3_Value[3];

    float   mKqTotal;
    float   mKqGoi;
    float   mKqKha;
    float   mKqDat;
    float   mKqKhongDat;

    void randomnNumber(void);

public slots:
   void onProgressChanged(int event, int infor);
private slots:
   void on_mAppClean_clicked();
   void on_mTarget_1_Clean_clicked();
   void on_mTarget_2_Clean_clicked();
   void on_mTarget_3_Clean_clicked();
   void on_pushButton_clicked();
   void on_mInofor1_Add_clicked();
   void on_mZone2_Target_1_Clean_clicked();
   void on_mZone2_Target_2_Clean_clicked();
   void on_mZone2_Target_3_Clean_clicked();
   void on_mInofor2_Add_clicked();
   void on_mZone3_Target_1_Clean_clicked();
   void on_mZone3_Target_2_Clean_clicked();
   void on_mZone3_Target_3_Clean_clicked();
   void on_mInofor3_Add_clicked();
};

#endif // MAINWINDOW_H
