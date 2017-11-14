/*
 * driver_solenoid.c
 *
 * Created: 12.11.2017 14:48:34
 *  Author: julihag
 */ 
#define F_CPU 16000000
#include "driver_solenoid.h"
#include "bit_functions.h"
#include <util/delay.h>


void solenoid_init(void){
	//Set solenoidpin(A1 == PF1) to output
	set_bit(DDRF, PF1);
	set_bit(PORTF, PF1);
}

void solenoid_shoot(void){
	clr_bit(PORTF, PF1);
	_delay_ms(500); 
	set_bit(PORTF, PF1);

}