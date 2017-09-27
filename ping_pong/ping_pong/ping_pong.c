/*
 * ping_pong.c
 *
 * Created: 01.09.2017 09:13:19
 *  Author: julihag
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


#include "driver_uart.h"
#include "bit_functions.h"
#include "register_init.h"
#include "sram_test.h"
#include "oled1.h"


volatile uint8_t JOY_STICK = 0;

volatile char *oled_cmd = 0x1000;

int main(void)
{
	// Disable global interrupts
	cli();
	
	UART_init(31);
	
	register_init();
	
	// Enable global interrupts
	sei();

	
	while(1){
		if(JOY_STICK){
			JOY_STICK = 0;
		}
		
		
		//printf("\nX = %d, Y = %d \n", joy_stick_read(4), joy_stick_read(5));
		printf("%d\n", slider_read(7));
	}

	
	return 0;
}

ISR(INT2_vect){
	JOY_STICK = 1; 
	//wake up the CPU
}