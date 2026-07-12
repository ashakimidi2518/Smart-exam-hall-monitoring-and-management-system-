//kpm.h
#ifndef _KPM_H
#define _KPM_H
#include "types.h"
void kpm_Init(void);
u32 Colscan(void);
u32 RowCheck(void);
u32 ColCheck(void);
u32 keyScan(void);
u32 ReadNum(u8 *);
u32 keyInput(u8 nodigit,u8 *cancel);
u32 passInput(u8 nodigit,u8 *cancel);
u32 menu_sel(void);
#endif

