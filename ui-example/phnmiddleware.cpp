#include "phnmiddleware.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include <QDebug>

#include <string.h>

#include "phnmessage.h"

QT_USE_NAMESPACE

phnmiddleware::phnmiddleware(QObject *parent)
    : QThread(parent)
{
    mRf_RecvAddress     = 0x00;
    mRf_TransAddress    = 0x00;

    mRf_Device_1        = NULL;
    mRf_Device_2        = NULL;

    mRf_Mutex.try_lock();
}

phnmiddleware::~phnmiddleware()
{
}

void phnmiddleware::run()
{
    qint64 currTime;
    qint64 prevTime;

    uint8_t currStatus[EVNT_UD_MAX];
    uint8_t prevStatus[EVNT_UD_MAX];
    uint8_t isUpdated = 0;

    memset(currStatus, 0x00, sizeof(currStatus));
    memset(prevStatus, 0x00, sizeof(prevStatus));

    prevTime = currTime = QDateTime::currentSecsSinceEpoch();



    while(true)
    {
        if(mRf_Device_1 == NULL || mRf_Device_2 == NULL)
        {
            const auto infos = QSerialPortInfo::availablePorts();
            for (const QSerialPortInfo &info : infos)
            {
               if(!info.isBusy())
               {
                   if(mRf_Device_1 == NULL)
                   {
                       mRf_Device_1 = new ConnectionBackground;

                       mRf_Device_1->setAddress(info.portName(), 1, &mRf_Mutex, mRf_RecvAddress, mRf_TransAddress);

                       // Connect our signal and slot
                       QObject::connect(mRf_Device_1, SIGNAL(progressChanged(int, int, int)),mMainWindow,SLOT(onProgressChanged(int, int, int)));

                       // Setup callback for cleanup when it finishes
                       QObject::connect(mRf_Device_1, SIGNAL(finished()),mRf_Device_1, SLOT(deleteLater()));

                       // Run, Forest, run!
                       mRf_Device_1->start(); // This invokes WorkerThread::run in a new thread

                   }
                   else if((mRf_Device_2 == NULL) && (info.portName().compare(mRf_Device_1->getPortName()) != 0))
                   {
                       mRf_Device_2= new ConnectionBackground;

                       mRf_Device_2->setAddress(info.portName(), 2, &mRf_Mutex, mRf_RecvAddress, mRf_TransAddress);

                       // Connect our signal and slot
                       QObject::connect(mRf_Device_2, SIGNAL(progressChanged(int, int ,int)),mMainWindow,SLOT(onProgressChanged(int, int, int)));

                       // Setup callback for cleanup when it finishes
                       QObject::connect(mRf_Device_2, SIGNAL(finished()),mRf_Device_2, SLOT(deleteLater()));

                       // Run, Forest, run!
                       mRf_Device_2->start(); // This invokes WorkerThread::run in a new thread
                   }
                   else
                   {
                       break;
                   }
               }
            }
        }

        QThread::sleep(1);

        currTime = QDateTime::currentSecsSinceEpoch();

        if((currTime - prevTime) >= 2)
        {
            prevTime = currTime;
            isUpdated = 0;

            memset(currStatus, 0x00, sizeof(currStatus));

            if(mRf_Device_1 != NULL)
            {
                for(int target = 3; target < EVNT_UD_MAX; target ++)
                {
                  if((currTime - mRf_Device_1->mDv_StatusTime[target]) > 2)
                  {
                      currStatus[target] = PHN_DEV_OFFLINE;
                  }
                  else
                  {
                      currStatus[target] = PHN_DEV_ONLINE;
                  }
                }

                isUpdated = 1;
            }

            if(mRf_Device_2 != NULL)
            {
                for(int target = 3; target < EVNT_UD_MAX; target ++)
                {
                  if((currTime - mRf_Device_2->mDv_StatusTime[target]) > 2)
                  {
                      if(currStatus[target] != PHN_DEV_ONLINE)
                      {
                        currStatus[target] = PHN_DEV_OFFLINE;
                      }
                  }
                  else
                  {
                      currStatus[target] = PHN_DEV_ONLINE;
                  }
                }

                isUpdated = 1;
            }
            if(isUpdated == 1)
            {
                 for(int target = 3; target < EVNT_UD_MAX; target ++)
                 {
                     if((currStatus[target] != prevStatus[target]) && (currStatus[target] == PHN_DEV_OFFLINE))
                     {
                        emit progressChanged(EVNT_UD_Z1_TARGET_1 + (target -3), 3, currStatus[target]);
                     }
                 }

                 memcpy(prevStatus, currStatus, sizeof(prevStatus));
            }
        }
    }
}


void phnmiddleware::setAddress(MainWindow *w, uint8_t start, uint8_t destination)
{
    mMainWindow = w;
    mRf_RecvAddress = start;
    mRf_TransAddress = destination;
}
