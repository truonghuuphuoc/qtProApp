#ifndef PHNMESSAGE_H
#define PHNMESSAGE_H

#include <stdint.h>

/*Start message*/
#define MESG_STX    0x02

/*End message*/
#define MESG_ETX    0x03

typedef enum
{
    PHN_DEV_ONLINE      = 0xFF,
    PHN_DEV_OFFLINE     = 0xFE,
}phnDeviceStatus_t;

class phnMessage
{
public:
    static uint8_t phnCalculateCrc(uint8_t * ptr, uint16_t length, uint8_t crc);
    static uint8_t phnMessage_CrcCalculate(uint8_t* data, uint16_t length);
    static void phnMessage_GetMessageFormat(uint8_t* data, uint16_t inLength, uint8_t* message, uint16_t *outLength);
};

#endif // PHNMESSAGE_H
