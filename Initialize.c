/*
 * File:   Initialize.c
 * Author: Matthias Leeb
 *
 * Created on 23. April 2019, 20:37
 */


#include <xc.h>

#include "types.h"
#include "Initialize.h"


//******************************************************************************
//Global Variables
//******************************************************************************


//******************************************************************************
//*name     :Hardware_Init
//*details  :Initialize peripheral modules
//*param    :void
//*return   :void
//******************************************************************************

void Hardware_Init (void)
{
    INIT_OSC ();
//    INIT_Timer1();

//    Init_ADC ();
//    Init_DMA2 ();           // for ADC
 
 
    
}




uint16 OscillatorSource = 0;
uint16 PllInputSource = 2;
uint16 PllOutputDivider = 0;
uint16 PllInputDivider = 0;
uint16 PllMultiplikator = 0;

void INIT_OSC(void)
{
     // clock switch sequence (see Oscillator Section 7.13.2 
    // make sure Configuration bits (pragma) are set correctly
    
    //current oscillator source
    OscillatorSource = OSCCONbits.COSC;
    
    //OSCCONbits.NOSC = 0b011;
    __builtin_write_OSCCONH(0x03);   // set to Primary Oscillator with PLL
    //OSCCONbits.OSWEN = 1;
    __builtin_write_OSCCONL(OSCCON | 0x01);      // initiate the oscillator switch

    while (OSCCONbits.OSWEN != 0){};      //wait until clock switch was successfull
        
    
    // system clock = 70MHz -> FPLLO = 140MHz

    CLKDIVbits.PLLPRE = 0b00000;        // divide by 2 (N1 = 2, default)
    CLKDIVbits.PLLPOST = 0b01;          // divide by 4 (N2 = 4, default)
    PLLFBDbits.PLLDIV = 140-2;          // M = 140
    
    
    
    //tune FRC oscillator, if FRC is used
    //OSCTUN = 0;
    //disable Watchdog Timer
    //WDTCONbits.ON = 0;              //disable watchdog timer
    
    
    OscillatorSource = OSCCONbits.COSC;

}

