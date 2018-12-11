/*
 * External_EEPROM.h
 *
 * Created: 12/11/2018 2:30:19 PM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

#include "i2c.h"

#define Error 0
#define Succes 1

void EEPROM_Init();
unsigned char EEPOM_Read_Byte(uint16 u16addr, uint8 *u8data);
unsigned char EEPROM_Write_Byte(uint16 u16addr, uint8 u8data);



#endif /* EXTERNAL_EEPROM_H_ */