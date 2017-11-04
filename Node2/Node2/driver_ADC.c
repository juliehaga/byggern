/*
 * driver_ADC.c
 *
 * Created: 01.11.2017 17:35:00
 *  Author: julihag
 */ 

#include "driver_ADC.h"
#include <avr/io.h>
#include "bit_functions.h"
#include <avr/interrupt.h>




volatile int ADC_ready;


void ADC_init(void){
	//Set PF0 to input
	clr_bit(DDRF, PF0);
	
	//enable ADC 
	set_bit(ADCSRA, ADEN); 
	
	//set prescaler to 128
	set_bit(ADCSRA, ADPS2);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS0);
	
	//Internal voltage ref 2.56 at AREF pin
	set_bit(ADMUX, REFS1); 
	set_bit(ADMUX, REFS0); 
	
	//enable interrupt
	set_bit(ADCSRA, ADIE); 
	
	
}

uint16_t ADC_read(void){
	//ADC0 is default channel
	//start conversion, when done automatically set to 0
	set_bit(ADCSRA, ADSC);
	
	while(!ADC_ready){
		printf("I while\n");
	}
	ADC_ready = 0;
	uint16_t data = ADCL | ADCH << 8;
	uint8_t data_l = ADCL; 
	uint8_t data_h = ADCH; 

	return data;
}



ISR(ADC_vect){
	ADC_ready = 1;
	//wake up the CPU
}
