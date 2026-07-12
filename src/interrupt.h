// interrupt.h
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "types.h"
extern vu8 menu_flag;
extern vu8 pause_flag;
void enable_Eint0(void);
void enable_Eint1(void);
#endif   // __INTERRUPT_H__

