/*
 * External_EEPROM.c
 *
 * Created: 12/11/2018 2:30:06 PM
 *  Author: Mustafa El_Behidy
 */ 


#include "External_EEPROM.h"

void EEPROM_Init()
{
	twi_Init();
}

unsigned char EEPROM_Write_Byte(uint16 u16addr, uint8 u8data)
{
	twi_Start();
	if (twi_Get_Status() != TWI_START)
		return Error;
	
	
	//slave address with Ack
	twi_Write((uint8)( (0xA0) | ((u16addr & 0x0700) >> 7 ) ));
	if (twi_Get_Status() != TWI_MT_SLA_W_ACK)
		return Error;
	
	// required location address
	twi_Write((uint8)(u16addr));
	if (twi_Get_Status() != TWI_MT_DATA_ACK)
		return Error;
		
	// Data
	twi_Write(u8data);
	if (twi_Get_Status() != TWI_MT_DATA_ACK)
		return Error;
	
	
	twi_Stop();
	return Succes;
}

unsigned char EEPOM_Read_Byte(uint16 u16addr, uint8 *u8data)
{
	twi_Start();
	if (twi_Get_Status() != TWI_START)
		return Error;
	
	// write the device address and then we need to get A10 A9 A8 plus R/W 0 (write)
	twi_Write((uint8)( (0xA0) | ((u16addr & 0x0700)>>7)) );
	if (twi_Get_Status() != TWI_MT_SLA_W_ACK)
		return Error;
	
	// write the required locatation address
	twi_Write((uint8)(u16addr));
	if (twi_Get_Status() != TWI_MT_DATA_ACK)
		return Error;
	
	// repeated start
	twi_Start();
	if(twi_Get_Status() != TWI_REP_START)
		return Error;
	
	
	// write the device address and then we need to get A10 A9 A8 plus R/W 1 (write)
	twi_Write((uint8)( (0xA0) | ((u16addr & 0x0700) >> 7) | 0x01 ));
	if (twi_Get_Status() != TWI_MT_SLA_R_ACK)
		return Error;
	
	*u8data = twi_Read_With_Nack();
	if (twi_Get_Status() != TWI_MR_DATA_NACK)
		return Error;
	
	twi_Stop();
	return Succes;
	
}