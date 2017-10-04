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


int joy_stick_read(int channel){
	double pos = ADC_read(channel);
	printf("pos = %d \n", pos);
	if (pos < 132){
		double a = (100-(pos/(132)*100));
		printf("-a = %d\n", a);
		return -(int)a;
	}
	else{
		double a = (pos-132)/(255-132)*100;
		printf("a = %d\n", a);
		return (int)a;
	}
}


int slider_read(int channel){
	double pos = ADC_read(channel);
	return pos/255*100;
}


int buttons_read(int button){

	if (button == 1){
		return (read_bit(PINB, PINB1));		//returns 2??
		}else if(button == 2){
		return read_bit(PINB, PINB0);
	}
	return -1;
}

