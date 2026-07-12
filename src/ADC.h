//ADC.h
#ifndef _ADC_H
#define _ADC_H
#include "types.h"
void adc_Init(void);
void Read_adc(u32 CHNO,u32 *adcDval,f32 *ear);
#endif

