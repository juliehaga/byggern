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


#include "UART_driver.h"
#include "bit_functions.h"
#include "register_init.h"
#include "sram_test.h"
#include "OLED_driver.h"
#include "ADC_driver.h"
#include "USB_board.h"
#include "menu_framework.h"
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "MCP2515.h"
#include "highscore.h"
#include "game.h"
#include "ps2.h"


states current_state = IDLE;
int oled_flag = 0;
int place = 0;
int highest_score;


int main(void) {
	
	// Disable global interrupts
	cli();
	UART_init(31);
	register_init();
	oled_init();
	ADC_init();
	CAN_init();
	ps2_init();
	//Enable global interrupts
	sei();
	printf("\n--------------------\n\nNODE 1 \n\n ---------------------\n");
	
	/*IKKE FJÆRN*/
	menu_setup();
	read_highscore_list();

	
	while(1){
		switch(current_state){
			case IDLE:
				main_menu();
				break;
			case PLAY:
				play_game();
				break;
			case RESET_HIGHSCORE:
				reset_highscore_list();
				current_state = HIGHSCORE;
				break;
			case NEW_HIGHSCORE:
				place = check_highscore(highest_score);
				if ( place  > -1){
					char* nickname = oled_type_in_name(int_to_str(highest_score));
					insert_highscore(place, highest_score, nickname);
				}
				current_state = HIGHSCORE;
				break;
			case HIGHSCORE:
				if(find_joystick_dir() == LEFT){
					current_state = IDLE;
				}
				if (oled_flag){
					oled_print_highscore();
					oled_flag = 0;
				}
				break;
			default:
				break;
		_delay_ms(10);
		}
	}
	return 0;
}

