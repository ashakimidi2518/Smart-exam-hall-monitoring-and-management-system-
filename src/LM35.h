//LM35.h
#ifndef _LM35_H
#define _LM35_H
#include "types.h"
f32 read_Lm35Degc(void);
f32 read_Lm35Degf(void);
void read_Lm35NT(f32 *tdegC,f32 *tdegF);
#endif

