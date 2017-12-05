#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<stdint.h>
#include <QMainWindow>

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

public slots:
   void onProgressChanged(int event, int infor);
private slots:
   void on_mAppClean_clicked();
   void on_mTarget_1_Clean_clicked();
   void on_mTarget_2_Clean_clicked();
   void on_mTarget_3_Clean_clicked();
};

#endif // MAINWINDOW_H
