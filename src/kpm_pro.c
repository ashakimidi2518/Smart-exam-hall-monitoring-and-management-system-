//kpm.c
#include "types.h"              
#include <lpc21xx.h>             
#include "kpm_defines.h"     
#include "delay.h" 
#include "kpm.h"
#include "lcd.h"
#include "lcd_def.h"
u8 KpmLUT[4][4] =	{{'1','2','3','A'},   // row 0 key characters
			             {'4','5','6','B'},   // row 1 key characters
			             {'7','8','9','C'},  // row 2 key characters
				           {'c','0','=','D'}}; // row 3 key characters ('c' = cancel, '=' = enter)
void kpm_Init(void)
{
	//cfg rows (p1.16-p1.19) as o/p
	IODIR1 |= 15<<ROW0; // set 4 row pins (P1.16-P1.19) as output, keep other bits unchanged
}
u32 Colscan(void)
{
	 // shift column pins to bit0, mask 4 bits; if any col bit is 0 (pressed), value < 15
	if(((IOPIN1>>COL0)&15)<15) 
	{
		// 0 = a key is pressed (at least one column pulled low)
	  return 0; 
	}
	else 
	{
		 // 1 = no key pressed (all columns read high)
	  return 1;
  }
}
u32 RowCheck(void)
{
	// variable to hold the row index being tested
	u32 rno;  
 // loop through all 4 rows	
	for(rno=0;rno<4;rno++) 
	{
		 // clear all row bits, then drive only row 'rno' low, others high
		IOPIN1=(IOPIN1 &~ (0xFF<<ROW0))|((~(1<<rno))<<ROW0);
 // check if a key press is detected in this row		
		if(Colscan()==0)  
		{
			// stop scanning, 'rno' now holds the active row
			break;    
		}
	}
	//make row as defaults
	IOCLR1 = 15<<ROW0;   // clear (drive low) all row pins to restore default state
	 // return the detected row number (or 4 if none found)
	return rno;       
}
u32 ColCheck(void)
{
	 // variable to hold the column index being tested
		u32 cno;   
   // loop through all 4 columns	
		for(cno=0;cno<4;cno++)   
		{
		// check if this specific column pin reads low (pressed)
		if(((IOPIN1>>(COL0+cno))&1)==0) 
		// stop scanning, 'cno' now holds the active column
			break;                      
	}
  // return the detected column number (or 4 if none found)
	return cno; 
}

u32 keyScan(void)
{
	u32 rno,cno,key;        // row number, column number, and resulting key value
	//wait for switch press
	while(Colscan());   
	//find rno
	rno=RowCheck();          
	//find cno
	cno = ColCheck();              
	//get key value from KPMLUT[][]
	key = KpmLUT[rno][cno];        
	//wait for switch release
	while(!Colscan());             
	//return keyvalue
	return key;                    
}
u32 ReadNum(u8 *endop)
{
	 // holds the currently scanned key
	u8 key;   
	u32 sum=0;	                  
	while(1)                      
	{
		// wait for and read a keypress
		key = keyScan(); 
    // small debounce delay after key scan		
		delay_ms(100);	
		// check if the key is a digit
		if(key>='0' && key<='9')    
		{
			 // shift existing digits left and add new digit
			sum = (sum*10)+(key-'0');//'0' = 48  
		}		
	else
	{
		 // store the non-digit terminating key in output parameter
		*endop = key; 
    // exit the loop since input is complete		
		break;                      
	}
  }
	return sum;                    
}
u32 keyInput(u8 nodigit,u8 *cancle)
{
	u32 value=0;                
	u8 cnt=0;                       
	u32 key;                       
	*cancle =0;  
   //it iterates upto number of digits you want to enter	
	while(cnt <= nodigit) 
	{
		// wait for and read a keypress
		key = keyScan();            
		//	delay_ms(200);		
		//here c is for exit 
		 // check if cancel key was pressed
		if(key == 'c')               
		{
			*cancle = 1;               
			return 0;                    
		}
		  // check if delete/backspace key was pressed
		else if(key == 'D')          
		{
			 // only delete if at least one digit has been entered
			if(cnt>0)                   
			{
				cnt--;                      // decrement digit counter
				value = value/10;     //removes the last entered value   // drop the last digit from value
				//move lcd cur left and erase char in lcd
				cmdLcd(MOV_CUR_LEFT);
        // overwrite the character with a blank space				
				charLcd(' ');   
        // move LCD cursor left again to position for next entry				
				cmdLcd(MOV_CUR_LEFT);       
			}
		}		
		//stores the entered values in one variable
		else if(cnt < nodigit)         
		{
			 // check if key is a digit
			if(key >= '0' && key <='9') 
			{
			// append the new digit to value
			value = (value*10) + (key - '0');	
		 // increment digit counter
			cnt++;   
     // display the digit on the LCD				
			charLcd(key);               
			}
		 }
		// check if enter/confirm key was pressed
	else if(key == '=')              
	{
		break ;                      
	}
	}
	return value;                
}
u32 passInput(u8 nodigit,u8 *cancle)
{
	u32 value=0;                    
	u8 cnt=0;                      
	u32 key;                        
	*cancle =0;  
  //it iterates upto number of digits you want to enter	
	while(cnt <= nodigit) 
	{
		//waiting for key scan
		key = keyScan();              
	//	delay_ms(200);	
		//here c is for exit 
		if(key == 'c')                
		{
			// set cancel flag
			*cancle = 1;                 
			return 0;                    
		}
		// check if delete/backspace key was pressed
		else if(key == 'D')            
		{
			// only delete if at least one digit has been entered
			if(cnt>0)                    
			{
				 // decrement digit counter
				cnt--;     
       //removes the last entered value   // drop the last digit from value				
				value = value/10;
				//move lcd cur left and erase char in lcd
				cmdLcd(MOV_CUR_LEFT); 
				// overwrite the character with a blank space				
				charLcd(' ');  
				// move LCD cursor left again to position for next entry				
				cmdLcd(MOV_CUR_LEFT);        
			}
		}	
		//stores the entered values in one variable
		else if(cnt < nodigit)         // only accept more digits if under the digit limit
		{
			if(key >= '0' && key <='9')  
			{
				// append the new digit to value
			value = (value*10) + (key - '0');  
      // increment digit counter				
			cnt++;    
			// display '*' on LCD instead of actual digit (password masking)				
			charLcd('*');                
			}
		 }
		// check if enter/confirm key was pressed
	else if(key == '=')              
	{
		break ;                     
	}
	}
	return value;                 
}
//it returns key value 1,2,3,4..
u32 menu_sel(void) 
{
	u32 key;                     
	do
	{
		// wait for and read a keypress
	key = keyScan(); //scans the input from keypad and stores in the key variables   
	// small debounce delay after key scan
	delay_ms(100);   
		// repeat until key is a digit character
	}while(key < '0' || key >'9'); //accepts only digit values  
	 // convert character digit to numeric value and return
	return key-'0';               
}


