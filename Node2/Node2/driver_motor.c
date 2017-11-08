/*
 * driver_motor.c
 *
 * Created: 04.11.2017 14:41:30
 *  Author: julihag
 */ 


#include "driver_motor.h"
#include "bit_functions.h"
#include "driver_DAC.h"
#include <avr/io.h>

void motor_init(void){
	//declare output pins
	set_bit(DDRH, PH5);				//EN as output
	set_bit(DDRH, PH6);				//DIR as output
	
	//prescale SCK to f_osc/64
	set_bit(TWSR, TWPS1); 
	set_bit(TWSR, TWPS0);
	
	//enable motor
	set_bit(PORTH, PH5);			
	
}


//Get joystick input 0-50: Left, 50-100: Right
void motor_drive(int joystick_value){
	
	motor_set_dir(joystick_value);
	
	if(joystick_value > 135){
		DAC_send_data((int)(joystick_value-135)*2.125); //Scaling
	}
	else if(joystick_value < 130){
		DAC_send_data((int)(130-joystick_value)*(double)255/130);
	}
	else{
		DAC_send_data(0);
	}
	
}

void motor_set_dir(int dir){
	
	if (dir < 132){
		clr_bit(PORTH, PH6);
	}
	else{
		set_bit(PORTH, PH6);
	}
}
