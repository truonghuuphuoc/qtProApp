#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<stdint.h>
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

    QString mSoundPath;
    QMediaPlayer *mPlayer;
    QMediaPlaylist *mPlayList;

    uint8_t mTarget_1_Index;
    uint8_t mTarget_2_Index;
    uint8_t mTarget_3_Index;

    uint8_t mTarget_1_Value[3];
    uint8_t mTarget_2_Value[3];
    uint8_t mTarget_3_Value[3];

public slots:
   void onProgressChanged(int event, int infor);
private slots:
   void on_mAppClean_clicked();
   void on_mTarget_1_Clean_clicked();
   void on_mTarget_2_Clean_clicked();
   void on_mTarget_3_Clean_clicked();
   void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
