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

int current_page = 1; 
menu* display_menu;
joystick_dir last_joy_dir = CENTER; 

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
	display_menu = main_menu; 
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




	oled_reset();
	print_menu_oled(main_menu, current_page);



	volatile uint8_t ADC_ready = 0;

	

	while(1){
	
		if(ADC_ready){
			ADC_ready = 0;
		}
		
		joystick_dir joy_dir = find_joystick_dir();
		if(joy_dir != last_joy_dir){
		
		

			switch(joy_dir){
				case UP:
					if(current_page > 1){
						current_page--;
					}
					print_menu_oled(display_menu, current_page);
					printf("up\n");
					break;
				case DOWN:
					if(current_page < display_menu->number_of_childs){
						current_page++;
					}
					print_menu_oled(display_menu, current_page);
					printf("down\n");
					break;
				case RIGHT:
					display_menu = update_display_menu(display_menu, current_page, RIGHT);
					current_page = 1;
					print_menu_oled(display_menu, current_page);
					printf("right\n");
					break;
				case LEFT:
					display_menu = update_display_menu(display_menu, current_page, LEFT);
					current_page = 1; 
					print_menu_oled(display_menu, current_page);
					printf("left\n");

					break;
			
				default:
					break;
			}
			last_joy_dir = joy_dir;
		}
	}


	return 0;
}

ISR(INT2_vect){
	ADC_ready = 1; 
	//wake up the CPU
}
