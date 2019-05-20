/* 
 * File:   adc_dma.c
 * Author: Matthias Leeb
 *
 * Created on 20. Mai 2019, 19:33
 */



#include "adc_dma.h"


// global varialbes
uint16 BufferA[NumSamples];
uint16 BufferB[NumSamples];
uint16 ADC_value = 0;
volatile uint8 waitDMAinterrupt = 0;

void Init_ADC (void)
{
    AD1CON1bits.FORM = 0;       // Data Output Format: unsigned integer
    AD1CON1bits.SSRCG = 0;
    AD1CON1bits.SSRC = 7;       // Internal Counter (SAMC) ends sampling and starts conversion
//    AD1CON1bits.ASAM = 1;       // ADC Sample Control: Sampling begins immediately after
     // conversion
    AD1CON1bits.AD12B = 1;      // 12-bit ADC operation
    AD1CON1bits.SIMSAM = 0;     // Sequential sampling of channels
    AD1CON2bits.CHPS = 0;       // read as 0 in 12bit mode
    AD1CON3bits.ADRC = 0;       // ADC Clock is derived from Systems Clock
    AD1CON3bits.SAMC = 20;       // Auto Sample Time = 20 * TAD
    AD1CON3bits.ADCS = 6;       // ADC Conversion Clock TAD = TCY * (ADCS + 1) = (1/70M) * 7 =
     // 100 ns (10 MHz)
     // ADC Conversion Time for 12-bit Tconv = 20 * TAD = 2 µs (500 kHz)
    // not sure about ADDMABM
    AD1CON1bits.ADDMABM = 0;
//    AD1CON1bits.ADDMABM = 1;    // DMA buffers are built in conversion order mode
    AD1CON2bits.SMPI = 0;       // SMPI must be 0 for DMA
    //AD1CHS0/AD1CHS123: Analog-to-Digital Input Select Register
    AD1CHS0bits.CH0SA = 0;      // MUXA +ve input selection (AIN0) for CH0
    AD1CHS0bits.CH0NA = 0;      // MUXA -ve input selection (VREF-) for CH0
    AD1CHS123bits.CH123SA = 0;  // MUXA +ve input selection (AIN0) for CH1
    AD1CHS123bits.CH123NA = 0;  // MUXA -ve input selection (VREF-) for CH1

    IFS0bits.AD1IF = 0;         // Clear the Analog-to-Digital interrupt flag bit
    IEC0bits.AD1IE = 0;         // Do Not Enable Analog-to-Digital interrupt
    AD1CON1bits.ADON = 1;       // Turn on the ADC
    
    
}

void Init_DMA2(void)
{
    DMA2CONbits.AMODE = 0;      // Configure DMA for Register indirect with post increment
    DMA2CONbits.MODE = 2;       // Configure DMA for Continuous Ping-Pong mode -> switch between STA and STB
    DMA2PAD = (int)&ADC1BUF0;
    DMA2CNT = (NumSamples-1);      // number of samples before interrupt
    DMA2REQ = 13;               // ADC1 Convert Done (ADC1BUF0)
    DMA2STAH = 0;
    DMA2STAL = __builtin_dmaoffset(BufferA);
    DMA2STBH = 0;
    DMA2STBL = __builtin_dmaoffset(BufferB);
    IFS1bits.DMA2IF = 0; //Clear the DMA interrupt flag bit
    IEC1bits.DMA2IE = 1; //Set the DMA interrupt enable bit
    DMA2CONbits.CHEN = 1;
    
}

void __attribute__((__interrupt__, no_auto_psv)) _DMA2Interrupt(void)
{
    AD1CON1bits.DONE = 0;
    AD1CON1bits.SAMP = 0;
    AD1CON1bits.ASAM = 0;           // Stop sampling
//    AD1CON1bits.ADON = 0;       // Turn off the ADC
    IEC1bits.DMA2IE = 0; //Set the DMA interrupt enable bit
    // check which channel was used
    if (DMAPPSbits.PPST2 == 0) // channel A selected
    {
        ADC_value = (BufferA[0]+BufferA[1]);
    }
    else
    {
        ADC_value = (BufferB[0]+BufferB[1]);
    }
    waitDMAinterrupt = 1;
    IFS1bits.DMA2IF = 0; //Clear the DMA interrupt flag bit
}

uint16 getADCvalue (uint8 channel)
{
    AD1CHS0bits.CH0SA = channel;
    waitDMAinterrupt = 0;
//    AD1CON1bits.ADON = 1;       // Turn on the ADC
    IEC1bits.DMA2IE = 1; //Set the DMA interrupt enable bit
    AD1CON1bits.ASAM = 1;           // Start sampling
    
    uint16 DMA_register = 0;
    // wait for DMA transfer to finish
    while(!waitDMAinterrupt)
    {
        DMA_register = 1;
    }
    return ADC_value;
}

boolean ADC_ChnEnable(void)
{
    // ADC_CHN_POTENTIOMETER
    ANSELAbits.ANSA0  = 1 ;
    TRISAbits.TRISA0 = 1 ;
    // ADC_CHN_TEMPERATURE_SENSOR
    ANSELAbits.ANSA1 = 1 ;
    TRISAbits.TRISA1 = 1 ;
    return TRUE;
}