/*
 * game.c
 *
 * Created: 18.11.2017 01:21:33
 *  Author: johanndk
 */ 
#define F_CPU 16000000

#include <avr/interrupt.h>
#include <util/delay.h>
#include "CAN_driver.h"
#include "MOTOR_driver.h"
#include "SERVO_driver.h"
#include "bit_functions.h"
#include "SOLENOID_driver.h"
#include "IR_driver.h"
#include "game.h"

#define SPEED_EASY 150
#define SPEED_MEDIUM 180
#define SPEED_HARD 225


float Kp;
float Ki;
float Kd;
uint8_t motor_controller;
uint8_t servo_controller;
extern states current_state;
int timer_flag = 0;
int last_shooter = 0;
volatile uint8_t rx_int_flag;
extern int max_motor_value; 


void update_control_values(void){
	clr_bit(TIMSK3, TOIE3);	
	printf("mottar CAN");
	Message recieve_msg = CAN_recieve();
	if(recieve_msg.ID == PLAY_ID){
		
		servo_controller = recieve_msg.data[0];
		motor_controller = recieve_msg.data[1];
		int shooter = recieve_msg.data[2];
		if (shooter == 0){
			last_shooter = 0;
			} if (shooter != last_shooter){
			
			solenoid_shoot();
			
			last_shooter = 1;
		}
	set_bit(TIMSK3, TOIE3);
	}else{
		Message error_msg = {ERROR_ID, 1, {0}};
		CAN_send(&error_msg);
		current_state == IDLE;
		
	}
}

void update_input(void){
	clr_bit(TIMSK3, TOIE3);
	motor_power(motor_PID(motor_controller, Kp, Ki, Kd));
	servo_set_pos(servo_controller);
	set_bit(TIMSK3, TOIE3);
	timer_flag = 0;
}

void end_game(void){
	Message end_game_msg = {SCORE_ID, 1, {0}};
	printf("Sender melding om SCORE\n");
	CAN_send(&end_game_msg);
}

void USB_play_game(){		
	while(!IR_score() && current_state == USB){
		if(rx_int_flag){
			update_control_values();
		}if(timer_flag == 1){
			update_input();
		}
	_delay_ms(2);
	}
	end_game();
	current_state = IDLE;  //waiting for message about new game
}

void set_USB_mode(difficulty mode){
	if(mode == EASY){
		Kp = 0.9;
		Kd = 0.07;
		Ki = 0.1;
	}else if(mode == MEDIUM){
		Kp = 0.95;
		Kd = 0.1;
		Ki = 0.05;
	}else if(mode == HARD){
		Kp = 1;
		Kd = 0.1;
		Ki = 0.01;
	}
}

void set_PS2_mode(difficulty mode){
	if(mode == EASY){
		max_motor_value = SPEED_EASY;
	}else if(mode == MEDIUM){
		max_motor_value = SPEED_MEDIUM;
	}else if(mode == HARD){
		max_motor_value = SPEED_HARD;
	}
}

void PS2_update_input(void){
	clr_bit(TIMSK3, TOIE3);
	motor_velocity_control(motor_controller);
	servo_set_pos(servo_controller);
	set_bit(TIMSK3, TOIE3);
	timer_flag = 0;
}

void PS2_play_game(){	
	while(!IR_score() && current_state == PS2){
		if(rx_int_flag){
			update_control_values();
			}if(timer_flag == 1){
			PS2_update_input();
		}
		_delay_ms(2);
	}	
	end_game();
	printf("END GAME\n");
	current_state = IDLE;  //waiting for message about new game
}


ISR(TIMER3_OVF_vect){
	timer_flag = 1;
}