/*
 * driver_motor.c
 *
 * Created: 04.11.2017 14:41:30
 *  Author: julihag
 */ 

#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "MOTOR_driver.h"
#include "bit_functions.h"
#include "DAC_driver.h"

#define F_CPU 16000000
#define epsilon 1
#define dt 0.032
#define MAX 255
#define MIN 0
#define STOP 0
#define FULL_SPEED 255

int left_pos;
int right_pos;
motor_dir dir;
int max_motor_value = 0; 
int prev_error = 0; 
 

void motor_init(void){
	DAC_init();
	//declare output pins
	set_bit(DDRH, PH4);				//EN as output
	//enable motor
	set_bit(PORTH, PH4);
	set_bit(DDRH, PH1);				//DIR as output
	set_bit(DDRH, PH5);				//!OE as output
	set_bit(DDRH, PH3);				//SEL as output
	set_bit(DDRH, PH6);				//!RST as output
	
	set_bit(PORTH, PH5);			//Output enables
	set_bit(PORTH, PH6);			//set restart to pin

	DDRK = 0x00;
	motor_reset_encoder();
	
	//Set timer/counter0 interrupt
	//Normal mode
	clr_bit(TCCR3A, WGM31);
	clr_bit(TCCR3A, WGM30);
	
	//Prescale Fosc/6
	set_bit(TCCR3B, CS31);

	//Interrupt enable overflow
	set_bit(TIMSK3, TOIE3);
}

// Set the power of the motor
void motor_power(int motor_input){
	motor_set_dir();
	DAC_send_data(motor_input);
}

void motor_set_dir(void){
	if (dir == LEFT){
		clr_bit(PORTH, PH1);
	}else{
		set_bit(PORTH, PH1);
	}
}

void motor_reset_encoder(void){
	clr_bit(PORTH, PH6);
	_delay_ms(70);	
	set_bit(PORTH, PH6);
}

// Read the unscaled values given by the encoder
int16_t motor_read_encoder_unscaled(void){
	clr_bit(PORTH, PH5);		//!OE low
	clr_bit(PORTH, PH3);		//SEL low
	_delay_ms(20);
	int16_t data = PINK << 8;	//Read MSB
	set_bit(PORTH, PH3);		//SEL high
	_delay_ms(20);


	data = PINK | data;
	set_bit(PORTH, PH5);		//!OE high
	
	return data;
}


int16_t motor_read_encoder(void){
	int data = motor_read_encoder_unscaled();
	return -((double)(255)/(0-right_pos))*data;
}

void motor_calibration(void){
	//drive to left corner
	dir = LEFT;
	motor_power(150);
	_delay_ms(700);
	
	//choose zero-position
	motor_reset_encoder();
	
	dir = RIGHT;
	motor_power(150);
	_delay_ms(700);
	right_pos = motor_read_encoder_unscaled();
	motor_power(STOP);
	
	dir = LEFT;
	motor_power(150);
	left_pos = motor_read_encoder_unscaled();
	_delay_ms(1200);
	motor_reset_encoder();
}

// PID Controller for the motor, controlling the placement of the racket
int motor_PID(int slider_value, float Kp, float Ki, float Kd){
	static float integral = 0; 
	int data = motor_read_encoder();
	int error = slider_value - data; 

	if (error > 0){
		dir = RIGHT;
	}else{
		dir = LEFT; 
	}
	//in case of error too small, stop integration
	if(abs(error) > epsilon){
		integral = integral + error*dt;
	} 
	float derivate = (error - prev_error)/dt;
	int output = Kp*abs(error) + Ki*integral + Kd*derivate;
	
	if (output > MAX) {
		output = MAX;
	}else if (output < MIN){
		output = MIN;
	} 
	prev_error = error;
	return output;
}

//Scales and controls the velocity of the motor, when using PS2 controller
void motor_velocity_control(int control_value){
	if (control_value < 160){
		dir = LEFT;
	}else if (control_value > 90){
		dir = RIGHT;
	}
	int input;
	motor_set_dir();
	if(control_value > 160){
		input = (int)(control_value-135)*2.125;
	}else if(control_value < 90){
		input = (int)(130-control_value)*(double)255/130;
	}else{
		input = 0;
	}
	if(input > max_motor_value){
		input = max_motor_value;
	}
	DAC_send_data(input);
}