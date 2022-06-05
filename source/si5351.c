
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
#include "../i2c.h"
#include "../si5351.h"
#include <libpic30.h>


uint64_t clk_freq[8];
uint64_t plla_freq;
uint64_t pllb_freq;

uint32_t xtal_freq[2];


int32_t ref_correction[2];
uint8_t clkin_div;
uint8_t i2c_bus_addr;
uint8_t clk_first_set[8];




uint8_t si5351_init(uint8_t xtal_load_c, uint32_t xo_freq, int32_t corr)
{
    return 0;
}




//uint8_t si5351_write_bulk(uint8_t addr, uint8_t length, uint8_t *data)
//{
//    uint8_t bytes[length+1];
//    bytes[0]=addr;
//    int i=0;
//    for(i=0;i<length;i++)
//    {
//        bytes[i+1]=data[0];
//    }
//	int ret =i2c1Xfer( SI5351_BUS_BASE_ADDR, bytes, length, NULL, 0 );
//    return ret;
//}

uint8_t si5351_write(uint8_t addr, uint8_t data)
{
    uint8_t bytes[2];
    bytes[0]=addr;
    bytes[1]=data;
	int ret =i2c1Xfer( SI5351_BUS_BASE_ADDR, bytes, 1, NULL, 0 );
    return ret;
}

uint8_t si5351_read(uint8_t addr)
{
	uint8_t bytes[1];
    uint8_t read[1];
    
    bytes[0]=addr;
    i2c1Xfer( SI5351_BUS_BASE_ADDR, bytes, 1, read, 1 );
    
    return read[0];
}


void si5351_set_ref_freq(uint32_t ref_freq, enum si5351_pll_input ref_osc)
{
	// uint8_t reg_val;
	//reg_val = si5351_read(SI5351_PLL_INPUT_SOURCE);

	// Clear the bits first
	//reg_val &= ~(SI5351_CLKIN_DIV_MASK);

	if(ref_freq <= 30000000UL)
	{
		xtal_freq[(uint8_t)ref_osc] = ref_freq;
		//reg_val |= SI5351_CLKIN_DIV_1;
		if(ref_osc == SI5351_PLL_INPUT_CLKIN)
		{
			clkin_div = SI5351_CLKIN_DIV_1;
		}
	}
	else if(ref_freq > 30000000UL && ref_freq <= 60000000UL)
	{
		xtal_freq[(uint8_t)ref_osc] = ref_freq / 2;
		//reg_val |= SI5351_CLKIN_DIV_2;
		if(ref_osc == SI5351_PLL_INPUT_CLKIN)
		{
			clkin_div = SI5351_CLKIN_DIV_2;
		}
	}
	else if(ref_freq > 60000000UL && ref_freq <= 100000000UL)
	{
		xtal_freq[(uint8_t)ref_osc] = ref_freq / 4;
		//reg_val |= SI5351_CLKIN_DIV_4;
		if(ref_osc == SI5351_PLL_INPUT_CLKIN)
		{
			clkin_div = SI5351_CLKIN_DIV_4;
		}
	}
	else
	{
		//reg_val |= SI5351_CLKIN_DIV_1;
	}

	//si5351_write(SI5351_PLL_INPUT_SOURCE, reg_val);
}