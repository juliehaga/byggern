/*
 * driver_solenoid.c
 *
 * Created: 12.11.2017 14:48:34
 *  Author: julihag
 */ 
#define F_CPU 16000000
#include <util/delay.h>

#include "SOLENOID_driver.h"
#include "bit_functions.h"



void solenoid_init(void){
	//Set solenoidpin(A1 == PF1) to output
	set_bit(DDRF, PF2);
	set_bit(PORTF, PF2);
}

void solenoid_shoot(void){
	clr_bit(PORTF, PF2);
	_delay_ms(100); 
	set_bit(PORTF, PF2);

}