/*
 * joystick.c
 *
 * Created: 04.10.2017 16:22:01
 *  Author: andrholt
 */ 

#include "joystick.h"
#include "ADC_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_functions.h"
#include "CAN_driver.h"
#include "driver_uart.h"
#include <stdlib.h>

#include <util/delay.h>

joystick_dir last_joy_pos = 0;

uint8_t last_joystick_pos_x = 0;
uint8_t last_joystick_pos_y = 0;

/*
channel 4 = y
channel 5 = x
*/


int joystick_read(int channel){
	//Return 0-255
	return ADC_read(channel);
}


int slider_read(int channel){
	//Return 0-255
	return ADC_read(channel);
}


int buttons_read(int button){

	if (button == 1){
		return (test_bit(PINB, PINB1));		//returns 2??
		}else if(button == 2){
		return test_bit(PINB, PINB0);
	}
	return -1;
}

joystick_dir find_joystick_dir(void){
	int joystick_x = joystick_read(5);
	int joystick_y = joystick_read(4);
	
	//printf("x = %d\n", joystick_x); 
	//printf("y = %d\n", joystick_y); 
	
	if (joystick_y > 135){
		return UP;
	}
	else if (joystick_y < 130){
		return DOWN;
	}
	else if(joystick_x > 135){
		return RIGHT;
	}
	else if(joystick_x < 130){
		return LEFT;
	}
	return CENTER;
}

void send_joystick_dir(void){
	uint8_t joy_pos_x = ADC_read(CHANNEL_X);
	
	uint8_t joy_pos_y = ADC_read(CHANNEL_Y);
	
	printf("joy x= %d \t", ADC_read(CHANNEL_X));
	printf("joy y= %d \n",  ADC_read(CHANNEL_Y));
	
	if(abs(joy_pos_x - last_joystick_pos_x) > 10 || abs(joy_pos_y - last_joystick_pos_y) > 10){
		Message msg;
		
		msg.length = 2;
		msg.data[0] = joy_pos_x;
		msg.data[1] = joy_pos_y;
		msg.ID = 0;
		
		CAN_send(&msg);
		last_joystick_pos_x = joy_pos_x;
		last_joystick_pos_y = joy_pos_y;
	}
}

void send_slider_pos(void){
	int joy_pos = slider_read(6);
	Message msg;
	
	msg.length = 1;
	msg.data[0] = (uint8_t)joy_pos;
	msg.ID = 0;
	
	CAN_send(&msg);
}
