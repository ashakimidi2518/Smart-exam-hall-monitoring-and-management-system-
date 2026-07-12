//lcd.h
#ifndef _LCD_H
#define _LCD_H
#include "types.h"
void writeLcd(u8 byte);
void cmdLcd(u8 opcode);
void lcd_Init(void);
void charLcd(u8 ascii);
void strLcd(s8 *str);
void U32Lcd(u32 num);
void S32Lcd(s32 num);
void F32Lcd(f32 fnum,u32 ndp);
void buildCgram(s8 *p,u32 nbytes);
#endif

