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
#include <stdlib.h>

joystick_dir last_joy_pos = 0;

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
	int joystick_x = joystick_read(4);
	int joystick_y = joystick_read(5);
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
	joystick_dir joy_pos_x = joystick_read(CHANNEL_X);
	joystick_dir joy_pos_y = joystick_read(CHANNEL_Y);
	
	Message msg;
	
	msg.length = 2;
	msg.data[0] = (uint8_t)joy_pos_x;
	msg.data[1] = (uint8_t)joy_pos_y;
	msg.ID = 0;
	
	CAN_send(&msg);
}

void send_slider_pos(void){
	int joy_pos = slider_read(6);
	Message msg;
	
	msg.length = 1;
	msg.data[0] = (uint8_t)joy_pos;
	msg.ID = 0;
	
	CAN_send(&msg);
}
