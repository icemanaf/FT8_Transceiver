
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

#include <xc.h>



#include "../constants.h"
#include "../oled.h"
#include "../i2c.h"
#include <libpic30.h>


/////////////////////////////////////////////////////////////////////////
//
// I2C Routines
//



/////////////////////////////////////////////////////////////////////////
//
// SSD1308 OLED Routines
//

#define SSD1308_Address                 0x3c 
#define SSD1308_Command_Mode		0x80
#define SSD1308_Data_Mode               0x40
#define SSD1308_Display_Off_Cmd         0xAE
#define SSD1308_Display_On_Cmd          0xAF
#define SSD1308_Normal_Display_Cmd      0xA6
#define SSD1308_Inverse_Display_Cmd	0xA7
#define SSD1308_Activate_Scroll_Cmd	0x2F
#define SSD1308_Dectivate_Scroll_Cmd	0x2E
#define SSD1308_Set_Brightness_Cmd      0x81


//https://github.com/noopkat/oled-font-5x7/blob/master/oled-font-5x7.js
//https://www4.cs.fau.de/Lehre/WS17/V_GSPIC/Uebungen/doc/group__Display.shtml



//  originial font



const uint8_t OledFont[][8] =
{
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x5F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x07,0x00,0x07,0x00,0x00,0x00},
  {0x00,0x14,0x7F,0x14,0x7F,0x14,0x00,0x00},
  {0x00,0x24,0x2A,0x7F,0x2A,0x12,0x00,0x00},
  {0x00,0x23,0x13,0x08,0x64,0x62,0x00,0x00},
  {0x00,0x36,0x49,0x55,0x22,0x50,0x00,0x00},
  {0x00,0x00,0x05,0x03,0x00,0x00,0x00,0x00},
  {0x00,0x1C,0x22,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x41,0x22,0x1C,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00,0x00},
  {0x00,0x08,0x08,0x3E,0x08,0x08,0x00,0x00},
  {0x00,0xA0,0x60,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x08,0x08,0x08,0x08,0x00,0x00},
  {0x00,0x60,0x60,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x10,0x08,0x04,0x02,0x00,0x00},
  {0x00,0x3E,0x51,0x49,0x45,0x3E,0x00,0x00},
  {0x00,0x00,0x42,0x7F,0x40,0x00,0x00,0x00},
  {0x00,0x62,0x51,0x49,0x49,0x46,0x00,0x00},
  {0x00,0x22,0x41,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x18,0x14,0x12,0x7F,0x10,0x00,0x00},
  {0x00,0x27,0x45,0x45,0x45,0x39,0x00,0x00},
  {0x00,0x3C,0x4A,0x49,0x49,0x30,0x00,0x00},
  {0x00,0x01,0x71,0x09,0x05,0x03,0x00,0x00},
  {0x00,0x36,0x49,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x06,0x49,0x49,0x29,0x1E,0x00,0x00},
  {0x00,0x00,0x36,0x36,0x00,0x00,0x00,0x00},
  {0x00,0x00,0xAC,0x6C,0x00,0x00,0x00,0x00},
  {0x00,0x08,0x14,0x22,0x41,0x00,0x00,0x00},
  {0x00,0x14,0x14,0x14,0x14,0x14,0x00,0x00},
  {0x00,0x41,0x22,0x14,0x08,0x00,0x00,0x00},
  {0x00,0x02,0x01,0x51,0x09,0x06,0x00,0x00},
  {0x00,0x32,0x49,0x79,0x41,0x3E,0x00,0x00},
  {0x00,0x7E,0x09,0x09,0x09,0x7E,0x00,0x00},
  {0x00,0x7F,0x49,0x49,0x49,0x36,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x41,0x22,0x00,0x00},
  {0x00,0x7F,0x41,0x41,0x22,0x1C,0x00,0x00},
  {0x00,0x7F,0x49,0x49,0x49,0x41,0x00,0x00},
  {0x00,0x7F,0x09,0x09,0x09,0x01,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x51,0x72,0x00,0x00},
  {0x00,0x7F,0x08,0x08,0x08,0x7F,0x00,0x00},
  {0x00,0x41,0x7F,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x40,0x41,0x3F,0x01,0x00,0x00},
  {0x00,0x7F,0x08,0x14,0x22,0x41,0x00,0x00},
  {0x00,0x7F,0x40,0x40,0x40,0x40,0x00,0x00},
  {0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00,0x00},
  {0x00,0x7F,0x04,0x08,0x10,0x7F,0x00,0x00},
  {0x00,0x3E,0x41,0x41,0x41,0x3E,0x00,0x00},
  {0x00,0x7F,0x09,0x09,0x09,0x06,0x00,0x00},
  {0x00,0x3E,0x41,0x51,0x21,0x5E,0x00,0x00},
  {0x00,0x7F,0x09,0x19,0x29,0x46,0x00,0x00},
  {0x00,0x26,0x49,0x49,0x49,0x32,0x00,0x00},
  {0x00,0x01,0x01,0x7F,0x01,0x01,0x00,0x00},
  {0x00,0x3F,0x40,0x40,0x40,0x3F,0x00,0x00},
  {0x00,0x1F,0x20,0x40,0x20,0x1F,0x00,0x00},
  {0x00,0x3F,0x40,0x38,0x40,0x3F,0x00,0x00},
  {0x00,0x63,0x14,0x08,0x14,0x63,0x00,0x00},
  {0x00,0x03,0x04,0x78,0x04,0x03,0x00,0x00},
  {0x00,0x61,0x51,0x49,0x45,0x43,0x00,0x00},
  {0x00,0x7F,0x41,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x02,0x04,0x08,0x10,0x20,0x00,0x00},
  {0x00,0x41,0x41,0x7F,0x00,0x00,0x00,0x00},
  {0x00,0x04,0x02,0x01,0x02,0x04,0x00,0x00},
  {0x00,0x80,0x80,0x80,0x80,0x80,0x00,0x00},
  {0x00,0x01,0x02,0x04,0x00,0x00,0x00,0x00},
  {0x00,0x20,0x54,0x54,0x54,0x78,0x00,0x00},
  {0x00,0x7F,0x48,0x44,0x44,0x38,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x28,0x00,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x48,0x7F,0x00,0x00},
  {0x00,0x38,0x54,0x54,0x54,0x18,0x00,0x00},
  {0x00,0x08,0x7E,0x09,0x02,0x00,0x00,0x00},
  {0x00,0x18,0xA4,0xA4,0xA4,0x7C,0x00,0x00},
  {0x00,0x7F,0x08,0x04,0x04,0x78,0x00,0x00},
  {0x00,0x00,0x7D,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x80,0x84,0x7D,0x00,0x00,0x00,0x00},
  {0x00,0x7F,0x10,0x28,0x44,0x00,0x00,0x00},
  {0x00,0x41,0x7F,0x40,0x00,0x00,0x00,0x00},
  {0x00,0x7C,0x04,0x18,0x04,0x78,0x00,0x00},
  {0x00,0x7C,0x08,0x04,0x7C,0x00,0x00,0x00},
  {0x00,0x38,0x44,0x44,0x38,0x00,0x00,0x00},
  {0x00,0xFC,0x24,0x24,0x18,0x00,0x00,0x00},
  {0x00,0x18,0x24,0x24,0xFC,0x00,0x00,0x00},
  {0x00,0x00,0x7C,0x08,0x04,0x00,0x00,0x00},
  {0x00,0x48,0x54,0x54,0x24,0x00,0x00,0x00},
  {0x00,0x04,0x7F,0x44,0x00,0x00,0x00,0x00},
  {0x00,0x3C,0x40,0x40,0x7C,0x00,0x00,0x00},
  {0x00,0x1C,0x20,0x40,0x20,0x1C,0x00,0x00},
  {0x00,0x3C,0x40,0x30,0x40,0x3C,0x00,0x00},
  {0x00,0x44,0x28,0x10,0x28,0x44,0x00,0x00},
  {0x00,0x1C,0xA0,0xA0,0x7C,0x00,0x00,0x00},
  {0x00,0x44,0x64,0x54,0x4C,0x44,0x00,0x00},
  {0x00,0x08,0x36,0x41,0x00,0x00,0x00,0x00},
  {0x00,0x00,0x7F,0x00,0x00,0x00,0x00,0x00},
  {0x00,0x41,0x36,0x08,0x00,0x00,0x00,0x00},
  {0x00,0x02,0x01,0x01,0x02,0x01,0x00,0x00},
  {0x00,0x02,0x05,0x05,0x02,0x00,0x00,0x00}
};


/*
const uint8_t OledFont[][8] =
{
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
{0x00,0x00,0x00,0x00,0x00,0x5F,0x00,0x00},
{0x00,0x00,0x00,0x07,0x00,0x07,0x00,0x00},
{0x00,0x00,0x14,0x7F,0x14,0x7F,0x14,0x00},
{0x00,0x00,0x12,0x2A,0x7F,0x2A,0x24,0x00},
{0x00,0x00,0x62,0x64,0x08,0x13,0x23,0x00},
{0x00,0x00,0x50,0x22,0x55,0x49,0x36,0x00},
{0x00,0x00,0x00,0x00,0x03,0x05,0x00,0x00},
{0x00,0x00,0x00,0x00,0x41,0x22,0x1C,0x00},
{0x00,0x00,0x00,0x00,0x1C,0x22,0x41,0x00},
{0x00,0x00,0x08,0x2A,0x1C,0x2A,0x08,0x00},
{0x00,0x00,0x08,0x08,0x3E,0x08,0x08,0x00},
{0x00,0x00,0x00,0x00,0x00,0x60,0xA0,0x00},
{0x00,0x00,0x08,0x08,0x08,0x08,0x08,0x00},
{0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00},
{0x00,0x00,0x02,0x04,0x08,0x10,0x20,0x00},
{0x00,0x00,0x3E,0x45,0x49,0x51,0x3E,0x00},
{0x00,0x00,0x00,0x40,0x7F,0x42,0x00,0x00},
{0x00,0x00,0x46,0x49,0x49,0x51,0x62,0x00},
{0x00,0x00,0x36,0x49,0x49,0x41,0x22,0x00},
{0x00,0x00,0x10,0x7F,0x12,0x14,0x18,0x00},
{0x00,0x00,0x39,0x45,0x45,0x45,0x27,0x00},
{0x00,0x00,0x30,0x49,0x49,0x4A,0x3C,0x00},
{0x00,0x00,0x03,0x05,0x09,0x71,0x01,0x00},
{0x00,0x00,0x36,0x49,0x49,0x49,0x36,0x00},
{0x00,0x00,0x1E,0x29,0x49,0x49,0x06,0x00},
{0x00,0x00,0x00,0x00,0x36,0x36,0x00,0x00},
{0x00,0x00,0x00,0x00,0x6C,0xAC,0x00,0x00},
{0x00,0x00,0x00,0x41,0x22,0x14,0x08,0x00},
{0x00,0x00,0x14,0x14,0x14,0x14,0x14,0x00},
{0x00,0x00,0x00,0x08,0x14,0x22,0x41,0x00},
{0x00,0x00,0x06,0x09,0x51,0x01,0x02,0x00},
{0x00,0x00,0x3E,0x41,0x79,0x49,0x32,0x00},
{0x00,0x00,0x7E,0x09,0x09,0x09,0x7E,0x00},
{0x00,0x00,0x36,0x49,0x49,0x49,0x7F,0x00},
{0x00,0x00,0x22,0x41,0x41,0x41,0x3E,0x00},
{0x00,0x00,0x1C,0x22,0x41,0x41,0x7F,0x00},
{0x00,0x00,0x41,0x49,0x49,0x49,0x7F,0x00},
{0x00,0x00,0x01,0x09,0x09,0x09,0x7F,0x00},
{0x00,0x00,0x72,0x51,0x41,0x41,0x3E,0x00},
{0x00,0x00,0x7F,0x08,0x08,0x08,0x7F,0x00},
{0x00,0x00,0x00,0x00,0x41,0x7F,0x41,0x00},
{0x00,0x00,0x01,0x3F,0x41,0x40,0x20,0x00},
{0x00,0x00,0x41,0x22,0x14,0x08,0x7F,0x00},
{0x00,0x00,0x40,0x40,0x40,0x40,0x7F,0x00},
{0x00,0x00,0x7F,0x02,0x0C,0x02,0x7F,0x00},
{0x00,0x00,0x7F,0x10,0x08,0x04,0x7F,0x00},
{0x00,0x00,0x3E,0x41,0x41,0x41,0x3E,0x00},
{0x00,0x00,0x06,0x09,0x09,0x09,0x7F,0x00},
{0x00,0x00,0x5E,0x21,0x51,0x41,0x3E,0x00},
{0x00,0x00,0x46,0x29,0x19,0x09,0x7F,0x00},
{0x00,0x00,0x32,0x49,0x49,0x49,0x26,0x00},
{0x00,0x00,0x01,0x01,0x7F,0x01,0x01,0x00},
{0x00,0x00,0x3F,0x40,0x40,0x40,0x3F,0x00},
{0x00,0x00,0x1F,0x20,0x40,0x20,0x1F,0x00},
{0x00,0x00,0x3F,0x40,0x38,0x40,0x3F,0x00},
{0x00,0x00,0x63,0x14,0x08,0x14,0x63,0x00},
{0x00,0x00,0x03,0x04,0x78,0x04,0x03,0x00},
{0x00,0x00,0x43,0x45,0x49,0x51,0x61,0x00},
{0x00,0x00,0x00,0x00,0x41,0x41,0x7F,0x00},
{0x00,0x00,0x20,0x10,0x08,0x04,0x02,0x00},
{0x00,0x00,0x00,0x00,0x7F,0x41,0x41,0x00},
{0x00,0x00,0x04,0x02,0x01,0x02,0x04,0x00},
{0x00,0x00,0x80,0x80,0x80,0x80,0x80,0x00},
{0x00,0x00,0x00,0x00,0x04,0x02,0x01,0x00},
{0x00,0x00,0x78,0x54,0x54,0x54,0x20,0x00},
{0x00,0x00,0x38,0x44,0x44,0x48,0x7F,0x00},
{0x00,0x00,0x00,0x28,0x44,0x44,0x38,0x00},
{0x00,0x00,0x7F,0x48,0x44,0x44,0x38,0x00},
{0x00,0x00,0x18,0x54,0x54,0x54,0x38,0x00},
{0x00,0x00,0x00,0x02,0x09,0x7E,0x08,0x00},
{0x00,0x00,0x7C,0xA4,0xA4,0xA4,0x18,0x00},
{0x00,0x00,0x78,0x04,0x04,0x08,0x7F,0x00},
{0x00,0x00,0x00,0x00,0x00,0x7D,0x00,0x00},
{0x00,0x00,0x00,0x00,0x7D,0x84,0x80,0x00},
{0x00,0x00,0x00,0x44,0x28,0x10,0x7F,0x00},
{0x00,0x00,0x00,0x00,0x40,0x7F,0x41,0x00},
{0x00,0x00,0x78,0x04,0x18,0x04,0x7C,0x00},
{0x00,0x00,0x00,0x7C,0x04,0x08,0x7C,0x00},
{0x00,0x00,0x00,0x38,0x44,0x44,0x38,0x00},
{0x00,0x00,0x00,0x18,0x24,0x24,0xFC,0x00},
{0x00,0x00,0x00,0xFC,0x24,0x24,0x18,0x00},
{0x00,0x00,0x00,0x04,0x08,0x7C,0x00,0x00},
{0x00,0x00,0x00,0x24,0x54,0x54,0x48,0x00},
{0x00,0x00,0x00,0x00,0x44,0x7F,0x04,0x00},
{0x00,0x00,0x00,0x7C,0x40,0x40,0x3C,0x00},
{0x00,0x00,0x1C,0x20,0x40,0x20,0x1C,0x00},
{0x00,0x00,0x3C,0x40,0x30,0x40,0x3C,0x00},
{0x00,0x00,0x44,0x28,0x10,0x28,0x44,0x00},
{0x00,0x00,0x00,0x7C,0xA0,0xA0,0x1C,0x00},
{0x00,0x00,0x44,0x4C,0x54,0x64,0x44,0x00},
{0x00,0x00,0x00,0x00,0x41,0x36,0x08,0x00},
{0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x00},
{0x00,0x00,0x00,0x00,0x08,0x36,0x41,0x00},
{0x00,0x00,0x01,0x02,0x01,0x01,0x02,0x00},
{0x00,0x00,0x00,0x02,0x05,0x05,0x02,0x00}

};
*/
 

void oledCommand( uint8_t ch )
{
    uint8_t bytes[2];
    bytes[0] = SSD1308_Command_Mode;
    bytes[1] = ch;
    i2c1Xfer( SSD1308_Address, bytes, 2, NULL, 0 );
}


void oledDisplayOffset( uint8_t offset )
{
    uint8_t bytes[3];
    bytes[0] = SSD1308_Command_Mode;
    bytes[1] = 0xD3;
    bytes[2] = offset;
    i2c1Xfer( SSD1308_Address, bytes, 3, NULL, 0 );
}


void oledData( uint8_t data )
{
    uint8_t bytes[2];
    bytes[0] = SSD1308_Data_Mode;
    bytes[1] = data;
    i2c1Xfer( SSD1308_Address, bytes, 2, NULL, 0 );
}


void oledGotoYX(unsigned char Row, unsigned char Column)
{
    oledCommand( 0xB0 + Row);
    oledCommand( 0x00 + (8*Column & 0x0F) );
    oledCommand( 0x10 + ((8*Column>>4)&0x0F) );
}


void oledPutChar( char ch )
{
    if ( ( ch < 32 ) || ( ch > 127 ) )
        ch = ' ';

    const uint8_t *base = &OledFont[ch - 32][0];

    uint8_t bytes[9];
    bytes[0] = SSD1308_Data_Mode;
    memmove( bytes + 1, base, 8 );
    i2c1Xfer( SSD1308_Address, bytes, 9, NULL, 0 );
}


void oledPrint( char *s )
{
    while (*s) oledPutChar( *s++);
}


void oledClear()
{
    uint16_t row,col;
    for (  row = 0; row < 8; row++ ) {
        for (  col = 0; col < 16; col++ ) {
            oledGotoYX( row, col );
            oledPutChar( ' ' );
        }
    }
}


void oledInit()
{
/*
    oledCommand( SSD1308_Display_Off_Cmd );
    __delay_ms( 100 );
    oledCommand( SSD1308_Display_On_Cmd );
    __delay_ms( 100 );
    oledCommand( SSD1308_Normal_Display_Cmd );
    oledCommand( SSD1308_Dectivate_Scroll_Cmd );
*/    
// olex way : 
#define OLED_SETCONTRAST 0x81
#define OLED_DISPLAYALLON_RESUME 0xA4
#define OLED_DISPLAYALLON 0xA5
#define OLED_NORMALDISPLAY 0xA6
#define OLED_INVERTDISPLAY 0xA7
#define OLED_DISPLAYOFF 0xAE
#define OLED_DISPLAYON 0xAF
#define OLED_SETDISPLAYOFFSET 0xD3
#define OLED_SETCOMPINS 0xDA
#define OLED_SETVCOMDETECT 0xDB
#define OLED_SETDISPLAYCLOCKDIV 0xD5
#define OLED_SETPRECHARGE 0xD9
#define OLED_SETMULTIPLEX 0xA8
#define OLED_SETLOWCOLUMN 0x00
#define OLED_SETHIGHCOLUMN 0x10
#define OLED_SETSTARTLINE 0x40
#define OLED_MEMORYMODE 0x20
#define OLED_COLUMNADDR 0x21
#define OLED_PAGEADDR   0x22
#define OLED_COMSCANINC 0xC0
#define OLED_COMSCANDEC 0xC8
#define OLED_SEGREMAP 0xA0
#define OLED_CHARGEPUMP 0x8D

    oledCommand( OLED_DISPLAYOFF );
    __delay_ms( 100 );
    oledCommand( OLED_SETDISPLAYCLOCKDIV ); 
    oledCommand( 0x80 );   // the suggested ratio 0x80
    __delay_ms( 100 );    
    oledCommand( OLED_SETMULTIPLEX );
    oledCommand( 0x3F );   
     __delay_ms( 100 );    
    oledCommand( OLED_SETDISPLAYOFFSET );
    oledCommand( 0x0 );   // no offset
     __delay_ms( 100 );    
    oledCommand(OLED_SETSTARTLINE | 0x0); // line #0
     __delay_ms( 100 );    
    oledCommand( OLED_CHARGEPUMP ); 
    oledCommand( 0xAF );  
    __delay_ms( 100 );
    oledCommand( OLED_MEMORYMODE );  
    oledCommand( 0x0 );  // 0x0 act like ks0108
    __delay_ms( 100 );    
                   // 0x0 act like ks0108
    oledCommand(OLED_SEGREMAP | 0x1);
    oledCommand(OLED_COMSCANDEC);
    oledCommand(OLED_SETCOMPINS);         // 0xDA
    oledCommand(0x02);
    oledCommand(OLED_SETCONTRAST);        // 0x81
    oledCommand(0x8F);
    oledCommand(OLED_SETPRECHARGE);       // 0xd9
    oledCommand(0xF1);
    oledCommand(OLED_SETVCOMDETECT);      // 0xDB
    oledCommand(0x40);
    oledCommand(OLED_DISPLAYALLON_RESUME);// 0xA4
    oledCommand(OLED_NORMALDISPLAY);      // 0xA6
    oledCommand(OLED_DISPLAYON);          //--turn on oled panel
    
}
