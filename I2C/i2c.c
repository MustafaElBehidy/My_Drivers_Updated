/*
 * i2c.c
 *
 * Created: 12/11/2018 11:56:48 AM
 *  Author: Mustafa El_Behidy
 */ 

#include "i2c.h"

void twi_Init()
{
	// TWBR TWI Bit Rate Register
	// SCL Frequency = CPU Clock Frequency / ( 16 + 2 * (TWBR) * pow(4,TWPS) )   400KB 
	TWBR = 0x02;
	TWSR = 0;
	TWAR = 0b00000010;   // my address = 0x01 :)
	// TWCR TWI Control Register
	TWCR |= (1<<TWEN);    // TWEN: TWI Enable Bit
	//TWCR |= (1<<TWIE)   // TWIE: TWI Interrupt Enable
	
	// TWSR TWI Status Register
	//Bits 1:0  TWPS: TWI Prescaler Bits
	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
       General Call Recognition: Off */
}

void twi_Set_SLA(uint8 Address);
void twi_Start()
{
	// TWINT TWI Interrupt Flag This bit is set by hardware when the TWI has finished its current job
	/*
	# The TWINT Flag must be cleared by software by writing a logic one to it.
	# Send Start Bit by TWSTA = 1
	# Enable TWI Module TWEN = 1
	*/
	TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// Wait for TWINT flag set (TWSTA is send successfully )
	while(!(TWCR & (1<<TWINT)));
}
void twi_Stop()
{
	/*
	# The TWINT Flag must be cleared by software by writing a logic one to it.
	# Send Stop Bit by TWSTO = 1
	# Enable TWI Module TWEN = 1
	*/
	TWCR |= (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}
void twi_Write(uint8 data)
{
	TWDR = data;
	//TWCR = (1<<TWINT) | (1<<TWEN);
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}
uint8 twi_Read_With_Ack()
{
	// If the TWEA bit is written to one, the ACK pulse is generated on the TWI bus.
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
uint8 twi_Read_With_Nack()
{
	TWCR |= (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}
uint8 twi_Get_Status()
{
	uint8 Status;
	Status = TWSR & 0xF8;
	return Status;
	/*
	The application designer should mask the Prescaler bits to zero when checking the
	Status bits.
	*/
}