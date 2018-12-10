/*
 * adc.c
 *
 * Created: 12/9/2018 12:46:51 PM
 *  Author: Mustafa El_Behidy
 */ 


#include "adc.h"

void ADC_Init()
{
	// ADC Multiplexer Selection Register
	// REFS0:1-> 00 use AREF as REF
	//ADMUX &= ~((1<<REFS0) | (1<<REFS1));
	//ADLAR->0 ADC left Adjust result 0 use ADCL and two bits of ADCH
	//ADMUX &= ~(1<<ADLAR);
	// MUX0:5 -> 00000 use channel ADC0
	//ADMUX &= ~((1<<MUX0) | (1<<MUX1) | (1<<MUX2) | (1<<MUX3) | (1<<MUX4) );
	ADMUX = 0;
	//ADC control and Status Register A
	// Enable the ADC
	
	// ADCSRA |= (1<<ADIE);     //Interrupt Enable
	//ADCSRA |= (1<<ADIF);        // Interrupt Flag
	//ADCSRA |= (1<<ADATE);	    // auto trigered enable
	// ADC Prescaler
	//ADC Prescaler
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADEN);;     // F_OSC/8 & Enable ADC
}
uint16 ADC_Read()
{
	ADCSRA |= (1<<ADSC);
	/*
	 ADSC is 1 as long as the conversion is in progress.
	 when the conversion is complete it return to zero
	*/
	while(ADCSRA & (1<<ADSC));  
	ADCSRA &= ~(1<<ADIF);   
	/*
	ADIF is cleared by hardware when executing the corresponding interrupt
	handling vector. Alternatively, ADIF is cleared by writing a logical
	one to the flag.
	*/
	return ADC;
}