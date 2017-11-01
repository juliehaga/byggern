/*
 * driver_servo.c
 *
 * Created: 01.11.2017 12:55:31
 *  Author: julihag
 */ 


#include "driver_pwm.h"
#include "driver_servo.h"
#include <stdio.h>
#include <avr/io.h>
#include "driver_uart.h"
void servo_init(void){
	pwm_init();
	//initialize to center position
	pwm_set_pulse_width(0.0015);
}


void servo_set_pos(uint8_t dir){
	

	if(dir > 55){					//dir is scaled from 0 to 100
		pwm_set_pulse_width(0.0015 + (dir-50)*0.000012);
	}
	else if (dir < 45){
		pwm_set_pulse_width(dir*0.00003);
	}
	else{
		pwm_set_pulse_width(0.0015);
	}
}