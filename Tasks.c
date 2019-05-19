/*
 * File:   Tasks.c
 * Author: Matthias
 *
 * Created on 22. April 2019, 20:04
 */

#include "Tasks.h"
#include "io_mapping.h"




void Task_scheduler (void)
{
    // function variables
    static uint16 Cnt1ms  = 0;
    static uint16 Cnt10ms  = 0;
    static uint16 Cnt50ms  = 0;
    static uint16 Cnt100ms = 0;
    static uint16 Cnt500ms = 0;
    static uint16 Cnt1s    = 0;
    
    Cnt1ms++;
    Task_1ms();

    if(Cnt1ms >= 10)
    {   
        Cnt1ms = 0; 
        Cnt10ms++;
        Task_10ms();
    }
    if(Cnt10ms >= 5)
    {   
        Cnt10ms = 0;  
        Cnt50ms++;
        Task_50ms();
    }
    if(Cnt50ms >= 2)
    {   
        Cnt50ms = 0;  
        Cnt100ms++;
        Task_100ms();
    }
    if(Cnt100ms >= 5)
    {   
        Cnt100ms = 0; 
        Cnt500ms++;
        Task_500ms();
    }
    if(Cnt500ms >= 2)
    {   
        Cnt500ms = 0; 
        Cnt1s++;
        Task_1s();
    }
    if(Cnt1s >= 10)
    {   
        Cnt1s = 0;
        Task_10s();
    }
}


void Task_1ms(void)
{

}

void Task_10ms(void)
{

}

void Task_50ms(void)
{
 
}

void Task_100ms(void)
{     
    LED_Toggle( LED_STATUS );
}
void Task_500ms(void)
{
    //LED_Toggle( LED_STATUS );
}

void Task_1s(void)
{
    
}

void Task_10s(void)
{

}
