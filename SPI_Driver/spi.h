/*
 * spi.h
 *
 * Created: 12/10/2018 11:41:59 AM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "common_Macros.h"
#include "micro_config.h"

void spi_Master_Init();
void spi_Slave_Init();
void spi_Send_Byte(uint8 data);
void spi_Send_String(const uint8 *data);
uint8 spi_Receive_Byte();
void spi_Receive_String(uint8* data);

#endif /* SPI_H_ */