/*******************************************************************************
Copyright 2016 Microchip Technology Inc. (www.microchip.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "bsp/adc.h"
#include "bsp/lcd.h"
#include "bsp/timer_1ms.h"
#include "bsp/buttons.h"
#include "bsp/leds.h"
#include "bsp/rtcc.h"
 
#include "io_mapping.h"

#include "Initialize.h"
#include "Tasks.h"
#include "Timer.h"
#include "adc_dma.h"
#include "EEPROM_emulation.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************
extern void SYS_Initialize ( void ) ;
static void TimerEventHandler( void );

static RTCC_DATETIME time;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    uint16_t adcResult;
    
    /* Call the System Initialize routine*/
    SYS_Initialize ( );
    Hardware_Init(); 
    
    /* To determine how the LED and Buttons are mapped to the actual board
     * features, please see io_mapping.h. */
    LED_Enable ( LED_BLINK_ALIVE );
    LED_Enable ( LED_BUTTON_PRESSED );
    LED_Enable ( LED_STATUS );

    BUTTON_Enable ( BUTTON_DEMO );
    BUTTON_Enable ( BUTTON_WR_EEPROM );
    BUTTON_Enable ( BUTTON_RD_EEPROM );
    
    Init_EEPROM();
    
    /* Get a timer event once every 100ms for the blink alive. */
    TIMER_SetConfiguration ( TIMER_CONFIGURATION_1MS );
    TIMER_RequestTick( &TimerEventHandler, 100 );
    
    /* The TIMER_1MS configuration should come before the RTCC initialization as
     * there are some processor modules that require the TIMER_1MS module to be
     * configured before the RTCC module, as the RTCC module is emulated using
     * the TIMER_1MS module. */
    time.bcdFormat = false;
    RTCC_BuildTimeGet( &time );
    RTCC_Initialize( &time );

    // old adc functions
//    ADC_SetConfiguration ( ADC_CONFIGURATION_DEFAULT );
//    ADC_ChannelEnable ( ADC_CHANNEL_POTENTIOMETER );
    // new adc functions
    ADC_ChnEnable();
    Init_ADC ();
    Init_DMA2();
    
    /* Clear the screen */
    printf( "\f" );   
    
    // Task scheduler moved to Timer1 interrupt
    //Task_scheduler();
    RequestFunction_Timer1 ( &Task_scheduler );
    
    while ( 1 )
    {
        
        // old adc functions
//        adcResult = ADC_Read10bit( ADC_CHANNEL_POTENTIOMETER );
        // new adc functions
        adcResult = getADCvalue (ADC_CHN_POTENTIOMETER);
        uint16 Temp_adc = 0;
        Temp_adc = getADCvalue (ADC_CHN_TEMPERATURE_SENSOR);
        
        RTCC_TimeGet( &time );
        
        if(BUTTON_IsPressed( BUTTON_WR_EEPROM ) == true)
        {
            uint16 check;
            check = EEPROM_write(adcResult, EEPROM_addr_Pot);
            check = 0;
        }
        
        if(BUTTON_IsPressed( BUTTON_RD_EEPROM ) == true)
        {
            // printf takes nearly 10ms to execute
            printf( "Time %02d:%02d:%02d   EEPROM = %4d   \r\n", 
                time.hour, 
                time.minute, 
                time.second, 
                EEPROM_read(EEPROM_addr_Pot)
              );
        }
        else
        {
            // printf takes nearly 10ms to execute
            printf( "Time %02d:%02d:%02d   Pot = %4d, %4d\r\n", 
                time.hour, 
                time.minute, 
                time.second, 
                adcResult,
                Temp_adc
              );
        }
        

        /* To determine how the LED and Buttons are mapped to the actual board
         * features, please see io_mapping.h. */
        if(BUTTON_IsPressed( BUTTON_DEMO ) == true)
        {
            LED_On( LED_BUTTON_PRESSED );
        }
        else
        {
            LED_Off( LED_BUTTON_PRESSED );
        }
        uint16 time_count = TMR1;

        time_count = TMR1-time_count;
        time_count = 0;
    }
}

static void TimerEventHandler(void)
{    
    LED_Toggle( LED_BLINK_ALIVE );
}
