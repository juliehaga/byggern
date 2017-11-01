/*
 * timer.c
 *
 * Created: 01.11.2017 10:39:55
 *  Author: julihag
 */ 

#include "driver_uart.h"
#include "driver_pwm.h"
#include <avr/io.h>
#include "bit_functions.h"
#include <avr/interrupt.h>

#define PWM_FREQ FOSC/256

void pwm_init(void){
	
	//non-invert mode
	set_bit(TCCR1A, COM1A1);
	clr_bit(TCCR1A, COM1A0);
	
	//ICRn as TOP
	set_bit(TCCR1A, WGM11);
	clr_bit(TCCR1A, WGM10);
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1B, WGM13);
	
	//set prescaler clk/256
	set_bit(TCCR1B, CS12); 
	clr_bit(TCCR1B, CS11); 
	clr_bit(TCCR1B, CS10); 
	
	//set OC1A to output pin
	set_bit(DDRB, PB5);
	
	
	pwm_set_period(0.02); 
}

void pwm_set_period(float sec){
	if ((sec < 0.021) & (sec > 0.009)){
		uint16_t period = (PWM_FREQ)*sec -0.5;
		ICR1 = period;  
	}
}

void pwm_set_pulse_width(float sec){
	cli();
	if ((sec < 0.0021) & (sec > 0.0009)){
		
		uint16_t pulse = PWM_FREQ*sec -0.5;

		OCR1A = pulse;
	}

	sei();
}
