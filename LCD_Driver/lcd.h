/*
 * lcd.h
 *
 * Created: 12/8/2018 7:10:51 PM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "common_Macros.h"
#include "micro_config.h"
#include <stdlib.h>

#define RS PD4
#define R_W PD5
#define EN PD6
#define LCD_DATA_PORT_OUT PORTC 
#define LCD_DATA_PORT_DDR DDRC
#define LCD_CONTROL_PORT_OUT PORTD
#define LCD_CONTROL_PORT_DDR DDRD

//#define FOUR_BIT_MODE 4
#define EIGHT_BIT_MODE 8
#define UPPER_PORT_PINS
//#define LOWER_PORT_PINS
#define Two_lines_LCD_Eight_Bit_Mode          0x38
#define Force_Cursor_To_beginning_of_1st_line 0x80
#define Force_Cursor_To_beginning_of_2nd_line 0xC0
#define Two_lines_LCD_FOUR_Bit_Mode           0x28
#define Clear_Command                         0x01
#define Display_on_Cursor_on                  0x0E
#define Display_on_Cursor_off                 0x0C
#define Display_off_Cursor_on                 0x0A
#define Display_off_Cursor_off                0x08
void lcd_Init();
void lcd_Send_Command(uint8_t command);
void lcd_Display_Character(uint8_t character);
void lcd_Dislay_String(const char* str);
void lcd_Dislay_String_Row_Col(const char* str, uint8_t row, uint8_t col);
void lcd_goto_Row_COl(uint8_t Row, uint8_t Col);
void lcd_Clear_Screen();
void lcd_Integer_To_String(int Data);
#endif /* LCD_H_ */