/*
 * fsm.c
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


#define SCORE_ID 1
#define INIT_ID 2


int life;
int score = 0; 
int highest_score = 0;  
extern int oled_flag;
extern int highest_score;
int send_can_flag = 0;
volatile uint8_t rx_int_flag = 0;
states current_state;
int controller = USB;
int difficulty;






void play_game(){
	int game_over = 0;
	game_setup();
	
	while(!game_over){
		//Update display
		if (oled_flag){
			oled_play_game(life, score);
			oled_flag = 0;
		}
		//Send controller values to node2
		if(send_can_flag){
			clr_bit(ETIMSK, TOIE3);
			if(controller == PS2){
				CAN_send_ps2_controllers();
			}else{
				CAN_send_USB_controllers();
			}
			send_can_flag = 0;
			set_bit(ETIMSK, TOIE3);
		}
		//Score in Node 2
		if(rx_int_flag){							
			oled_play_game(life, score);
			Message msg_node2 = CAN_recieve();
			if(msg_node2.data[0] = SCORE_ID){
				//Score in Node 2, end of round
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
						//If yes - Send play game signal to node 2
						_delay_ms(500);
						Message reboot_node2 ={INIT_ID, 2, {controller, difficulty}};
						CAN_send(&reboot_node2);
						score = 0;
					}
				}
			}
				
		}
			
	}
	//If highscore, add to list and display highscore-list
	current_state = NEW_HIGHSCORE;
}

void game_setup(){
	Message boot_node2 = {INIT_ID, 2, {controller, difficulty}};
	CAN_send(&boot_node2);
	
	life = 3;
	highest_score = 0;
	score = 0;
	while(!rx_int_flag); //wait for init succeeded
	CAN_recieve();
	oled_loading_game();
	printf("NODE 2 initialized \n");
}


ISR(TIMER1_OVF_vect){
	oled_flag = 1;
	score += 1;	
}

ISR(TIMER3_OVF_vect){
	send_can_flag = 1;
}
