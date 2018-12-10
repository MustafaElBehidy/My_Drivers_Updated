/*
 * common_Macros.h
 *
 * Created: 12/8/2018 3:57:40 PM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

//SET Bit to one
#define Set_Bit(REG,BIT) (REG|=(1<<BIT))
// clear bit to 0
#define CLEAR_BIT(REG,BIT) (REG &= ~(1<<BIT))
// check if Bit is set
#define BIT_IS_SET(REG,BIT) (REG & (1<<BIT))
// check if bit is clear
#define BIT_IS_CLEAR(REG,BIT) (!(REG & (1<<BIT)))
//rotate reg value right by specific value
#define ROT_RIGHT(REG,NUM) (REG = (REG<<NUM) | (REG>>(8-NUM)))
// rotate reg left by specific value
#define ROT_LEFT(REG,NUM) (REG = (REG>>NUM) | (REG<<(8-NUM)))

#endif /* COMMON_MACROS_H_ */