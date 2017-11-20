/*
 * game.c
 *
 * Created: 14.11.2017 09:38:38
 *  Author: julihag
 */ 


#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "game.h"
#include "CAN_driver.h"
#include "OLED_driver.h"
#include "USB_board.h"
#include "bit_functions.h"
#include "highscore.h"


extern int difficulty;
extern int controller;

extern int update_oled_flag;
extern int highest_score;

int send_can_flag = 0;

volatile uint8_t rx_int_flag = 0;		
states current_state;
int score;


void play_game(){
	highest_score = 0; 
	int game_over = 0;
	int life = 3;
	
	Message boot_node2 = {INIT_ID, 2, {controller, difficulty}};
	CAN_send(&boot_node2);
	
	oled_loading_game();
	while(!rx_int_flag);			//Wait for Node 2 to respond
	CAN_recieve();					//clear rx_int_flag
	score = 0; 
	
	while(!game_over){
		
		//Update display
		if (update_oled_flag){
			oled_play_game(life, score);
			update_oled_flag = 0;
		}
		
		//Send Can-message to node2
		if(send_can_flag){
			clr_bit(ETIMSK, TOIE3);
			if(controller == PS2){
				CAN_send_ps2_controllers();
			}else{
				CAN_send_controllers();
			}
			send_can_flag = 0;
			set_bit(ETIMSK, TOIE3);
		}
		
		
		if(rx_int_flag){							
			oled_play_game(life, score);
			Message msg_node2 = CAN_recieve();
			
			//Check for communication error with Node 2 - end game
			if (msg_node2.ID == ERROR_ID){
				game_over = 1;
				current_state = IDLE;
			}
			
			//Check if game ended
			else if(msg_node2.ID == END_GAME_ID){
				life --;
				
				//check if new highscore
				if(score > highest_score){
					highest_score = score;
				}
				
				if(life == 0){
					game_over = 1;
					oled_game_over();
					
				} else{
					
					//Ask for a new game
					oled_play_again();
					while(!button_read(LEFT_BUTTON) & !button_read(RIGHT_BUTTON));
					
					//If no - game over
					if (button_read(RIGHT_BUTTON) != 0){
						game_over = 1;
					}else{
						
						//Start new round in Node 2
						CAN_send(&boot_node2);
						oled_loading_game();
						score = 0;
					}
				}
			}	
		}
	}
	current_state = NEW_HIGHSCORE;
}


ISR(TIMER1_OVF_vect){
	update_oled_flag = 1;
	score += 1;	
}

ISR(TIMER3_OVF_vect){
	send_can_flag = 1;
}
