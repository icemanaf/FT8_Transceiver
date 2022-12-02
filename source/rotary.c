
#include "../rotary.h"


 //using the technique described here https://www.mkesc.co.uk/ise.pdf
const signed short LUT[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

void ScanEncoder( uint8_t clk,  uint8_t data, struct RotaryEncoder *enc)
{
    
    enc->position= enc->position<<2;
    enc->position|=(((clk<<1) | data) & 0x03);
    enc->counter+=LUT[(enc->position & 0xf)];
    
    if (enc->counter-enc->counter_prev>STEP_SIZE)
    {  
        enc->rightCallback();   
        enc->counter=0;
        enc->counter_prev=0;
    }
    
    if (enc->counter_prev-enc->counter> STEP_SIZE)
    {
        enc->leftCallback();
         enc->counter=0;
        enc->counter_prev=0;
    }
    
      
}