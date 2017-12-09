#ifndef CONNECTIONBACKGROUND_H
#define CONNECTIONBACKGROUND_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <QtCore>
#include <QThread>
#include <QString>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#define LOG_MESSAGE     0

#define MESG_BUFFER_SIZE    200

typedef enum
{
    STAT_SCAN_DEVICE    = 0x00,
    STAT_OPEN_DEVICE    = 0x01,
    STAT_WRIT_DATA      = 0x02,
    STAT_READ_DATA      = 0x03,
    STAT_PROC_DATA      = 0x04,
    STAT_DEVI_ERROR     = 0x05,
    STAT_TOUT_READ      = 0x06,
    STAT_PROC_SLEEP     = 0x07,

}ConnectionProcess;


typedef enum
{
    EVNT_UD_START_ADDR  = 0x00,
    EVNT_UD_DEST_ADDR   = 0x01,
    EVNT_UD_SERIAL_PORT = 0x02,
    EVNT_UD_APP_STATUS  = 0x03,
    EVNT_UD_TARGET_1    = 0x04,
    EVNT_UD_TARGET_2    = 0x05,
    EVNT_UD_TARGET_3    = 0x06,
}phnConnectionEvent;

typedef enum
{
    APP_STATUS_ERROR    = 0x00,
    APP_STATUS_ONLINE   = 0x01,
    APP_STATUS_OFFLINE  = 0x02,
}phnAppStatus;

class ConnectionBackground: public QThread
{
    Q_OBJECT
public:
    explicit ConnectionBackground(QObject *parent = nullptr);
    ~ConnectionBackground();

    void run() Q_DECL_OVERRIDE;

    void setAddress(uint8_t start, uint8_t destination);

private:
    void phnRfReceive_Reset();
    bool phRfReceive_ReceiveMessage();
    bool phnRfReceive_SendMessage(uint8_t *data, uint16_t length);
    void phnRfReceive_MessageHandler(uint8_t data);
    void phnRfReceive_PrepareRequest(void);

    void phnRfReceive_DebugLog(QString message, uint8_t *data, uint16_t length);
    void phnRfReceive_MessageLog(QString message);


signals:
    void progressChanged(int event, int infor);

private:
    bool mSerialError;
    QSerialPort *mSerialPort;

    uint8_t mRf_IsStartFrame;
    uint8_t mRf_IsEndFrame;
    uint8_t mRf_IsFisrtNibble;

    uint8_t mRf_CurrentByte;
    uint8_t mRf_IsMessageRecv;


    uint8_t mRf_RecvAddress;
    uint8_t mRf_TransAddress;


    uint8_t mRf_MessageData[MESG_BUFFER_SIZE];
    uint16_t mRf_DataPosition;


    uint8_t mRf_RequestData[MESG_BUFFER_SIZE];
    uint16_t mRf_RequestLength;
    uint8_t mRf_Ack;

};

#endif // CONNECTIONBACKGROUND_H
