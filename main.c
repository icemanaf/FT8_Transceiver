// FOSC
#pragma config FOSFPR = HS2_PLL8        // Oscillator (HS2 w/PLL 8x)
#pragma config FCKSMEN = CSW_FSCM_OFF   // Clock Switching and Monitor (Sw Disabled, Mon Disabled)

// FWDT
#pragma config FWPSB = WDTPSB_16        // WDT Prescaler B (1:16)
#pragma config FWPSA = WDTPSA_512       // WDT Prescaler A (1:512)
#pragma config WDT = WDT_OFF            // Watchdog Timer (Disabled)

// FBORPOR
#pragma config FPWRT = PWRT_64          // POR Timer Value (64ms)
#pragma config BODENV = BORV20          // Brown Out Voltage (Reserved)
#pragma config BOREN = PBOR_ON          // PBOR Enable (Enabled)
#pragma config MCLRE = MCLR_EN          // Master Clear Enable (Enabled)

// FGS
#pragma config GWRP = GWRP_OFF          // General Code Segment Write Protect (Disabled)
#pragma config GCP = CODE_PROT_OFF      // General Segment Code Protection (Disabled)

// FICD
#pragma config ICS = ICS_PGD            // Comm Channel Select (Use PGC/EMUC and PGD/EMUD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



#include "constants.h"
#include <xc.h> 
#include <libpic30.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "oled.h"
#include "i2c.h"
#include "si5351.h"
#include "rotary.h"
#include "controller.h"

#define FREQ_CORRECTION 40020




//globals
state current_state;

volatile int T3Counter;
volatile long T1Counter;
volatile uint16_t IC1Capture;
volatile uint16_t IC1Capture2;
volatile int period;
volatile short inputOn=0;
volatile short int0;
volatile short int2;

short osc_on=0;

int val=0;
struct RotaryEncoder rot;





//input capture 1 module interrupt
void __attribute__((__interrupt__, __auto_psv__)) _IC1Interrupt(void)
{
    inputOn=20;
    //read the two capture values
    IC1Capture2=IC1BUF;
    IC1Capture=IC1BUF;
    if (IC1Capture>IC1Capture2)
    {
       period=IC1Capture-IC1Capture2; 
    }
    else
    {
        period=IC1Capture2-IC1Capture;
    }
    TMR3=0;
   _IC1IF=0;
    
}

///Timer3 ISR
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void)
{
    // Clear Timer 1 interrupt flag
    T3Counter++;
    
    _T3IF=0;
 
}



void __attribute__((__interrupt__, auto_psv)) _INT0Interrupt(void)
{
    int0++;
    IFS0bits.INT0IF=0;
}



void __attribute__((__interrupt__, auto_psv)) _INT2Interrupt(void)
{
   
   
    
    int2=1;
    IFS1bits.INT2IF = 0;    //Clear the INT2 interrupt flag 
}


void DisplayState(state *val)
{
    char buffer[20];
    long freq=GetFrequency(val);;
    int step=GetStepValue(val);
    int band=GetBandValue(val);
    
    oledGotoYX( 2, 2 );
    oledPrint("            ");
    if (val->current_selection == FREQ)
    {
        sprintf(buffer,"* %ld Hz",freq);
    }
    else
    {
         sprintf(buffer,"  %ld Hz",freq);
    }
    oledGotoYX( 2, 2 );
    oledPrint(buffer);
    
    
    oledGotoYX( 4, 2 );
    oledPrint("                     ");
    strcpy(buffer,"");
    if (val->current_selection==STEP)
    {
        sprintf(buffer,"* Step %d hz",step);
    }
    else
    {
         sprintf(buffer,"  Step %d hz",step);
    }
    
    oledGotoYX( 4, 2 );
    oledPrint(buffer);
    
    oledGotoYX( 6, 2 );
    oledPrint("                     ");
    strcpy(buffer,"");
    if (val->current_selection==BAND)
    {
        sprintf(buffer,"* Band %d m",band);
    }
    else
    {
         sprintf(buffer,"  Band %d m",band);
    }
    
    oledGotoYX( 6, 2 );
    oledPrint(buffer);
    
    
    
}

void Increment()
{
    
    switch(current_state.current_selection)
    {
        case BAND:
            IncBand(&current_state);
            break;
        case FREQ:
            IncFreq(&current_state);
            break;
        case STEP:
            IncStep(&current_state);
            break;
    }
    
    si5351_set_freq(SI5351_FREQ_MULT*GetFrequency(&current_state) , SI5351_CLK0);
    DisplayState(&current_state);
}

void Decrement()
{
    switch(current_state.current_selection)
    {
        case BAND:
            DecBand(&current_state);
            break;
        case FREQ:
            DecFreq(&current_state);
            break;
        case STEP:
            DecStep(&current_state);
            break;
    }
    
    si5351_set_freq(SI5351_FREQ_MULT*GetFrequency(&current_state) , SI5351_CLK0);
    DisplayState(&current_state);
    
}


int main(void) {
    
    int inputFreq=0;
    int oldInputFreq=0;
   
    
    rot.position=0;
    rot.counter=0;
    rot.counter_prev=0;
    rot.leftCallback=&Decrement;
    rot.rightCallback=&Increment;
 
    
    ResetState(&current_state);
    
    
    ADPCFG=0xFFFF; //set input capture pins to digital mode
     
    i2c1Reset();
     __delay_ms(500);
     i2c1Enable(100); 
    __delay_ms(500);
   
    
    
    
    oledInit();
    __delay_ms(200);
    oledClear();
    
    uint8_t ret =si5351_init(SI5351_CRYSTAL_LOAD_8PF, 0, FREQ_CORRECTION);
    ret=si5351_set_freq(SI5351_FREQ_MULT*GetFrequency(&current_state) , SI5351_CLK0);
    ret=si5351_read(SI5351_DEVICE_STATUS);
    
    si5351_drive_strength(SI5351_CLK0, SI5351_DRIVE_2MA);
    si5351_output_enable(SI5351_CLK0,1);
   
    
    
    /*Initialise input capture*/
    TRISDbits.TRISD0=1;  //set pin 10 as IC1 input
    IC1CONbits.ICSIDL=0;
    IC1CONbits.ICTMR=0; //use timer 3
    IC1CONbits.ICI=0b01; // Interrupt on every second capture event
    IC1CONbits.ICM=0b011; //  Capture mode, every  rising edg
    IEC0bits.IC1IE=1;
    
    
    //enable external interrupts
    IEC0bits.INT0IE=1;
    IEC1bits.INT2IE=1;
    TRISBbits.TRISB6=1; //Rotary encoder switch
    TRISBbits.TRISB7=1; //Rotary encoder clock
    TRISBbits.TRISB0=1; //Rotary encoder data
    ADPCFG = 0xFFFF; 
    
    TRISBbits.TRISB2=0; // TX/RX
    PORTBbits.RB2=0;
  
    
    //setup Timer3 as the internal clock , firing every 1ms.
     T3CONbits.TCKPS0=0;
     T3CONbits.TCKPS1=0;
     T3CONbits.TON=1;
     
     IEC0bits.T3IE=1;
    // IEC0bits.IC1IE=1;
    // PR3=6000;
     

     
    while(1)
    {
       
       inputFreq=0;            
       while(inputOn>0)
       {
            
            if (period>1000)
            {
                inputFreq=(int)(12000000/(float)period);
                if (osc_on==0)
                {
                    PORTBbits.RB2=1;
                    __delay_ms(50);
                    si5351_set_freq(SI5351_FREQ_MULT*(GetFrequency(&current_state)+inputFreq) , SI5351_CLK1);    
                    si5351_output_enable(SI5351_CLK1,1);
                    osc_on=1;
                }
                
                if (inputFreq!=oldInputFreq)
                {
                    si5351_set_freq(SI5351_FREQ_MULT*(GetFrequency(&current_state)+inputFreq) , SI5351_CLK1);
                }
                oldInputFreq=inputFreq;
            }
            __delay_ms(2);
           inputOn--;
           if (inputOn==0)
           {
               si5351_set_freq(SI5351_FREQ_MULT*(GetFrequency(&current_state)) , SI5351_CLK1);
               si5351_output_enable(SI5351_CLK1,0);
               __delay_ms(100);
               PORTBbits.RB2=0;
              __delay_ms(500);
           }
       }
       
       
       ScanEncoder(PORTBbits.RB0,PORTBbits.RB7,&rot);
       
       
        if (osc_on>0)
        {
            si5351_output_enable(SI5351_CLK1,0);
            PORTBbits.RB2=0;
            osc_on=0;
        }
       
       if (int0>0)
       {
           //button press
           ToggleSelection(&current_state);
           DisplayState(&current_state);
           int0=0;
       }

        //reset counters
        T3Counter=0;
           
    }
    
    
    return 0;
}
