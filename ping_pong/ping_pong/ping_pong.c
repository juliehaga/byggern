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
#include "ADC_driver.h"
#include "joystick.h"
#include "menu_framework.h"


volatile uint8_t ADC_ready = 0;

volatile uint8_t* a = 0x1400;



int main(void) {
	// Disable global interrupts
	cli();
	UART_init(31);
	register_init();
	oled_init();
	ADC_init();
	// Enable global interrupts
	sei();
	
	
	//deklarere alle structs
	menu* main_menu = create_menu("Main Menu");
	menu* julie = create_menu("Julie");
	menu* andrea = create_menu("Andrea");
	menu* johanne = create_menu("Johanne");
	menu* red = create_menu("Red");
	menu* blue = create_menu("Blue");
	menu* green = create_menu("Green");
	menu* black = create_menu("Black");
	menu* white = create_menu("White");
	
	create_submenu(main_menu, julie);
	create_submenu(main_menu, andrea);
	create_submenu(main_menu, johanne);
	create_submenu(julie, red);
	printf("%s \n", main_menu->child->name);
	printf("%s \n", julie->next_sibling->name);
	printf("%s \n", andrea->next_sibling->name);
	printf("%s \n", julie->child->name);
	printf("%s \n", andrea->parent->name);
	printf("%s \n", johanne->prev_sibling->name);
	
	printf("%s \n", main_menu->child->name);
	oled_reset();
	oled_home();
	print_menu_oled(main_menu);
	oled_reset();
	print_menu_oled(julie);
	volatile uint8_t ADC_ready = 0;
	
	print_menu_page();
	while(1){
		
		
		if(ADC_ready){
			ADC_ready = 1;
		}
		
		
		
		printf("x = %d y = %d\n", joystick_read(4), joystick_read(5));
		
		
		
	}

	return 0;
}

ISR(INT2_vect){
	ADC_ready = 1; 
	//wake up the CPU
}
