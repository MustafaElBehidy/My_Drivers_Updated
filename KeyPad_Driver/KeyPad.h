/*
 * KeyPad.h
 *
 * Created: 12/8/2018 3:58:41 PM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "micro_config.h"
#include "common_Macros.h"

#define N_COL 4      // Number of columns
#define N_ROW 4      // Number of Rows

#define KeyPad_Port_Out PORTA        // KeyPad Port   
#define KeyPad_Port_In PINA          // 
#define KeyPad_Port_DDR DDRA

/* function to make loop on cols and rows to check if key is pressed
   and check if keypad is 3*4 or 4*4
   and handle each keypad by using its function
*/ 
uint8_t KeyPad_Get_Key_Pressed();              
// function to deal with Keypad 3*4 and read the key
uint8_t KeyPad_4x3_AdjustKeyNumber(uint8_t button_number);
// function to deal with Keypad 4*4 and read the key 
uint8_t KeyPad_4x4_AdjustKeyNumber(uint8_t button_number);


#endif /* KEYPAD_H_ */