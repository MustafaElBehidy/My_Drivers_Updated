/*
 * KeyPad.c
 *
 * Created: 12/8/2018 3:58:52 PM
 *  Author: Mustafa El_Behidy
 */ 

#include "KeyPad.h"

uint8_t KeyPad_Get_Key_Pressed()
{
	uint8_t row,col;        // to make loop on cols and rows
	while (1)
	{
		for (col = 0; col < N_COL; col++)      // columns loop
		{
			// make all pins input except the dedicated col will be output
			KeyPad_Port_DDR = (0b00010000<<col);   
			for (row = 0; row < N_ROW; row++)
			{
				/* 
				all pins take one Value 1 to be pulled up except the dedicated 
				col that is output will take zero value 
				*/
				KeyPad_Port_Out = (~(0b00010000<<col));     
				if (BIT_IS_CLEAR(KeyPad_Port_In,row))      // check if key is pressed
				{
					if (N_COL == 3)      //#if
					{
						// if 3*4 keyPad will use this function to return the dedicatrd Value
						return KeyPad_4x3_AdjustKeyNumber((row*N_COL) + col + 1 );   
					}
					else if(N_COL == 4)    //#elif
					{
						// if 4*4 keyPad will use this function to return the dedicatrd Value
						return KeyPad_4x4_AdjustKeyNumber((row*N_COL) + col + 1 );   
					}
					//#endif
				}
			}
		}
	}
}
//#if (N_COL == 3)
uint8_t KeyPad_4x3_AdjustKeyNumber(uint8_t button_number)
{
	switch(button_number)
	{
		case 10:
			return '*';
			break;
		case 11:
			return 0;
			break;
		case 12:
			return '#';
			break;
		default:
			return button_number;
	}
}
//#elif (N_COL == 4)
unsigned char KeyPad_4x4_AdjustKeyNumber(uint8_t button_number)
{
	switch(button_number)
	{
	case 1:
		return 7; break;
	case 2:
		return 8; break;
	case 3: 
		return 9; break;
	case 4:
		return '%'; break;
	case 5:
		return 4; break;
	case 6:
		return 5; break;
	case 7:
		return 6; break;
	case 8:
		return '*'; break;
	case 9:
		return 1; break;
	case 10:
		return 2; break;
	case 11:
		return 3; break;
	case 12:
		return '-'; break;
	case 13:
		return 13; break;    //ASCII for ENTER
	case 14:
		return 0; break;
	case 15:
		return '='; break;
	case 16:
		return '+'; break;
	default :
		return button_number;
	}
}
//#endif