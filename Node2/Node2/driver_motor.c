/*
 * driver_motor.c
 *
 * Created: 04.11.2017 14:41:30
 *  Author: julihag
 */ 

#define F_CPU 16000000
#include "driver_motor.h"
#include "bit_functions.h"
#include "driver_DAC.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdlib.h>

#define epsilon 2
#define ST 0.01
#define MAX 255
#define MIN 0


#define Kp 0.1
#define Ki 0.005

float top_speed;
int prev_encoder = 0; 
 

void motor_init(void){
	//declare output pins
	set_bit(DDRH, PH4);				//EN as output
	//enable motor
	set_bit(PORTH, PH4);
	set_bit(DDRH, PH1);				//DIR as output
	set_bit(DDRH, PH5);				//!OE as output
	set_bit(DDRH, PH3);				//SEL as output
	set_bit(DDRH, PH6);				//!RST as output
	
	set_bit(PORTH, PH5);
	set_bit(PORTH, PH6);
	
	
	
	DDRK = 0x00;
	motor_reset_encoder();
}


//Get joystick input 0-130: Left, 135-255: Right
void motor_drive(int motor_input){
	
	motor_set_dir(motor_input);
	
	if(motor_input > 135){
		DAC_send_data((int)(motor_input-135)*2.125); //Scaling
	}
	else if(motor_input < 130){
		DAC_send_data((int)(130-motor_input)*(double)255/130);
	}
	else{
		DAC_send_data(0);
	}
	
}

void motor_set_dir(int dir){
	if (dir < 132){
		clr_bit(PORTH, PH1);
	}
	else{
		set_bit(PORTH, PH1);
	}
}

void motor_reset_encoder(void){
	clr_bit(PORTH, PH6);
	_delay_ms(70);	
	set_bit(PORTH, PH6);
	//Reset
}

int16_t motor_read_encoder(void){
	clr_bit(PORTH, PH5);		//!OE low
	clr_bit(PORTH, PH3);		//SEL low
	_delay_ms(20); 
	int16_t data = PINK << 8;	//Read MSB
	set_bit(PORTH, PH3);		//SEL high
	_delay_ms(20);
	
	//printf("K = %d\n", PINK);
	data = PINK | data;
	//motor_reset_encoder();
	set_bit(PORTH, PH5);		//!OE high
	return data;
}

int motor_velocity(void){
	int encoder_value = motor_read_encoder();
	float velocity = (encoder_value - prev_encoder)/ST;
	return 0;
}

void motor_calibration(void){
	motor_drive(255);
	
	_delay_ms(200);
	motor_drive(132);
	motor_reset_encoder();
	printf("encoder value %d\n", motor_read_encoder());
	motor_drive(0);
	_delay_ms(100);
	motor_drive(132);
	top_speed = motor_read_encoder()/0.2;
	printf("top %d\n", top_speed);
}


void motor_PI(int joystick_value){
	static float integral = 0; 
	int error = joystick_value - motor_velocity(); 
	
	//in case of error ti small, stop integration
	if(abs(error) > epsilon){
		integral = integral + error*ST;
	} 
	int output = Kp*error + Ki*integral;
	
	if (output > MAX) {
		output = MAX;
	} else if (output < MIN){
		output = MIN;
	} 
	motor_drive(output);
}


