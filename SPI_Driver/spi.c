/*
 * spi.c
 *
 * Created: 12/10/2018 11:41:45 AM
 *  Author: Mustafa El_Behidy
 */ 


#include "spi.h"

void spi_Master_Init()
{
	/*
		SCK  Output  PB7
		MOSI Output  PB5
		SS   Output  PB4
		MISO Input   PB6
	*/
	DDRB |= (1<<PB4) | (1<<PB5) | (1<<PB7);
	DDRB &= ~(1<<PB6);
	SPCR |= (1<<MSTR);        // Master Mode
	// SPE Enable SPI
	SPCR |= (1<<SPE);
	// F_OSC / 128 SPR1:0 11
	//SPCR |= (1<<SPR1) | (1<<SPR0);
}
void spi_Slave_Init()
{
	/*
		SCK   Input
		MOSI  Input
		SS    Input
		MISO  Output
	*/
	DDRB &= ~((1<<PB4) | (1<<PB5) | (1<<PB7));
	DDRB |= (1<<PB6);
	// SPE Enable SPI
	SPCR |= (1<<SPE);
	// F_OSC / 128 SPR1:0 11
	//SPCR |= (1<<SPR1) | (1<<SPR0);
}
void spi_Send_Byte(uint8 data)
{
	// When a serial transfer is complete, the SPIF Flag is set.
	// a serial transfer include Transmit and Receive 
	SPDR = data;                  // Transmit data and SPIF still zero till Transmission is complete  
	while(!(SPSR & (1<<SPIF)));   // SPIF is one when serial transfer is complete.
	                              // wait until Interrupt flag = 1, data is sent correctly. 
}
uint8 spi_Receive_Byte()
{
	while(!(SPSR & (1<<SPIF)));  // SPIF is one when serial transfer is complete.
	                             // wait until Interrupt flag = 1, data is Received correctly. 
	return SPDR;
}
void spi_Send_String(const uint8* data)
{
	uint8 i = 0;
	while(data[i] != '\0')
	{
		spi_Send_Byte(data[i]);
		i++;
	}
}
void spi_Receive_String(uint8* data)
{
	uint8 i = 0;
	data[i] = spi_Receive_Byte();
	while(data[i] != '#')
	{
		i++;
		data[i] = spi_Receive_Byte();
	}
	data[i] = '\0';
}