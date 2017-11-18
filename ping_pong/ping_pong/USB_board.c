/*
 * joystick.c
 *
 * Created: 04.10.2017 16:22:01
 *  Author: andrholt
 */ 

#include "USB_board.h"
#include "ADC_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_functions.h"
#include "CAN_driver.h"
#include "UART_driver.h"
#include <stdlib.h>
#include "bit_functions.h"

#include <util/delay.h>

joystick_dir last_joy_pos = 0;




int joystick_read(int channel){
	//Return 0-255
	return ADC_read(channel);
}


int slider_read(int channel){
	//Return 0-255
	return ADC_read(channel);
}


int button_read(int button){
	/*
	Left button = 1
	Right button = 2
	*/
	
	if (button == 1){
		return (test_bit(PINB, PINB1)/2);		//returns 2??
	}else if(button == 2){
		return test_bit(PINB, PINB0);
	}
	return -1;
}

joystick_dir find_joystick_dir(void){
	int joystick_x = joystick_read(CHANNEL_X);
	int joystick_y = joystick_read(CHANNEL_Y);
	
	if (joystick_y > 150){
		return UP;
	}
	else if (joystick_y < 110){
		return DOWN;
	}
	else if(joystick_x > 150){
		return RIGHT;
	}
	else if(joystick_x < 110){
		return LEFT;
	}
	return CENTER;
}


void send_slider_pos(void){
	int joy_pos = slider_read(6);
	Message msg;
	
	msg.length = 1;
	msg.data[0] = (uint8_t)joy_pos;
	msg.ID = 0;
	
	CAN_send(&msg);
}

int read_joystick_button(void){
	return test_bit(PINB, PINB2);
}