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
#include <avr/interrupt.h>

#define epsilon 2
#define dt 0.032
#define MAX 255
#define MIN 0
#define STOP 0
#define FULL_SPEED 255

int left_pos = 0;
int right_pos;
motor_dir dir;

#define Kp 1
#define Ki 0.01
#define Kd 0.1
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
	
	sei();
	motor_calibration();
	cli();
		
	//Set timer/counter0 interrupt
	//Normal mode
	clr_bit(TCCR3A, WGM31);
	clr_bit(TCCR3A, WGM30);
	
	//Prescaler Fosc/8
	set_bit(TCCR3B, CS31);
	
	
	
	
	//Interrupt enable overflow
	set_bit(TIMSK3, TOIE3);
	

}


//Get joystick input 0-130: Left, 135-255: Right
void motor_drive(int motor_input){
	motor_set_dir();
	DAC_send_data(motor_input);
}

void motor_set_dir(void){
	if (dir == LEFT){
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
	
	return data*(-0.027);
}



void motor_calibration(void){
	
	//drive to left corner
	dir = LEFT;
	motor_drive(180);
	_delay_ms(500);
	
	//choose zero-position
	motor_reset_encoder();
	printf("encoder value %d\n", motor_read_encoder());
	
	dir = RIGHT;
	motor_drive(180);
	_delay_ms(500);
	right_pos = motor_read_encoder();
	motor_drive(STOP);
	printf("top %d\n", right_pos);
}


int motor_PI(int slider_value){
	static float integral = 0; 
	int error = slider_value - motor_read_encoder(); 
	if (error > 0){
		dir = RIGHT;
	} else{
		dir = LEFT; 
	}
	
	//in case of error ti small, stop integration
	if(abs(error) > epsilon){
		integral = integral + error*dt;
	} 
	float derivate = (error - prev_error)/dt;
	int output = Kp*abs(error) + Ki*integral + Kd*derivate;
	if (output > MAX) {
		output = MAX;
	} else if (output < MIN){
		output = MIN;
	} 
	prev_error = error;
	return output;
}


