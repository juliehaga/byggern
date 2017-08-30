/*
 * ping_pong_game.c
 *
 * Created: 30.08.2017 10:30:12
 *  Author: julihag
 */ 



#include <avr/io.h>
#include <util/delay.h>
#include "driver.h"

#define FOSC 4.9152// Clock Speed
#define F_CPU 4.9142//CPU clock speed
#define BAUD 9600  //Bits per second
#define MYUBRR FOSC/16/BAUD-1

#define set_bit(reg, pin)\
(reg |= (1<< (pin)))

#define clr_bit(reg, pin)\
(reg &= ~(1<< (pin)))

#define test_bit(reg, pin)\
(reg & (1<< (pin))

int main(void)
{	

	
	USART_init(MYUBRR);
	USART_transmit('h');
	return 0;   
}

		
