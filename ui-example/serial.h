// STM32 loader serial interface

#ifndef __SERIAL_H__
#define __SERIAL_H__


#ifdef __cplusplus
extern "C" {
#endif

#include <windows.h>
#include <stdint.h>

typedef HANDLE ser_handler;


#define SER_INF_TIMEOUT         0xFFFFFFFF
#define SER_NO_TIMEOUT          0
#define SER_OK                  0
#define SER_ERR                 1

// Serial interface modes (blocking or non blocking)
#define SER_MODE_BLOCKING       0
#define SER_MODE_NONBLOCKING    1

// Setup constants
#define SER_PARITY_NONE         0
#define SER_PARITY_EVEN         1
#define SER_PARITY_ODD          2

#define SER_STOPBITS_1          0
#define SER_STOPBITS_1_5        1
#define SER_STOPBITS_2          2

#define SER_DATABITS_5          5
#define SER_DATABITS_6          6
#define SER_DATABITS_7          7
#define SER_DATABITS_8          8

// Serial access functions (to be implemented by each platform)
ser_handler ser_open( int com_id);

void ser_close( ser_handler id );

int ser_setup( ser_handler id, uint32_t baud, int databits, int parity, int stopbits );

int ser_read( ser_handler id, uint8_t* dest, uint32_t maxsize );

int ser_read_byte( ser_handler id, uint8_t *data);

int ser_write( ser_handler id, const uint8_t *src, uint32_t size );

int ser_write_byte( ser_handler id, uint8_t data );

void ser_set_timeout_ms( ser_handler id, uint32_t timeout );

#ifdef __cplusplus
}
#endif

#endif
