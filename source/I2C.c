#include <stdint.h>
#include <stdbool.h>
#include <xc.h>
#include "../constants.h"
#include "../i2c.h"
#include <libpic30.h>
#include <stddef.h>





void i2c1Enable( uint8_t flags )
{
    // Calculate BGP from FCY
    // brg = ( FCY/FSCL - FCY/10000000) - 1
//    uint32_t fscl = ( flags & kI2C_400KHZ ) ? 400000UL : 100000UL;
//    uint16_t brg = ( ( FCY / fscl ) - ( FCY / 1000000 ) ) - 1;
//    I2C1BRG = brg;
    //I2C1BRG = 179;  // 100 kHz  for 20 MHz
    I2CBRG = 17;  // 400 kHz  for 12 MHz
    
    // enable I2C module
    I2CCONbits.I2CEN = 1;
}


void i2c1Disable()
{
    I2CCONbits.I2CEN = 0;
}


 int16_t i2c1XferInt(
	uint8_t address,
	uint8_t* wdata, int wsize,
	uint8_t* rdata, int rsize )
{
    int16_t count = 0;
    bool hasWrite = ( wdata != NULL ) && ( wsize != 0 );
    bool hasRead = ( rdata != NULL ) && ( rsize != 0 );
    if ( ! ( hasWrite || hasRead ) ) return -1;

    // clear bus collision
    I2CSTATbits.BCL = 0;

    // generate start condition
    I2CCONbits.SEN = 1;
    while ( 1 ) {
        if ( I2CSTATbits.BCL ) return -2;
        if ( ! I2CCONbits.SEN ) break;
    }

    // Send 7-bit slave address and Read/Write flag
    I2CTRN = ( address << 1 ) | ( hasWrite ? 0x00 : 0x01 );
    while ( 1 ) {
        if ( I2CSTATbits.BCL ) return -3;
        if ( ! I2CSTATbits.TRSTAT ) break;
    }

    if ( I2CSTATbits.ACKSTAT ) return -4;
    
    int i;
    // Write data
    for( i = 0; i < wsize; i++ ) {
        I2CTRN = wdata[ i ];
        while ( 1 ) {
            if ( I2CSTATbits.BCL ) return -5;
            if ( ! I2CSTATbits.TRSTAT ) break;
        }
        if ( I2CSTATbits.ACKSTAT ) return -6;
    }

    if ( hasRead ) {
        // if we've been writing, send a Repeated Start
        if ( hasWrite ) {
            // generate start condition
            I2CCONbits.RSEN = 1;
            while ( 1 ) {
                if ( I2CSTATbits.BCL ) return -7;
                if ( ! I2CCONbits.RSEN ) break;
            }

            // Send 7-bit slave address with Read flag
            I2CTRN = ( address << 1 ) | 0x01;
            while ( 1 ) {
                if ( I2CSTATbits.BCL ) return -8;
                if ( ! I2CSTATbits.TRSTAT ) break;
            }
            if ( I2CSTATbits.ACKSTAT ) return -9;
        }

        // Read data
        int i;
        for ( i = 0; i < rsize; i++ ) {
            // check idle
            if ( I2CCON & 0x1F ) return -10;

            // enable reception
            I2CCONbits.RCEN = 1;
            while ( 1 ) {
                if ( I2CSTATbits.BCL ) return -11;
                if ( ! I2CCONbits.RCEN ) break;
            }

            // read data byte from buffer
            rdata[ i ] = I2CRCV;
            count++;

            // send acknowledge (or not acknowledge for final byte)
            I2CCONbits.ACKDT = i == ( rsize - 1 ) ? 1 : 0;
            I2CCONbits.ACKEN = 1;
            while ( 1 ) {
                if ( I2CSTATbits.BCL ) return -12;
                if ( ! I2CCONbits.ACKEN ) break;
            }
        }
    }

    // Generate stop condition
    I2CCONbits.PEN = 1;
    while ( 1 ) {
        if ( I2CSTATbits.BCL ) return -13;
        if ( ! I2CCONbits.PEN ) break;
    }

    return count;
}


int16_t i2c1Xfer(
	uint8_t address,
	uint8_t* wdata, int wsize,
	uint8_t* rdata, int rsize )
{
    int16_t result = i2c1XferInt( address, wdata, wsize, rdata, rsize );
    if ( result < 0 ) {
        // clear bus collision
        I2CSTATbits.BCL = 0;
        // clear start condition
        if ( I2CSTATbits.S )
            I2CCONbits.PEN = 1;
    }
    return result;
}


void i2c1Reset()
{
    // first make sure I2C module is disabled
    i2c1Disable();

    // hold SCL low for 100 ms to reset I2C bus
    //I2C1_SCL_TRIS = 0;
    //I2C1_SCL_LAT = 0;
    int i;
    for (  i = 0; i < 10; i++ )
        __delay_ms( 10 );
    // tri-date SCL and SDA
    //I2C1_SCL_TRIS = 1;
    //I2C1_SDA_TRIS = 1;
    __delay_ms( 10 );
}
