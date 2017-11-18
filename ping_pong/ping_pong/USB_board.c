/*
 * joystick.c
 *
 * Created: 04.10.2017 16:22:01
 *  Author: andrholt
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "USB_board.h"
#include "ADC_driver.h"
#include "bit_functions.h"




joystick_dir last_joy_pos = CENTER;


int joystick_read(int channel){
	//Return 0-255
	return ADC_read(channel);
}


int slider_read(int channel){
	//Return 0-255
	return ADC_read(channel);
}

int button_read(int button){
	if (button == LEFT_BUTTON){
		return (test_bit(PINB, PINB1)/2);	
	}else if(button == RIGHT_BUTTON){
		return test_bit(PINB, PINB0);
	}
	return -1;
}


int read_joystick_button(void){
	return test_bit(PINB, PINB2);
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


