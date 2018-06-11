#include "connectionbackground.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include <QDebug>
#include <QDateTime>
#include <string.h>

#include "phnmessage.h"

QT_USE_NAMESPACE

ConnectionBackground::ConnectionBackground(QObject *parent)
    : QThread(parent)
{
    mSerialError = false;
    mSerialId = (ser_handler )-1;
    mRF_PortName = "";

    mRf_IsStartFrame    = 0;
    mRf_IsEndFrame      = 0;
    mRf_IsFisrtNibble   = 0;

    mRf_CurrentByte     = 0;
    mRf_IsMessageRecv   = 0;


    mRf_RecvAddress    = 0x00;
    mRf_TransAddress = 0x00;


    memset(mRf_MessageData, 0x00, MESG_BUFFER_SIZE);
    mRf_DataPosition = 0;

    memset(mRf_RequestData, 0x00, MESG_BUFFER_SIZE);
    mRf_RequestLength = 0;
    mRf_Ack = 0x00;

    memset(mDv_Status, PHN_DEV_OFFLINE, sizeof(mDv_Status));
    memset(mDv_StatusTime, 0x00, sizeof(mDv_StatusTime));
}

ConnectionBackground::~ConnectionBackground()
{
}

void ConnectionBackground::run()
{
    ConnectionProcess step = STAT_SCAN_DEVICE;

    emit progressChanged(EVNT_UD_START_ADDR, mDv_Id, mRf_RecvAddress);
    emit progressChanged(EVNT_UD_DEST_ADDR, mDv_Id, mRf_TransAddress);

    while(true)
    {
        switch (step) {
        case STAT_SCAN_DEVICE:
        {
            if(mRF_PortName.isEmpty())
            {
                QThread::sleep(1);
                break;
            }

            // Open port
            if( ( mSerialId = ser_open( mRF_PortName.mid(3, mRF_PortName.length() - 3).toInt() ) ) == ( ser_handler )-1 )
            {
                QThread::sleep(1);

                step = STAT_SCAN_DEVICE;
                break;
            }

            step = STAT_OPEN_DEVICE;
            break;
        }

        case STAT_OPEN_DEVICE:
        {

            if(ser_setup( mSerialId, 9600, SER_DATABITS_8, SER_PARITY_NONE, SER_STOPBITS_1 ) != SER_OK)
            {
                ser_close(mSerialId);
                QThread::sleep(1);

                step = STAT_SCAN_DEVICE;
                break;
            }


            emit progressChanged(EVNT_UD_SERIAL_PORT, mDv_Id, mRF_PortName.mid(3, mRF_PortName.length() - 3).toInt());

            if(mDv_Status[0] != APP_STATUS_OFFLINE)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, mDv_Id, APP_STATUS_OFFLINE);
                mDv_Status[0] = APP_STATUS_OFFLINE;
            }

            step = STAT_WRIT_DATA;
            break;
        }

        case STAT_WRIT_DATA:
        {
            phnRfReceive_PrepareRequest();
            mSerialError = phnRfReceive_SendMessage(mRf_RequestData, mRf_RequestLength);

            if(!mSerialError)
            {
                step = STAT_DEVI_ERROR;
                break;
            }

            step = STAT_READ_DATA;
            break;
        }

        case STAT_READ_DATA:
            mSerialError = phRfReceive_ReceiveMessage();

            if(!mSerialError)
            {
                step = STAT_DEVI_ERROR;
                break;
            }

            if(mRf_IsMessageRecv)
            {
                step = STAT_PROC_DATA;
                break;
            }

            step = STAT_TOUT_READ;
            break;

        case STAT_PROC_DATA:
        {
            if(mDv_Status[0] != APP_STATUS_ONLINE)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, mDv_Id, APP_STATUS_ONLINE);

                mDv_Status[0] = APP_STATUS_ONLINE;
            }

            for(int target = 3; target < mRf_DataPosition; target ++)
            {
                qint64 currTime = QDateTime::currentSecsSinceEpoch();
                //Be n - Bia so 4
                if((mDv_Status[target] != mRf_MessageData[target]) && (mRf_MessageData[target] == PHN_DEV_ONLINE))
                {
                    mDv_StatusTime[target] = currTime;
                    emit progressChanged(EVNT_UD_Z1_TARGET_1 + (target -3), mDv_Id, mRf_MessageData[target]);
                }
                else if(mRf_MessageData[target] != PHN_DEV_OFFLINE && mRf_MessageData[target] !=PHN_DEV_ONLINE)
                {
                    mDv_StatusTime[target] = currTime;
                    emit progressChanged(EVNT_UD_Z1_TARGET_1 + (target -3), mDv_Id, mRf_MessageData[target]);
                }
            }

            memcpy(&mDv_Status[3], &mRf_MessageData[3], mRf_DataPosition - 3);

            if(mRf_Ack)
            {
                mRf_Ack = 0x00;
            }
            else
            {
                mRf_Ack = 0x01;
            }

            phnRfReceive_Reset();

            step = STAT_PROC_SLEEP;
            break;
        }

        case STAT_TOUT_READ:
        {
            if(mDv_Status[0] != APP_STATUS_OFFLINE)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, mDv_Id, APP_STATUS_OFFLINE);
            }

            memset(mDv_Status, PHN_DEV_OFFLINE, sizeof(mDv_Status));
            memset(mDv_StatusTime, 0x00, sizeof(mDv_StatusTime));
            mDv_Status[0] = APP_STATUS_OFFLINE;

            step = STAT_WRIT_DATA;
            break;
        }

        case STAT_PROC_SLEEP:
            step = STAT_WRIT_DATA;
            QThread::msleep(1000);
            break;

        case STAT_DEVI_ERROR:
        {
            if(mDv_Status[0] != APP_STATUS_ERROR)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, mDv_Id, APP_STATUS_ERROR);
            }

            memset(mDv_Status, PHN_DEV_OFFLINE, sizeof(mDv_Status));
            memset(mDv_StatusTime, 0x00, sizeof(mDv_StatusTime));
            mDv_Status[0] = APP_STATUS_ERROR;

            //delete
            ser_close(mSerialId);
            mSerialId = (ser_handler)-1;

            step = STAT_SCAN_DEVICE;
            QThread::sleep(1);
            break;
        }

        default:
            step = STAT_SCAN_DEVICE;
            break;
        }
    }
}

void ConnectionBackground::phnRfReceive_Reset()
{
    mRf_IsStartFrame    = 0;
    mRf_IsEndFrame      = 0;
    mRf_DataPosition    = 0;
    mRf_IsFisrtNibble   = 0;
    mRf_IsMessageRecv   = 0;
}


void ConnectionBackground::phnRfReceive_MessageHandler(uint8_t data)
{
    uint8_t crc;
    switch (data)
    {
        case MESG_STX:   // start of text
            phnRfReceive_Reset();

            mRf_IsStartFrame = 1;
            mRf_IsFisrtNibble = 1;
            break;

        case MESG_ETX:   // end of text

            // have end frame
            mRf_IsEndFrame = 1;
            break;

        default:
            // wait until packet officially starts
            if (mRf_IsStartFrame == 0)
            {
                break;
            }

            // check byte is in valid form (4 bits followed by 4 bits complemented)
            if ((data >> 4) != ((data & 0x0F) ^ 0x0F))
            {
                // bad character
                phnRfReceive_Reset();
                break;
            }
            // convert back
            data >>= 4;

            // high-order nibble?
            if (mRf_IsFisrtNibble == 1)
            {
                mRf_CurrentByte = data;
                mRf_IsFisrtNibble = 0;
                break;
            }

            // low-order nibble
            mRf_CurrentByte <<= 4;
            mRf_CurrentByte |= data;
            mRf_IsFisrtNibble = 1;

            // if we have the ETX this must be the CRC
            if (mRf_IsEndFrame == 1)
            {
                crc = phnMessage::phnMessage_CrcCalculate(mRf_MessageData, mRf_DataPosition);
                if (crc != mRf_CurrentByte)
                {
                    phnRfReceive_Reset();
                }
                else
                {
                    //have message
                    mRf_IsMessageRecv = 1;
                }

                break;
            }  // end if have ETX already

            // keep adding if not full
            mRf_MessageData[mRf_DataPosition++] = mRf_CurrentByte;
            break;
    }
}

bool ConnectionBackground::phnRfReceive_SendMessage(uint8_t *data, uint16_t length)
{
     int32_t lenwritted;

    if (mSerialId == (ser_handler)-1)
    {
        return false;
    }

    mRf_Mutex->tryLock(300);


    //clear all data before send
    FlushFileBuffers(mSerialId);

    ser_set_timeout_ms(mSerialId, 1000);
    lenwritted = ser_write(mSerialId, data, length);

    mRf_Mutex->unlock();

    if (lenwritted == 0)
    {
       return false;
    }

    return true;
}

bool ConnectionBackground::phRfReceive_ReceiveMessage()
{
    int res;
    uint8_t rcv;

    res = ser_read_byte(mSerialId, &rcv);

    if(res == 0)
    {
        //no error
        phnRfReceive_MessageLog(QString("Timeout in 1 secnods process"));
        return true;
    }

    phnRfReceive_MessageHandler(rcv);

    //set timeout
    ser_set_timeout_ms(mSerialId, 100);

    do
    {
        res = ser_read_byte(mSerialId, &rcv);

        if(res == 0)
        {
            phnRfReceive_MessageLog(QString("Serial error in read process"));
            //error
            return false;
        }

        phnRfReceive_MessageHandler(rcv);

        if(mRf_IsMessageRecv == 1)
        {
            //check message
            if((mRf_DataPosition % 3) == 0 &&
               mRf_MessageData[0] == mRf_RecvAddress &&
               mRf_MessageData[1] == mRf_TransAddress)
            {
                phnRfReceive_DebugLog(QString("rep: "), mRf_MessageData, mRf_DataPosition);

                //have message
                break;
            }
            else
            {
                //wrong address
                phnRfReceive_MessageLog(QString("command wrong address"));
                phnRfReceive_Reset();
            }
        }

    } while (mRf_IsMessageRecv == 0);

    return true;
}

void ConnectionBackground::phnRfReceive_PrepareRequest()
{
    uint8_t request[MESG_BUFFER_SIZE];

    request[0] = mRf_TransAddress;
    request[1] = mRf_RecvAddress;
    request[2] = mRf_Ack;


    phnRfReceive_DebugLog(QString("req: "), request, 3);

    phnMessage::phnMessage_GetMessageFormat(request, 3, mRf_RequestData, &mRf_RequestLength);
}


void ConnectionBackground::phnRfReceive_DebugLog(QString message, uint8_t *data, uint16_t length)
{
#if(LOG_MESSAGE)

#if(0)
    QString resHex;
    QString s;
    QString log;

    QString im = QTime::currentTime().toString("hh:mm:ss");

    log.sprintf("[%d] ", mDv_Id);


    for (int i = 0; i < length; i++)
    {
        s.sprintf("%02X", data[i]);
        resHex.append(s);
        resHex.append(" ");
    }

    qDebug() << (log + im + " " + message + resHex.toUpper());
#endif
#else
    Q_UNUSED (data);
    Q_UNUSED (length);
#endif
}

void ConnectionBackground::phnRfReceive_MessageLog(QString message)
{
#if(LOG_MESSAGE)
    QString log;

    QString im = QTime::currentTime().toString("hh:mm:ss");

    log.sprintf("[%d] ", mDv_Id );

    qDebug() << (log + im + " " + message);
#endif
}

void ConnectionBackground::setAddress(QString portname, uint8_t id, QMutex *mutex, uint8_t start, uint8_t destination)
{
    mRf_Mutex = mutex;
    mDv_Id = id;
    mRF_PortName = portname;
    mRf_RecvAddress = start;
    mRf_TransAddress = destination;
}

QString ConnectionBackground::getPortName()
{
    return mRF_PortName;
}
