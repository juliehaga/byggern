/*
 * driver_servo.c
 *
 * Created: 01.11.2017 12:55:31
 *  Author: julihag
 */ 

#include <stdio.h>
#include <avr/io.h>
#include "PWM_driver.h"
#include "SERVO_driver.h"
#include "UART_driver.h"


void servo_init(void){
	pwm_init();
	//initialize to center position
	pwm_set_pulse_width(0.0015);
}

void servo_set_pos(uint8_t dir){
	if(dir > 135){					//dir is scaled from 0 to 100
		pwm_set_pulse_width(0.0015 + (dir-132)*0.000004);
	}else if (dir < 130){
		pwm_set_pulse_width(0.0009 + dir*0.000004);
	}else{
		pwm_set_pulse_width(0.0015);
	}
}