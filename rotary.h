
#ifndef ROTARY_H
#define	ROTARY_H

#include <xc.h>
#include <stdint.h>


#define STEP_SIZE 4

typedef void (*rotateEvent)(void);

 struct RotaryEncoder{
    uint8_t position;
    int counter;
    int counter_prev;
    rotateEvent leftCallback;
    rotateEvent rightCallback;
};

void ScanEncoder( uint8_t , uint8_t,struct RotaryEncoder *enc);

#endif	

