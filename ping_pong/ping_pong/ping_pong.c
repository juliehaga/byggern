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
#include "OLED_driver.h"


volatile uint8_t JOY_STICK = 0;



int main(void)
{
	// Disable global interrupts
	cli();
	
	UART_init(31);
	register_init();
	
	oled_init();

	
	// Enable global interrupts
	sei();
	
	
	
	
	
	oled_reset();
	//oled_fill_page(0);
	oled_home();
	oled_print_string("bendik1111111112hei");
	
	while(1)
	{
		printf("button=  %d\n", read_bit(PINB, PINB2));
	}

	return 0;
}

ISR(INT2_vect){
	JOY_STICK = 1; 
	//wake up the CPU
}