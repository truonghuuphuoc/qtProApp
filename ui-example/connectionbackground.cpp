#include "connectionbackground.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include <QDebug>

#include <string.h>

#include "phnmessage.h"

QT_USE_NAMESPACE

ConnectionBackground::ConnectionBackground(QObject *parent)
    : QThread(parent)
{
    mSerialError = false;
    mSerialPort = NULL;

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
}

ConnectionBackground::~ConnectionBackground()
{
}

void ConnectionBackground::run()
{
    ConnectionProcess step = STAT_SCAN_DEVICE;

    uint8_t status[10];

    emit progressChanged(EVNT_UD_START_ADDR, mRf_RecvAddress);
    emit progressChanged(EVNT_UD_DEST_ADDR, mRf_TransAddress);

    memset(status, 0x00, sizeof(0x00));

    while(true)
    {
        switch (step) {
        case STAT_SCAN_DEVICE:
        {
            const auto infos = QSerialPortInfo::availablePorts();
            for (const QSerialPortInfo &info : infos)
            {
               if(!info.isBusy())
               {
                   mSerialPort = new QSerialPort;
                   mSerialPort->setPortName(info.portName());
                   mSerialPort->setBaudRate(QSerialPort::Baud9600);
                   mSerialPort->setDataBits(QSerialPort::Data8);
                   mSerialPort->setStopBits(QSerialPort::OneStop);
                   mSerialPort->setParity(QSerialPort::NoParity);
                   mSerialPort->setFlowControl(QSerialPort::NoFlowControl);

                   step = STAT_OPEN_DEVICE;
                   break;
               }
            }

            QThread::sleep(2);
            break;
        }

        case STAT_OPEN_DEVICE:
        {

            if (mSerialPort != NULL && !mSerialPort->open(QIODevice::ReadWrite))
            {
                delete mSerialPort;
                mSerialPort = NULL;

                step = STAT_SCAN_DEVICE;
                break;
            }

            QString portName = mSerialPort->portName();

            emit progressChanged(EVNT_UD_SERIAL_PORT, portName.mid(3, portName.length() - 3).toInt());

            if(status[0] != APP_STATUS_OFFLINE)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, APP_STATUS_OFFLINE);
                status[0] = APP_STATUS_OFFLINE;
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
            if(status[0] != APP_STATUS_ONLINE)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, APP_STATUS_ONLINE);

                status[0] = APP_STATUS_ONLINE;
            }

            if(mRf_DataPosition >= 6)
            {
                //Be 1 - Bia so 4
                if(status[1] != mRf_MessageData[3])
                {
                    emit progressChanged(EVNT_UD_Z1_TARGET_1, mRf_MessageData[3]);
                }
                else if(mRf_MessageData[3] != PHN_DEV_OFFLINE && mRf_MessageData[3] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z1_TARGET_1, mRf_MessageData[3]);
                }

                //Be 1 - Bia so 7
                if(status[2] != mRf_MessageData[4])
                {
                    emit progressChanged(EVNT_UD_Z1_TARGET_2, mRf_MessageData[4]);
                }
                else if(mRf_MessageData[4] != PHN_DEV_OFFLINE && mRf_MessageData[4] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z1_TARGET_2, mRf_MessageData[4]);
                }

                //Be 1 - Bia so 8
                if(status[3] != mRf_MessageData[5])
                {
                    emit progressChanged(EVNT_UD_Z1_TARGET_3, mRf_MessageData[5]);
                }
                else if(mRf_MessageData[5] != PHN_DEV_OFFLINE && mRf_MessageData[5] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z1_TARGET_3, mRf_MessageData[5]);
                }
            }

            if(mRf_DataPosition >= 9)
            {
                //Be 2 - Bia so 4
                if(status[4] != mRf_MessageData[6])
                {
                    emit progressChanged(EVNT_UD_Z2_TARGET_1, mRf_MessageData[6]);
                }
                else if(mRf_MessageData[6] != PHN_DEV_OFFLINE && mRf_MessageData[6] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z2_TARGET_1, mRf_MessageData[6]);
                }

                //Be 2 - Bia so 7
                if(status[5] != mRf_MessageData[7])
                {
                    emit progressChanged(EVNT_UD_Z2_TARGET_2, mRf_MessageData[7]);
                }
                else if(mRf_MessageData[7] != PHN_DEV_OFFLINE && mRf_MessageData[7] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z2_TARGET_2, mRf_MessageData[7]);
                }

                //Be 2 - Bia so 8
                if(status[6] != mRf_MessageData[8])
                {
                    emit progressChanged(EVNT_UD_Z2_TARGET_3, mRf_MessageData[8]);
                }
                else if(mRf_MessageData[8] != PHN_DEV_OFFLINE && mRf_MessageData[8] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z2_TARGET_3, mRf_MessageData[8]);
                }
            }

            if(mRf_DataPosition >= 12)
            {
                //Be 3 - Bia so 4
                if(status[7] != mRf_MessageData[9])
                {
                    emit progressChanged(EVNT_UD_Z3_TARGET_1, mRf_MessageData[9]);
                }
                else if(mRf_MessageData[9] != PHN_DEV_OFFLINE && mRf_MessageData[9] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z3_TARGET_1, mRf_MessageData[9]);
                }

                //Be 3 - Bia so 7
                if(status[8] != mRf_MessageData[10])
                {
                    emit progressChanged(EVNT_UD_Z3_TARGET_2, mRf_MessageData[10]);
                }
                else if(mRf_MessageData[10] != PHN_DEV_OFFLINE && mRf_MessageData[10] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z3_TARGET_2, mRf_MessageData[10]);
                }


                //Be 3 - Bia so 8
                if(status[8] != mRf_MessageData[11])
                {
                    emit progressChanged(EVNT_UD_Z3_TARGET_3, mRf_MessageData[11]);
                }
                else if(mRf_MessageData[11] != PHN_DEV_OFFLINE && mRf_MessageData[11] !=PHN_DEV_ONLINE)
                {
                    emit progressChanged(EVNT_UD_Z3_TARGET_3, mRf_MessageData[11]);
                }
            }

            memcpy(&status[1], &mRf_MessageData[3], mRf_DataPosition - 3);

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
            if(status[0] != APP_STATUS_OFFLINE)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, APP_STATUS_OFFLINE);
                status[0] = APP_STATUS_OFFLINE;
            }
            step = STAT_WRIT_DATA;
            break;
        }

        case STAT_PROC_SLEEP:
            step = STAT_WRIT_DATA;
            QThread::msleep(300);
            break;

        case STAT_DEVI_ERROR:
        {
            if(status[0] != APP_STATUS_ERROR)
            {
                emit progressChanged(EVNT_UD_APP_STATUS, APP_STATUS_ERROR);
                status[0] = APP_STATUS_ERROR;
            }

            //delete
            mSerialPort->close();
            delete mSerialPort;
            mSerialPort = NULL;

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
    if (mSerialPort != NULL && mSerialPort->isOpen() == false)
    {
        return false;
    }

    //clear all data before send
    mSerialPort->clear(QSerialPort::Direction::AllDirections);

    int16_t lenwritted = (int16_t)mSerialPort->write((const char*)data, length);

    if (lenwritted == -1)
    {
       return false;
    }
    else if (lenwritted != length)
    {
        return false;
    }
    else if (!mSerialPort->waitForBytesWritten(1000)) {
        return false;
    }

    return true;
}

bool ConnectionBackground::phRfReceive_ReceiveMessage()
{
    int timeout;
    uint8_t recv;

    timeout = 3000; //3 seconds
    while (timeout >0)
    {
        if(mSerialPort->bytesAvailable() != 0)
        {
            break;
        }

        mSerialPort->waitForReadyRead(1);

        timeout --;
    }

    if (mSerialPort->error() == QSerialPort::ReadError)
    {
        phnRfReceive_MessageLog(QString("Read error in 3 secnods process"));
        return false;
    }

    if(mSerialPort->bytesAvailable() == 0)
    {
        //no error
       phnRfReceive_MessageLog(QString("Timeout in 3 secnods process"));
        return true;
    }

    do
    {
        uint16_t lenread = mSerialPort->read((char *)&recv, 1);

        if(lenread != 1)
        {
            phnRfReceive_MessageLog(QString("Read 1 byte error in read process"));
            //error
            return false;
        }

        if(mSerialPort->error() == QSerialPort::ReadError)
        {
            phnRfReceive_MessageLog(QString("Serial error in read process"));
            //error
            return false;
        }

        phnRfReceive_MessageHandler(recv);

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
                phnRfReceive_Reset();
            }
        }

        timeout = 300;
        while (timeout >0)
        {
            if(mSerialPort->bytesAvailable() != 0)
            {
                break;
            }

            mSerialPort->waitForReadyRead(1);

            timeout --;
        }

        if(mSerialPort->error() == QSerialPort::ReadError)
        {
            phnRfReceive_MessageLog(QString("Read error in 300 millisecond process"));
            //error
            return false;
        }

        if (mSerialPort->bytesAvailable() == 0)
        {
            phnRfReceive_Reset();

            phnRfReceive_MessageLog(QString("Timeout in 300 millisecond process"));
            //no error
            return true;
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
    QString resHex;
    QString s;

    for (int i = 0; i < length; i++)
    {
        s.sprintf("%02X", data[i]);
        resHex.append(s);
        resHex.append(" ");
    }

    qDebug() << (message + resHex.toUpper());
#else
    Q_UNUSED (data);
    Q_UNUSED (length);
#endif
}

void ConnectionBackground::phnRfReceive_MessageLog(QString message)
{
#if(LOG_MESSAGE)
    qDebug() << message;
#endif
}

void ConnectionBackground::setAddress(uint8_t start, uint8_t destination)
{
    mRf_RecvAddress = start;
    mRf_TransAddress = destination;
}
