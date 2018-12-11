/*
 * i2c.h
 *
 * Created: 12/11/2018 11:57:03 AM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "common_Macros.h"
#include "std_types.h"
#include "micro_config.h"

// Status Codes for Master Transmitter Mode
#define TWI_START           0x08       // A START condition has been transmitted
#define TWI_REP_START       0x10       // A repeated START condition has been transmitted
#define TWI_MT_SLA_W_ACK    0x18       // SLA+W has been transmitted; ACK has been received
#define TWI_MT_DATA_ACK     0x28       // Data byte has been transmitted; ACK has been received

// Status Codes for Master Receiver Mode
#define TWI_MT_SLA_R_ACK    0x40       // SLA+R has been transmitted; ACK has been received
#define TWI_MR_DATA_ACK     0x50       // Data byte has been received; ACK has been returned
#define TWI_MR_DATA_NACK    0x58       //Data byte has been received; NOT ACK has been returned
/*
#define TWI_MT_SLA_W_NACK   0x20       // SLA+W has been transmitted; NOT ACK has been received
#define TWI_MT_DATA_NACK    0x30       // Data byte has been transmitted; NOT ACK has been received
#define TWI_MT_ARB_LOST     0X38       // Arbitration lost in SLA+W or data bytes
#define TWI_MR_SLA_R_NACK   0x48       // SLA+R has been transmitted; NOT ACK has been received
*/

void twi_Init();
void twi_Set_SLA(uint8 Address);
void twi_Start();
void twi_Stop();
void twi_Write(uint8 data);
uint8 twi_Read_With_Ack();
uint8 twi_Read_With_Nack();
uint8 twi_Get_Status();


#endif /* I2C_H_ */