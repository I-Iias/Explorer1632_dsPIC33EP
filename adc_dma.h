/* 
 * File:   adc_dma.h
 * Author: Matthias Leeb
 *
 * Created on 20. Mai 2019, 19:33
 */

#ifndef ADC_DMA_H
#define	ADC_DMA_H

#include "types.h"
#include <xc.h>

#define ADC_CHN_POTENTIOMETER       0
#define ADC_CHN_TEMPERATURE_SENSOR  1

#define NumSamples 128

extern uint16 BufferA[NumSamples];
extern uint16 BufferB[NumSamples];

void Init_ADC (void);
void Init_DMA2(void);
uint16 getADCvalue (uint8 channel);
boolean ADC_ChnEnable(void);



#endif	/* ADC_DMA_H */

