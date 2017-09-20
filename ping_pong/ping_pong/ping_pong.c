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
#include "driver_uart.h"
#include "bit_functions.h"
#include "register_init.h"
#include "sram_test.h"


volatile uint8_t JOY_STICK = 0;

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
		//printf("%d\n", slider_read(7));
		printf("%d\n", buttons_read(1));
		//buttons_read(1);
	}

	
	return 0; 
}

ISR(INT2_vect){
	JOY_STICK = 1; 
	//wake up the CPU
}