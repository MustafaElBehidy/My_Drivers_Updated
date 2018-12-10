/*
 * uart.h
 *
 * Created: 12/9/2018 5:36:58 PM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"

void uart_Init(uint16 Baud_Rate);
void uart_Send_Byte(uint8 Data);
void uart_Send_String(const uint8* Data);
uint8 uart_Receive_Byte();
void uart_Receive_String(uint8* str);


#endif /* UART_H_ */