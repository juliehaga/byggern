/*
 * fsm.c
 *
 * Created: 14.11.2017 09:38:38
 *  Author: julihag
 */ 

#define F_CPU 4915200
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "game.h"
#include "CAN_driver.h"
#include "OLED_driver.h"
#include "joystick.h"
#include "fsm.h"



extern char* highscore_names[5] = {"AAA"};
extern int highscore_scores[5] = {0};

int score = 0; 
int highest_score = 0;  
int life;
int oled_flag = 0;
volatile uint8_t rx_int_flag = 0;		//automatically set when 
//states current_state;


void play_game(void){
	int game_over = 0;
	life = 3;
	score = 0;  
	oled_reset();
	CAN_send_start();
	printf("har sendt start\n");
	
	while(!game_over){
		
		if (oled_flag){
			oled_play_game(life, score);
			oled_flag = 0;
		}
		CAN_send_controllers();
		_delay_ms(2);
		
		if(rx_int_flag){
			oled_play_game(life, score);
			life --;
			if(score > highest_score){
				highest_score = score;
			}
			printf("life: %d\n", life);
			if(life ==0){
				game_over = 1; 
				oled_game_over();
			} else{
				oled_play_again();
				while(!button_read(LEFT_BUTTON) & !button_read(RIGHT_BUTTON));
				if (button_read(RIGHT_BUTTON) != 0){
					game_over = 1;
				}else{
					score = 0;
				}
			}
			oled_reset();
			rx_int_flag = 0; 	
			}
		
	}
	//current_state = IDLE; 
}


int check_highscore(int score){
	char* name;
	for (int i = 0; i < 5 ; i++ ){
		if(score > highscore_scores[i]){
			name  = oled_type_in_name(score);
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
