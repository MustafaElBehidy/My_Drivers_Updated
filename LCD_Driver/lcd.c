/*
 * lcd.c
 *
 * Created: 12/8/2018 7:11:07 PM
 *  Author: Mustafa El_Behidy
 */ 


#include "lcd.h"

void lcd_Init()
{
	#ifdef EIGHT_BIT_MODE 
		LCD_DATA_PORT_DDR = 0xFF;      //set data port as output
		LCD_CONTROL_PORT_DDR |= (1<<RS) | (1<<EN) | (1<<R_W);  //configure pin(RS,R/W,EN) as output Mode
	#endif
	
	#ifdef FOUR_BIT_MODE
	
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_DDR = 0xF0;
		#else
			LCD_DATA_PORT_DDR = 0x0F;
		#endif
		LCD_CONTROL_PORT_DDR |= (1<<RS) | (1<<EN) | (1<<R_W);  //configure pin(RS,R/W,EN) as output Mode
	#endif
	lcd_Send_Command(Two_lines_LCD_Eight_Bit_Mode);
	lcd_Send_Command(Display_on_Cursor_on);
	lcd_Send_Command(Clear_Command);
}
/*
to send command
RS = 0 Instruction Mode     R/W = 0 Writing Mode
delay 
Enable
delay
send command on lcd_data_port
delay
disable
delay
*/
void lcd_Send_Command(uint8_t command)
{
	LCD_CONTROL_PORT_OUT &= ~((1<<RS) | (1<<R_W));  //RS = 0 Instruction Mode     R/W = 0 Writing Mode
	_delay_ms(1);
	LCD_CONTROL_PORT_OUT |= (1<<EN);                // Enable
	_delay_ms(1);
	#ifdef EIGHT_BIT_MODE
		LCD_DATA_PORT_OUT = command;                    // Send Command
		_delay_ms(1);
		LCD_CONTROL_PORT_OUT &= ~(1<<EN);               //Disable
		_delay_ms(1);
	#endif
	
	#ifdef FOUR_BIT_MODE
		#ifdef UPPER_PORT_PINS 
			LCD_DATA_PORT_OUT = (command & 0xF0);
		#else
			LCD_DATA_PORT_OUT = ((command >> 4) & 0x0F);
		#endif
		_delay_ms(1);
		LCD_CONTROL_PORT_OUT &= ~(1<<EN);               //Disable
		_delay_ms(1);
		LCD_CONTROL_PORT_OUT |= (1<<EN);                // Enable
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS 
			LCD_DATA_PORT_OUT = ((command << 4) & 0xF0);
		#else
			LCD_DATA_PORT_OUT = (command & 0x0F);
		#endif
		_delay_ms(1);
		LCD_CONTROL_PORT_OUT &= ~(1<<EN);              // Disable
		_delay_ms(1);
	#endif	
}
void lcd_Display_Character(uint8_t character)
{
	Set_Bit(LCD_CONTROL_PORT_OUT, RS);   // RS = 1 Data Mode
	CLEAR_BIT(LCD_CONTROL_PORT_OUT, R_W);    // R/W = 0  Write Mode
	_delay_ms(1);
	Set_Bit(LCD_CONTROL_PORT_OUT, EN);     // Enable LCD
	_delay_ms(1);
	#ifdef EIGHT_BIT_MODE 
		LCD_DATA_PORT_OUT = character;      // Send Data
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_PORT_OUT, EN);   // Disable LCD
		_delay_ms(1);
	#endif
	
	#ifdef FOUR_BIT_MODE
		#ifdef UPPER_PORT_PINS
			LCD_DATA_PORT_OUT = (character & 0xF0);
		#else
			LCD_DATA_PORT_OUT = ((character >> 4) & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_PORT_OUT, EN);   // Disable LCD
		_delay_ms(1);
		Set_Bit(LCD_CONTROL_PORT_OUT, EN);      // Enable LCD
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS 
			LCD_DATA_PORT_OUT = ((character << 4) & 0xF0);
		#else
			LCD_DATA_PORT_OUT = (character & 0x0F);
		#endif
		_delay_ms(1);
		CLEAR_BIT(LCD_CONTROL_PORT_OUT, EN);    // Disable LCD
		_delay_ms(1);
	#endif
}
void lcd_Dislay_String(const char* str)
{
	uint8_t i = 0;
	while (str[i] != '\0')
	{
		lcd_Display_Character(str[i]);
		i++;	
	}
}
void lcd_Dislay_String_Row_Col(const char* str, uint8_t row, uint8_t col)
{
	lcd_goto_Row_COl(row,col);        //go to the required position
	lcd_Dislay_String(str);           // display the string
}
// this function valid for all type of LCD 1,2 and 4 rows
void lcd_goto_Row_COl(uint8_t Row, uint8_t Col)
{
	uint8_t address = 0;
	switch(Row)
	{
		case 0:
			address = Col + 0x00;
			break;
		case 1:
			address = Col + 0x40;
			break;
		case 2:
			address = Col + 0x10;
			break;
		case 3:
			address = Col + 0x50;
			break;
	}
	//write to specific address in LCD
	lcd_Send_Command(address | Force_Cursor_To_beginning_of_1st_line);  // 0x80 + address   
}
void lcd_Clear_Screen()
{
	lcd_Send_Command(Clear_Command);
}

void lcd_Integer_To_String(int Data)
{
	char buff[16];
	itoa(Data,buff,10);
	lcd_Dislay_String(buff);
}
