//TEST_RTC_defines.h
#ifndef _TEST_RTC_DEFINES_H
#define _TEST_RTC_DEFINES_H
// Select CPU
#define LPC2129 1
#define LPC2148 2
#define CPU LPC2129      // Change to LPC2148 if using LPC2148
// Clock Definitions
#define FOSC 12000000
#define CCLK (FOSC * 5)
#define PCLK (CCLK / 4)
// RTC Prescaler
#define PREINT_VAL  ((PCLK / 32768) - 1)
#define PREFRAC_VAL (PCLK - ((PREINT_VAL + 1) * 32768))
// CCR Register Bits
#define RESET_RTC   (1<<1)
#define ENABLE_RTC  (1<<0)
#define RTC_CLK_SRC ((1<<4) | (1<<0))
#endif
