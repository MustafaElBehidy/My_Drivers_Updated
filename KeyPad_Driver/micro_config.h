/*
 * micro_config.h
 *
 * Created: 12/8/2018 3:58:17 PM
 *  Author: Mustafa El_Behidy
 */ 


#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 1000000UL    // 1KHZ Frequency
#endif 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#endif /* MICRO_CONFIG_H_ */