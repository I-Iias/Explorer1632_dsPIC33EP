/*
 * File:   Timer.c
 * Author: Matthias
 *
 * Created on 23. April 2019, 23:16
 */


#include "xc.h"
#include "Timer.h"
#include "Tasks.h"

FUNCTION_HANDLER handle = NULL;

void INIT_Timer1(void)
{
    T1CON            = 0;            //clear configuration register
    T1CONbits.TCS    = 0;            //Internal peripheral clock
    T1CONbits.TCKPS  = 1;            //prescaler 1:8       
    T1CONbits.TGATE  = 0;            //Gated time accumulation is disabled
    T1CONbits.TSIDL  = 0;            //Continue operation when device enters Idle mode
    TMR1             = 0;            //clear count register 
    PR1              = 8750;        //Periode | PRx = [(Fp/prescaler)*T] = 70MHz/8*1ms = 8750
    IFS0bits.T1IF    = 0;            //reset interrupt flag
    IPC0bits.T1IP    = 5;            //interrupt priority
    IEC0bits.T1IE    = 1;            //enable interrupt   
    T1CONbits.TON     = 1;            //1=0n 0=off
}

void RequestFunction_Timer1 (FUNCTION_HANDLER handle_new)
{
    handle = handle_new;
}

void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)       // Timer 1
{
    if(handle != NULL)
    {
        handle();
    }
    //Task_scheduler();
    IFS0bits.T1IF = 0;
}