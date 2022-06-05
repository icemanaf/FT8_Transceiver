
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


 enum si5351_pll_input plla_ref_osc;
 enum si5351_pll_input pllb_ref_osc;
 enum si5351_pll pll_assignment[8];

uint8_t si5351_init(uint8_t xtal_load_c, uint32_t xo_freq, int32_t corr)
{
    uint8_t status_reg=0;
   

		// Wait for SYS_INIT flag to be clear, indicating that device is ready
		
		do
		{
			status_reg = si5351_read(SI5351_DEVICE_STATUS);
		} while (status_reg >> 7 == 1);

		// Set crystal load capacitance
		si5351_write(SI5351_CRYSTAL_LOAD, (xtal_load_c & SI5351_CRYSTAL_LOAD_MASK) | 0b00010010);

		// Set up the XO reference frequency
		if (xo_freq != 0)
		{
			si5351_set_ref_freq(xo_freq, SI5351_PLL_INPUT_XO);
		}
		else
		{
			si5351_set_ref_freq(SI5351_XTAL_FREQ, SI5351_PLL_INPUT_XO);
		}

		// Set the frequency calibration for the XO
		si5351_set_correction(corr, SI5351_PLL_INPUT_XO);

		si5351_reset();

        status_reg = si5351_read(SI5351_DEVICE_STATUS);
        return status_reg;
   
}




uint8_t si5351_write_bulk(uint8_t addr, uint8_t length, uint8_t *data)
{
    uint8_t bytes[length+1];
    bytes[0]=addr;
    int i=0;
    for(i=0;i<length;i++)
    {
        bytes[i+1]=data[0];
    }
	int ret =i2c1Xfer( SI5351_BUS_BASE_ADDR, bytes, length, NULL, 0 );
    return ret;
}

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


void si5351_set_correction(int32_t corr, enum si5351_pll_input ref_osc)
{
	ref_correction[(uint8_t)ref_osc] = corr;

	// Recalculate and set PLL freqs based on correction value
	si5351_set_pll(plla_freq, SI5351_PLLA);
	si5351_set_pll(pllb_freq, SI5351_PLLB);
}



void si5351_set_pll(uint64_t pll_freq, enum si5351_pll target_pll)
{
  struct Si5351RegSet pll_reg;

	if(target_pll == SI5351_PLLA)
	{
		si5351_pll_calc(SI5351_PLLA, pll_freq, &pll_reg, ref_correction[plla_ref_osc], 0);
	}
	else
	{
		si5351_pll_calc(SI5351_PLLB, pll_freq, &pll_reg, ref_correction[pllb_ref_osc], 0);
	}

  // Derive the register values to write

  // Prepare an array for parameters to be written to
  uint8_t params[20];
  uint8_t i = 0;
  uint8_t temp;

  // Registers 26-27
  temp = ((pll_reg.p3 >> 8) & 0xFF);
  params[i++] = temp;

  temp = (uint8_t)(pll_reg.p3  & 0xFF);
  params[i++] = temp;

  // Register 28
  temp = (uint8_t)((pll_reg.p1 >> 16) & 0x03);
  params[i++] = temp;

  // Registers 29-30
  temp = (uint8_t)((pll_reg.p1 >> 8) & 0xFF);
  params[i++] = temp;

  temp = (uint8_t)(pll_reg.p1  & 0xFF);
  params[i++] = temp;

  // Register 31
  temp = (uint8_t)((pll_reg.p3 >> 12) & 0xF0);
  temp += (uint8_t)((pll_reg.p2 >> 16) & 0x0F);
  params[i++] = temp;

  // Registers 32-33
  temp = (uint8_t)((pll_reg.p2 >> 8) & 0xFF);
  params[i++] = temp;

  temp = (uint8_t)(pll_reg.p2  & 0xFF);
  params[i++] = temp;

  // Write the parameters
  if(target_pll == SI5351_PLLA)
  {
    si5351_write_bulk(SI5351_PLLA_PARAMETERS, i, params);
		plla_freq = pll_freq;
  }
  else if(target_pll == SI5351_PLLB)
  {
    si5351_write_bulk(SI5351_PLLB_PARAMETERS, i, params);
		pllb_freq = pll_freq;
  }

  
}



uint64_t si5351_pll_calc(enum si5351_pll pll, uint64_t freq, struct Si5351RegSet *reg, int32_t correction, uint8_t vcxo)
{
	uint64_t ref_freq;
	if(pll == SI5351_PLLA)
	{
		ref_freq = xtal_freq[(uint8_t)plla_ref_osc] * SI5351_FREQ_MULT;
	}
	else
	{
		ref_freq = xtal_freq[(uint8_t)pllb_ref_osc] * SI5351_FREQ_MULT;
	}
	//ref_freq = 15974400ULL * SI5351_FREQ_MULT;
	uint32_t a, b, c, p1, p2, p3;
	uint64_t lltmp; //, denom;

	// Factor calibration value into nominal crystal frequency
	// Measured in parts-per-billion

	ref_freq = ref_freq + (int32_t)((((((int64_t)correction) << 31) / 1000000000LL) * ref_freq) >> 31);

	// PLL bounds checking
	if (freq < SI5351_PLL_VCO_MIN * SI5351_FREQ_MULT)
	{
		freq = SI5351_PLL_VCO_MIN * SI5351_FREQ_MULT;
	}
	if (freq > SI5351_PLL_VCO_MAX * SI5351_FREQ_MULT)
	{
		freq = SI5351_PLL_VCO_MAX * SI5351_FREQ_MULT;
	}

	// Determine integer part of feedback equation
	a = freq / ref_freq;

	if (a < SI5351_PLL_A_MIN)
	{
		freq = ref_freq * SI5351_PLL_A_MIN;
	}
	if (a > SI5351_PLL_A_MAX)
	{
		freq = ref_freq * SI5351_PLL_A_MAX;
	}

	// Find best approximation for b/c = fVCO mod fIN
	// denom = 1000ULL * 1000ULL;
	// lltmp = freq % ref_freq;
	// lltmp *= denom;
	// do_div(lltmp, ref_freq);

	//b = (((uint64_t)(freq % ref_freq)) * RFRAC_DENOM) / ref_freq;
	if(vcxo)
	{
		b = (((uint64_t)(freq % ref_freq)) * 1000000ULL) / ref_freq;
		c = 1000000ULL;
	}
	else
	{
		b = (((uint64_t)(freq % ref_freq)) * RFRAC_DENOM) / ref_freq;
		c = b ? RFRAC_DENOM : 1;
	}

	// Calculate parameters
  p1 = 128 * a + ((128 * b) / c) - 512;
  p2 = 128 * b - c * ((128 * b) / c);
  p3 = c;

	// Recalculate frequency as fIN * (a + b/c)
	lltmp = ref_freq;
	lltmp *= b;
	do_div(lltmp, c);
	freq = lltmp;
	freq += ref_freq * a;

	reg->p1 = p1;
	reg->p2 = p2;
	reg->p3 = p3;

	if(vcxo)
	{
		return (uint64_t)(128 * a * 1000000ULL + b);
	}
	else
	{
		return freq;
	}
}


void si5351_reset(void)
{
	// Initialize the CLK outputs according to flowchart in datasheet
	// First, turn them off
	si5351_write(16, 0x80);
	si5351_write(17, 0x80);
	si5351_write(18, 0x80);
	si5351_write(19, 0x80);
	si5351_write(20, 0x80);
	si5351_write(21, 0x80);
	si5351_write(22, 0x80);
	si5351_write(23, 0x80);

	// Turn the clocks back on...
	si5351_write(16, 0x0c);
	si5351_write(17, 0x0c);
	si5351_write(18, 0x0c);
	si5351_write(19, 0x0c);
	si5351_write(20, 0x0c);
	si5351_write(21, 0x0c);
	si5351_write(22, 0x0c);
	si5351_write(23, 0x0c);

	// Set PLLA and PLLB to 800 MHz for automatic tuning
	si5351_set_pll(SI5351_PLL_FIXED, SI5351_PLLA);
	si5351_set_pll(SI5351_PLL_FIXED, SI5351_PLLB);

	// Make PLL to CLK assignments for automatic tuning
	pll_assignment[0] = SI5351_PLLA;
	pll_assignment[1] = SI5351_PLLA;
	pll_assignment[2] = SI5351_PLLA;
	pll_assignment[3] = SI5351_PLLA;
	pll_assignment[4] = SI5351_PLLA;
	pll_assignment[5] = SI5351_PLLA;
	pll_assignment[6] = SI5351_PLLB;
	pll_assignment[7] = SI5351_PLLB;

	si5351_set_ms_source(SI5351_CLK0, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK1, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK2, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK3, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK4, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK5, SI5351_PLLA);
	si5351_set_ms_source(SI5351_CLK6, SI5351_PLLB);
	si5351_set_ms_source(SI5351_CLK7, SI5351_PLLB);

	// Reset the VCXO param
	si5351_write(SI5351_VXCO_PARAMETERS_LOW, 0);
	si5351_write(SI5351_VXCO_PARAMETERS_MID, 0);
	si5351_write(SI5351_VXCO_PARAMETERS_HIGH, 0);

	// Then reset the PLLs
	si5351_pll_reset(SI5351_PLLA);
	si5351_pll_reset(SI5351_PLLB);

	// Set initial frequencies
	uint8_t i;
	for(i = 0; i < 8; i++)
	{
		clk_freq[i] = 0;
		si5351_output_enable((enum si5351_clock)i, 0);
		clk_first_set[i] = false;
	}
}


void si5351_pll_reset(enum si5351_pll target_pll)
{
	if(target_pll == SI5351_PLLA)
 	{
    	si5351_write(SI5351_PLL_RESET, SI5351_PLL_RESET_A);
	}
	else if(target_pll == SI5351_PLLB)
	{
	    si5351_write(SI5351_PLL_RESET, SI5351_PLL_RESET_B);
	}
}

void si5351_set_ms_source(enum si5351_clock clk, enum si5351_pll pll)
{
	uint8_t reg_val;

	reg_val = si5351_read(SI5351_CLK0_CTRL + (uint8_t)clk);

	if(pll == SI5351_PLLA)
	{
		reg_val &= ~(SI5351_CLK_PLL_SELECT);
	}
	else if(pll == SI5351_PLLB)
	{
		reg_val |= SI5351_CLK_PLL_SELECT;
	}

	si5351_write(SI5351_CLK0_CTRL + (uint8_t)clk, reg_val);

	pll_assignment[(uint8_t)clk] = pll;
}



void si5351_output_enable(enum si5351_clock clk, uint8_t enable)
{
  uint8_t reg_val;

  reg_val = si5351_read(SI5351_OUTPUT_ENABLE_CTRL);

  if(enable == 1)
  {
    reg_val &= ~(1<<(uint8_t)clk);
  }
  else
  {
    reg_val |= (1<<(uint8_t)clk);
  }

  si5351_write(SI5351_OUTPUT_ENABLE_CTRL, reg_val);
}
