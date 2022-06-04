

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
#include "./headers/oled.h"



volatile int T3Counter;
volatile long T1Counter;



///Timer3 ISR
void __attribute__((__interrupt__, __auto_psv__)) _T3Interrupt(void)
{
    // Clear Timer 1 interrupt flag
    T3Counter++;
    
    _T3IF=0;
 
}

//Timer1 ISR
void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void)
{
   
   T1Counter++;
    
     _T1IF=0;
    
}


int main(void) {
    
    
    long frequency;
    float fdisplay;
    char str_buffer[20];
  
    
    TRISB=0;
    ADPCFG=0xFFFF;
     
    i2c1Reset();
     __delay_ms(1000);
     i2c1Enable(100); 
    __delay_ms(1000);
   
      
    oledInit();
    oledClear();
    oledGotoYX( 2, 0 );
    oledPrint("Initialising..");
    
    __delay_ms(2000);
    oledClear();
    
    //setup Timer3 as the internal clock , firing every 1ms.
     T3CONbits.TCKPS0=0;
     T3CONbits.TCKPS1=0;
     T3CONbits.TON=1;
     
     IEC0bits.T3IE=1;
     PR3=6000;
     
     //setup Timer1 as the external event counter
     TRISCbits.TRISC14=1;
     T1CONbits.TCKPS = 0;
     T1CONbits.TGATE = 0;
     T1CONbits.TCS=1;
     T1CONbits.TON=1;
     IEC0bits.T1IE=1;
     
     
    while(1)
    {
        if (T3Counter>=2000)
        {
            //stop measurement
            T1CONbits.TON=0;
            T3CONbits.TON=0;
            
            //activity light
            PORTBbits.RB0=~PORTBbits.RB0;
            
            //Frequency measurement code
            frequency= TMR1 + T1Counter*65536; 
            
           
            if (frequency>1000000)
            {
                 fdisplay=frequency/1000000.0f;
                 sprintf(str_buffer,"%0.5f Mhz",fdisplay);
            }
            else if (frequency>10000)
            {
                fdisplay=frequency/1000.0f;
                sprintf(str_buffer,"%0.4f Khz",fdisplay);
            }
            else
            {
                 sprintf(str_buffer,"%ld Hz",frequency);
            }
            
           
            oledGotoYX( 1, 0 );
            oledPrint("              ");
            oledGotoYX( 1, 0 );
            oledPrint(str_buffer);
            
           //reset counters
            T3Counter=0;
            T1Counter=0;
            TMR1=0;
            TMR3=0;
            
            //start measurement again
            T1CONbits.TON=1;
            T3CONbits.TON=1;
            
        }
        
       
        
    }
    
    
    return 0;
}
