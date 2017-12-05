#include "phnmessage.h"


uint8_t phnMessage::phnMessage_CrcCalculate(uint8_t* data, uint16_t length)
{
    uint8_t crc = 0;
    uint8_t inbyte;
    uint8_t i, mix;

    uint16_t index;

    for (index = 0; index < length; index++)
    {
        inbyte = data[index];

        for (i = 8; i > 0; i--)
        {
            mix = (uint8_t)((uint8_t)(crc ^ inbyte) & (uint8_t)0x01);
            crc >>= 1;

            if (mix > 0)
            {
                crc ^= 0x8C;
            }

            inbyte >>= 1;
        }
    }

    return crc;
}

void phnMessage::phnMessage_GetMessageFormat(uint8_t* data, uint16_t inLength, uint8_t* message, uint16_t *outLength)
{
    uint8_t value, crc;
    uint8_t index;
    uint16_t position = 0;

    //Start message
    message[position] = MESG_STX;
    position++;

    //Data
    for (index = 0; index < inLength; index++)
    {
        //Data first nibble
        value = (uint8_t)(data[index] >> 4);
        message[position] = (uint8_t)((value << 4) | (value ^ 0x0F));
        position++;

        //Data second nibble
        value = (uint8_t)(data[index] & 0x0F);
        message[position] = (uint8_t)((value << 4) | (value ^ 0x0F));
        position++;
    }

    //End message
    message[position] = MESG_ETX;
    position++;

    //Crc
    crc = phnMessage_CrcCalculate(data, inLength);

    //Crc first nibble
    value = (uint8_t)(crc >> 4);
    message[position] = (uint8_t)((value << 4) | (value ^ 0x0F));
    position++;

    //Crc second nibble
    value = (uint8_t)(crc & 0x0F);
    message[position] = (uint8_t)((value << 4) | (value ^ 0x0F));
    position++;

    *outLength = position;
}
