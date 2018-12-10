/*
 * uart.c
 *
 * Created: 12/9/2018 5:36:45 PM
 *  Author: Mustafa El_Behidy
 */ 


#include "uart.h"

void uart_Init(uint16 Baud_rate)
{
	UCSRA |= (1<<U2X);                     // Asynchronous Speed Mode
	UCSRB |= (1<<RXEN) | (1<<TXEN);        // Enable RX and TX
	// URSEL must be one when writing UCSRC
	// character size 011 for 8-BIT data mode
	UCSRC |= (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);     
	//Baud Rate 9600  UBBR = (f_osc / ( 8 * BRR ) - 1) = 12
	UBRRH = 0;
	UBRRL = (uint8)((F_CPU / ( 8 * Baud_rate ) - 1));
}
void uart_Send_Byte(uint8 Data)
{
	// if UDRE is one, the buffer is empty. 
	// 0 if have new data to be transmitted then you can't load it with data now
	// Note: I can send data when transmitted buffer is empty
	while(!(UCSRA & (1<<UDRE)));   
	UDR = Data;
}

uint8 uart_Receive_Byte()
{
	// RXC is one as long as there are unread data in the receive buffer
	// and cleared by CPU when the receive buffer is empty
	// Note: I can Receive data when receive buffer is empty
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
void uart_Send_String(const uint8* Data)
{
	uint8 count = 0;
	while(Data[count] != '\0')
	{
		uart_Send_Byte(Data[count]);
		count++;
	}
}

void uart_Receive_String(uint8* str)
{
	uint8 count = 0;
	str[count] = uart_Receive_Byte();
	while (str[count] != '#')
	{
		count++;
		str[count] = uart_Receive_Byte();
	}
	str[count] = '\0';
}
