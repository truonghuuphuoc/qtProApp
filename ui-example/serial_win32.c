// Serial inteface implementation for POSIX-compliant systems

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "serial.h"

#pragma warning( push )
#pragma warning( disable : 4142)

#define WIN_ERROR     ( HANDLE )-1
#define WIN_MAX_PORT_NAME   1024

// Helper: set timeout
static int ser_win32_set_timeouts( HANDLE hComm, DWORD ri, DWORD rtm, DWORD rtc, DWORD wtm, DWORD wtc )
{   
    COMMTIMEOUTS timeouts;

    if( GetCommTimeouts( hComm, &timeouts ) == FALSE )
    {
        CloseHandle( hComm );
        return SER_ERR;
    }
    timeouts.ReadIntervalTimeout = ri;
    timeouts.ReadTotalTimeoutConstant = rtm;
    timeouts.ReadTotalTimeoutMultiplier = rtc;
    timeouts.WriteTotalTimeoutConstant = wtm;
    timeouts.WriteTotalTimeoutMultiplier = wtc;

    if( SetCommTimeouts( hComm, &timeouts ) == FALSE )
    {
        CloseHandle( hComm );
        return SER_ERR;
    }

    return SER_OK;
}

// Open the serial port
ser_handler ser_open( int com_id)
{
    char portname[ WIN_MAX_PORT_NAME + 1 ];
    HANDLE hComm;

    portname[ 0 ] = portname[ WIN_MAX_PORT_NAME ] = '\0';
    _snprintf( portname, WIN_MAX_PORT_NAME, "\\\\.\\COM%d", com_id );

    hComm = CreateFile( portname, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0 );

    if( hComm == INVALID_HANDLE_VALUE )
    {
        return WIN_ERROR;
    }

    if( !SetupComm( hComm, 2048, 2048 ) )
    {
        return WIN_ERROR;
    }

    return hComm;
}

// Close the serial port
void ser_close( ser_handler id )
{
    CloseHandle( id );
}

int ser_setup( ser_handler id, uint32_t baud, int databits, int parity, int stopbits )
{
    HANDLE hComm = ( HANDLE )id;
    DCB dcb;

    if( GetCommState( hComm, &dcb ) == FALSE )
    {
        CloseHandle( hComm );
        return SER_ERR;
    }

    dcb.BaudRate = baud;
    dcb.ByteSize = databits;
    dcb.Parity = parity == SER_PARITY_NONE ? NOPARITY : ( parity == SER_PARITY_EVEN ? EVENPARITY : ODDPARITY );
    dcb.StopBits = stopbits == SER_STOPBITS_1 ? ONESTOPBIT : ( stopbits == SER_STOPBITS_1_5 ? ONE5STOPBITS : TWOSTOPBITS );
    dcb.fBinary = TRUE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fParity = parity != SER_PARITY_NONE ? TRUE : FALSE;
    dcb.fOutX = FALSE;
    dcb.fInX = FALSE;
    dcb.fNull = FALSE;
    /**/ dcb.fAbortOnError = FALSE;
    dcb.fOutxCtsFlow = FALSE;
    dcb.fOutxDsrFlow = FALSE;
    dcb.fDtrControl = DTR_CONTROL_DISABLE;
    dcb.fDsrSensitivity = FALSE;
    dcb.fRtsControl = RTS_CONTROL_DISABLE;
    dcb.fOutxCtsFlow = FALSE;

    if( SetCommState( hComm, &dcb ) == 0 )
    {
        CloseHandle( hComm );
        return SER_ERR;
    }

    if( ser_win32_set_timeouts( hComm, 0, 0, 0, 0, 0 ) == SER_ERR )
    {
        CloseHandle( hComm );
        return SER_ERR;
    }

    FlushFileBuffers( hComm );

    return SER_OK;
}

// Read up to the specified number of bytes, return bytes actually read
uint32_t ser_read( ser_handler id, uint8_t* dest, uint32_t maxsize )
{
    HANDLE hComm = ( HANDLE )id;
    DWORD readbytes;

    if( ReadFile( hComm, dest, maxsize, &readbytes, NULL ) == FALSE )
    {
        return 0;
    }

    return readbytes;
}

// Read a single byte and return it (or -1 for error)
int ser_read_byte( ser_handler id, uint8_t *data)
{
    int res = ser_read( id, data, 1 );

    return res;
}

// Write up to the specified number of bytes, return bytes actually written
uint32_t ser_write( ser_handler id, const uint8_t *src, uint32_t size )
{
    HANDLE hComm = ( HANDLE )id;
    DWORD written;

    if( WriteFile( hComm, src, size, &written, NULL ) == FALSE )
    {
        return 0;
    }

    return written;
}

// Write a byte to the serial port
uint32_t ser_write_byte( ser_handler id, uint8_t data )
{
    return ser_write( id, &data, 1 );
}

// Set communication timeout
void ser_set_timeout_ms( ser_handler id, uint32_t timeout )
{
    if( timeout == SER_NO_TIMEOUT )
    {
        ser_win32_set_timeouts( id, MAXDWORD, 0, 0, 0, 0 );
    }
    else if( timeout == SER_INF_TIMEOUT )
    {
        ser_win32_set_timeouts( id, 0, 0, 0, 0, 0 );
    }
    else
    {
        ser_win32_set_timeouts( id, 0, 0, timeout, 0, 0 );
    }
}


#pragma warning( pop )
