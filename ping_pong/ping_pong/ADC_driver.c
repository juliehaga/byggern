/*
 * ADC_driver.c
 *
 * Created: 20.09.2017 10:46:05
 *  Author: andrholt
 */ 
#define F_CPU 4915200
#include "ADC_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_functions.h"
#include <util/delay.h>



volatile int ADC_ready;

int ADC_init(void) {
	// Interrupt on rising edge PE0
	EMCUCR |= (1<<ISC2);

	// Enable interrupt on PE0
	GICR |= (1<<INT2);
	
	// Button input
	clr_bit(DDRE, PE0);
	
	//Enable the external memory interface/4 bits address
	MCUCR |= (1<<SRE);
	SFIOR |= (1<<XMM2);
	
	//Set the interrupt pin to input
	DDRE &= ~(1<<PINE0);

	//set button pins to input
	clr_bit(DDRB, DDB0);
	clr_bit(DDRB, DDB1);
	
	//set joystick button to input
	clr_bit(DDRB, DDB2);
	return 0;
}



uint8_t ADC_read(uint8_t channel) {
	//Address for the ADC
	volatile char *adc = (char *) 0x1400;
	_delay_ms(2);
	//Choose channel in ADC
	*adc = 0x04 | channel;
	while(!ADC_ready);
	_delay_ms(2);
	ADC_ready = 0; 
	return *adc;
}


ISR(INT2_vect){
	ADC_ready = 1;
	//wake up the CPU
}
