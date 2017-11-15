/*
 * fsm.c
 *
 * Created: 14.11.2017 09:38:38
 *  Author: julihag
 */ 

#define F_CPU 4915200
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "game.h"
#include "CAN_driver.h"
#include "OLED_driver.h"
#include "joystick.h"
#include "bit_functions.h"





extern char* highscore_names[5] = {"AAA"};
extern int highscore_scores[5] = {0};

int score = 0; 
int highest_score = 0;  
int life;
extern int oled_flag;
int send_can_flag = 0;
volatile uint8_t rx_int_flag = 0;		//automatically set when 
states current_state;


void play_game(void){
	
	
	int game_over = 0;
	life = 3;
	score = 0;  
	highest_score = 0; 
	oled_reset();
	CAN_send_start();
	printf("har sendt start\n");
	
	while(!game_over){
		
		//Update display
		if (oled_flag){
			oled_play_game(life, score);
			oled_flag = 0;
		}
		
		//Send Can-message to node2
		if(send_can_flag){
			clr_bit(ETIMSK, TOIE3);
			CAN_send_controllers();
			send_can_flag = 0;
			set_bit(ETIMSK, TOIE3);
		}
		
		
		
		
		if(rx_int_flag){							
			//Score in Node 2
			printf("mottar melding fra node 2 \n");
			oled_play_game(life, score);
			life --;
			
			//check if new highscore
			if(score > highest_score){
				highest_score = score;
			}
			printf("life: %d\n", life);
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
					Message new_game = {0, 1, {0}};
					CAN_send(&new_game);
					score = 0;
					}
				}
			oled_reset();
			rx_int_flag = 0; 	
			}
		}
	//If highscore, add to list and display highscore-list
	check_highscore(highest_score);
	current_state = HIGHSCORE;
}


int check_highscore(int score){
	char* name;
	for (int i = 0; i < 5 ; i++ ){
		if(score > highscore_scores[i]){
			name  = oled_type_in_name(int_to_str(score));
			for(int j = 5 ; j == i+1 ; j--){
				highscore_scores[j] = highscore_scores[j-1];
				highscore_names[j] = highscore_names[j-1];
			}
			highscore_names[i] = name;
			highscore_scores[i] = score;
			return 1;
		}
	}
	return 0;
}



ISR(TIMER1_OVF_vect){
	oled_flag = 1;
	score += 1;	
}

ISR(TIMER3_OVF_vect){
	send_can_flag = 1;
	
}
