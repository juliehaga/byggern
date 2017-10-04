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





int main(void) {
	// Disable global interrupts
	cli();
	UART_init(31);
	register_init();
	oled_init();
	// Enable global interrupts
	sei();
	
	
	//deklarere alle structs
	menu* main_menu = create_menu("Main Menu", 3);
	menu* julie = create_menu("Julie", 2);
	menu* andrea = create_menu("Andrea", 1);
	menu* johanne = create_menu("Johanne", 2);
	menu* red = create_menu("Red", 0);
	menu* blue = create_menu("Blue", 0);
	menu* green = create_menu("Green", 0);
	menu* black = create_menu("Black", 0);
	menu* white = create_menu("White", 0);
	
	create_submenu(main_menu, julie);
	create_submenu(main_menu, andrea);
	
	
	printf("%s \n", main_menu->sub_menus[0]->name);
	
	/*create_submenu(main_menu, andrea);
	create_submenu(main_menu, johanne);

	create_submenu(julie, red);
	create_submenu(julie, blue);
	create_submenu(andrea, green);
	create_submenu(johanne, black);
	create_submenu(johanne, white);
	*/
	

	oled_reset();
	//oled_fill_page(0);
	oled_home();

	//print_menu_oled(main_menu);
	
	
	while(1)
	{
		
	}

	return 0;
}

ISR(INT2_vect){
	JOY_STICK = 1; 
	//wake up the CPU
}
