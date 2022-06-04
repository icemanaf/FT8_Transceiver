
// more than once.  
#ifndef I2C_H
#define	I2C_H

#define kI2C_100KHZ     (0x00)
#define kI2C_400KHZ     (0x02)



void i2c1Enable( uint8_t flags );
void i2c1Disable();



 int16_t i2c1XferInt(
	uint8_t address,
	uint8_t* wdata, int wsize,
	uint8_t* rdata, int rsize );


int16_t i2c1Xfer(
	uint8_t address,
	uint8_t* wdata, int wsize,
	uint8_t* rdata, int rsize );


void i2c1Reset();



#endif	/* XC_HEADER_TEMPLATE_H */

