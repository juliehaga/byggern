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


int joystick_read(int channel){
	double pos = ADC_read(channel);

	if (pos < 132){
		double a = (100-(pos/(132)*100));
	}

	if (pos < 132){
		double a = (100-(pos/(132)*100));
	

		return -(int)a;
	}
	else{
		double a = (pos-132)/(255-132)*100;

		return (int)a;
	}
}


int slider_read(int channel){
	double pos = ADC_read(channel);
	return pos/255*100;
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
	
	if (joystick_y > 80){
		return UP;
	}
	else if (joystick_y < -80){
		return DOWN;
	}
	else if(joystick_x > 80){
		return RIGHT;
	}
	else if(joystick_x < -80){
		return LEFT;
	}
	return CENTER;
	
}




