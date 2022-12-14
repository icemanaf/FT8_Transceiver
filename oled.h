/* 
 * File:   oled.h
 * Author: baghli
 *
 * Created on 3 juin 2017, 16:02
 */
#include <stdint.h>
#include "constants.h"
#include "i2c.h"
#ifndef OLED_H
#define	OLED_H

//#define FCY 20000000					// Instruction cycle rate 

/////////////////////////////////////////////////////////////////////////
//
// I2C Routines
//

//#define I2C1_SCL_TRIS	TRISBbits.TRISB8
//#define I2C1_SDA_TRIS	TRISBbits.TRISB9
//#define I2C1_SCL_LAT	LATBbits.LATB8
//#define I2C1_SDA_LAT	LATBbits.LATB9





void oledCommand( uint8_t ch );
void oledDisplayOffset( uint8_t offset );
void oledData( uint8_t data );
void oledGotoYX(unsigned char Row, unsigned char Column);
void oledPutChar( char ch );
void oledPrint( char *s );
void oledClear();
void oledInit();

#endif	/* OLED_H */

