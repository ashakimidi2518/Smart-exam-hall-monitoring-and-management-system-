//ADC_defines.h
#ifndef _ADC_DEFINES_H
#define _ADC_DEFINES_H
#include "TEST_RTC_defines.h"
#define ADCLK    3000000
#define DIVIDER  ((PCLK/ADCLK)-1)
#define ADC_CLK_DIV (DIVIDER<<8)
#define PDN_BIT     (1<<21)
#define START_CONV  (1<<24)
#define CH0 (1<<0)
#define CH1 (1<<1)
#define CH2 (1<<2)
#define CH3 (1<<3)
#define RESULT   6
#define DONE_BIT 31
#endif

