/*
* Node2.c
*
* Created: 25.10.2017 11:49:48
*  Author: andrholt
*/
#define F_CPU 16000000
#include <util/delay.h>

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "driver_uart.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "CAN_driver.h"
#include "driver_servo.h"
#include "driver_pwm.h"
#include "driver_ADC.h"
#include "driver_IR.h"
#include "driver_motor.h"
#include "driver_DAC.h"
#include "driver_solenoid.h"
#include "bit_functions.h"

volatile uint8_t rx_int_flag = 0;
uint8_t left_joystick = 0;
uint8_t right_joystick;
float Kp;
float Ki;
float Kd;
int output = 0;
int timer_flag = 0;
int IR_value = 0; 
int last_IR_value = 0; 
int solenoid_button = 0;
typedef enum {IDLE = 0, EASY = 1, MEDIUM = 2, HARD = 3, PLAY} states;
states current_state = IDLE;

int main(void)
{
	
	cli();
	UART_init(MYUBRR);
	CAN_init();
	servo_init();
	ADC_init();
	solenoid_init();
	motor_init();
	sei();
	
	while(1)
	{
		
		switch (current_state)
		{
		case IDLE:
			if (rx_int_flag){
				Message recieve_msg = CAN_recieve();
				int received_state = recieve_msg.data[3];
				if (received_state > 0 && received_state <4){ 
					current_state = received_state;
					printf("current state %d \n", recieve_msg.data[3]);
				}
				rx_int_flag = 0;
			}
			break;
		case EASY:
			printf("EASY \n");
			Kp = 0.9;
			Kd = 0.07;
			Ki = 0.1;
			current_state = PLAY;
			break;
		case MEDIUM:
			printf("MEDIUM \n");
			Kp = 0.95;
			
			Kd = 0.1;
			Ki = 0.05;
			current_state = PLAY;
			break;
		case HARD:
			printf("HARD \n");
			Kp = 1;
			Kd = 0.1;
			Ki = 0.01;
			current_state = PLAY;
			break;
		case PLAY:
			
			if(rx_int_flag){
				Message recieve_msg = CAN_recieve();
				
				right_joystick = recieve_msg.data[0];
				left_joystick = recieve_msg.data[1];
				
				if (recieve_msg.data[2] == 0){
					solenoid_button = 0;
				}
				
				servo_set_pos(right_joystick);
				
				if (recieve_msg.data[2] != solenoid_button){
					printf("shoot\n");
					solenoid_shoot();
					solenoid_button = 1;
				}
				rx_int_flag = 0;
			}
			
			if(timer_flag == 1){
				clr_bit(TIMSK3, TOIE3);
				motor_drive(motor_PID(left_joystick, Kp, Ki, Kd));
				set_bit(TIMSK3, TOIE3);
				timer_flag = 0;
			}
			
			IR_value = IR_game_over();
			
			if(IR_value == 1){
				printf("Can melding, spill over\n");
				Message msg = {0, 1, {0}};
				CAN_send(&msg);
				current_state = IDLE;
						//waiting for message about new game
				
				
			}

			_delay_ms(1);
			break;
		}
		
	}
	return 0;
}


ISR(TIMER3_OVF_vect){
	timer_flag = 1;
	
}