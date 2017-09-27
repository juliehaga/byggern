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
#include "oled_driver.h"


volatile uint8_t JOY_STICK = 0;

volatile char *oled_cmd = 0x1000;
volatile char *oled_d = 0x1200;

int main(void)
{
	// Disable global interrupts
	cli();
	
	UART_init(31);
	register_init();
	
	oled_init();

	
	// Enable global interrupts
	sei();
	
	
	
	
	oled_fill_page(0);
	oled_fill_page(1);
	oled_fill_page(2);
	oled_fill_page(3);
	oled_fill_page(4);
	oled_fill_page(5);
	oled_fill_page(6);
	oled_fill_page(7);
	*oled_cmd = 1;
	while(1)
	{
	
	}

	return 0;
}

ISR(INT2_vect){
	JOY_STICK = 1; 
	//wake up the CPU
}