#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdint.h>
#include "phnevent.h"
#include <QQueue>
#include <QtCore>
#include <QThread>
#include <QMainWindow>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include "phnsoundplayer.h"

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

    uint8_t mTarget_1_Index;
    uint8_t mTarget_2_Index;
    uint8_t mTarget_3_Index;

    uint8_t mTarget_1_Value[3];
    uint8_t mTarget_2_Value[3];
    uint8_t mTarget_3_Value[3];

	QQueue<phnEvent> mEvent;
	phnSoundPlayer *mSoundThread;

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
};

#endif // MAINWINDOW_H
