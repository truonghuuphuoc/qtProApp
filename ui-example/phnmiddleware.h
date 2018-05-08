#ifndef PHNMIDDLEWARE_H
#define PHNMIDDLEWARE_H


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <QtCore>
#include <QThread>
#include <QString>
#include <QMutex>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "connectionbackground.h"
#include "mainwindow.h"

class phnmiddleware: public QThread
{
    Q_OBJECT
public:
    explicit phnmiddleware(QObject *parent = nullptr);
    ~phnmiddleware();

    void run() Q_DECL_OVERRIDE;

    void setAddress(MainWindow *w, uint8_t start, uint8_t destination);


signals:
    void progressChanged(int event, int id, int infor);

private:
    uint8_t mRf_RecvAddress;
    uint8_t mRf_TransAddress;
    MainWindow *mMainWindow;
    ConnectionBackground *mRf_Device_1;
    ConnectionBackground *mRf_Device_2;

    QMutex mRf_Mutex;
};

#endif // PHNMIDDLEWARE_H
