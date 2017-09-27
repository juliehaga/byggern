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
#include "menu_framework.h"


volatile uint8_t JOY_STICK = 0;

//deklarere alle structs
const menu_struct red = {"Red", NULL};
const menu_struct blue = {"Blue", NULL};
const menu_struct green = {"Green", NULL};
const menu_struct black= {"Black", NULL};
const menu_struct white= {"White", NULL}; 

menu_struct sub_julie[3] = {red, green, blue};
menu_struct sub_andrea[1] = {black};
menu_struct sub_johanne[1] = {white};
	
menu_struct julie("Julie", sub_julie); 
menu_struct johanne("Johanne", sub_johanne); 
menu_struct andrea("Andrea", sub_andrea); 

menu_struct sub_main_menu[3] = {julie, johanne, andrea};

menu_struct main_menu("Main Menu", sub_main_menu);

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
	print_menu_oled(main_menu);

	while(1)
	{
		
	}

	return 0;
}

ISR(INT2_vect){
	JOY_STICK = 1; 
	//wake up the CPU
}
