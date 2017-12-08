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

    emit progressChanged(EVNT_UD_START_ADDR, mRf_RecvAddress);
    emit progressChanged(EVNT_UD_DEST_ADDR, mRf_TransAddress);

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
                   qDebug() << info.portName();
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
            uint8_t waitdevice = 1;

            if (mSerialPort != NULL && !mSerialPort->open(QIODevice::ReadWrite))
            {
                delete mSerialPort;
                mSerialPort = NULL;

                step = STAT_SCAN_DEVICE;
                break;
            }

            QString portName = mSerialPort->portName();

            emit progressChanged(EVNT_UD_SERIAL_PORT, portName.mid(3, portName.length() - 3).toInt());

            emit progressChanged(EVNT_UD_APP_STATUS, waitdevice);

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
            uint8_t onlinedevice = 2;
            emit progressChanged(EVNT_UD_APP_STATUS, onlinedevice);

            //process data
            emit progressChanged(EVNT_UD_TARGET_1, mRf_MessageData[3]);
            emit progressChanged(EVNT_UD_TARGET_2, mRf_MessageData[4]);
            emit progressChanged(EVNT_UD_TARGET_3, mRf_MessageData[5]);

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
            uint8_t offline = 1;
            emit progressChanged(EVNT_UD_APP_STATUS, offline);

            step = STAT_PROC_SLEEP;
            break;
        }

        case STAT_PROC_SLEEP:
            step = STAT_WRIT_DATA;
            QThread::sleep(3);
            break;

        case STAT_DEVI_ERROR:
        {
            uint8_t error = 0;
            emit progressChanged(EVNT_UD_APP_STATUS, error);

            //delete
            mSerialPort->close();
            delete mSerialPort;
            mSerialPort = NULL;

            step = STAT_SCAN_DEVICE;
            QThread::sleep(1);
            break;
        }

        default:
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
    mSerialPort->readAll();

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

    timeout = 1000;
    while (mSerialPort->bytesAvailable() == 0 && timeout > 0)
    {
        timeout--;

        if(mSerialPort->error() == QSerialPort::ReadError ||
           mSerialPort->error() == QSerialPort::TimeoutError)
        {
            //error
            return false;
        }

        QThread::msleep(1);
    }

    if(mSerialPort->bytesAvailable() == 0)
    {
        //no error
        return true;
    }

    do
    {
        uint16_t lenread = mSerialPort->read((char *)&recv, 1);

        if(lenread != 1)
        {
            //error
            return false;
        }

        if(mSerialPort->error() == QSerialPort::ReadError ||
           mSerialPort->error() == QSerialPort::TimeoutError)
        {
            //error
            return false;
        }

        phnRfReceive_MessageHandler(recv);

        if(mRf_IsMessageRecv == 1)
        {
            //check message
            if(mRf_DataPosition == 6 &&
               mRf_MessageData[0] == mRf_RecvAddress &&
               mRf_MessageData[1] == mRf_TransAddress)
            {

                QByteArray array((const char*)mRf_MessageData, mRf_DataPosition);
                qDebug() << "rep: " << QString(array.toHex().toUpper());

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
        while (mSerialPort->bytesAvailable() == 0 && timeout > 0)
        {
            timeout--;

            if(mSerialPort->error() == QSerialPort::ReadError ||
               mSerialPort->error() == QSerialPort::TimeoutError)
            {
                //error
                return false;
            }

            QThread::msleep(1);
        }

        if (mSerialPort->bytesAvailable() == 0)
        {
            phnRfReceive_Reset();

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


    QByteArray array((const char*)request, 3);
    qDebug() << "req: " << QString(array.toHex().toUpper());

    phnMessage::phnMessage_GetMessageFormat(request, 3, mRf_RequestData, &mRf_RequestLength);
}


void ConnectionBackground::setAddress(uint8_t start, uint8_t destination)
{
    mRf_RecvAddress = start;
    mRf_TransAddress = destination;
}
