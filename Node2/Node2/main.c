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
#include "UART_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "CAN_driver.h"
#include "SERVO_driver.h"
#include "PWM_driver.h"
#include "ADC_driver.h"
#include "IR_driver.h"
#include "MOTOR_driver.h"
#include "DAC_driver.h"
#include "SOLENOID_driver.h"
#include "bit_functions.h"
#include "game.h"

volatile uint8_t rx_int_flag = 0;

states current_state = IDLE;
difficulty mode = EASY;

Message config_msg;



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
	
	while (!rx_int_flag);
	config_msg = CAN_recieve();
	motor_calibration();
	if(config_msg.data[0] > -1 && config_msg.data[0] < 3){
		Message init_succeeded = {0, 1, {0}};
		CAN_send(&init_succeeded);
		printf("MELDING sent til node 1\n");
		current_state = config_msg.data[0];
		mode = config_msg.data[1];
		//LEGG TIL FAILED TO INIT
	}
	
	
	
	printf("CONFIG state %d \t mode %d \n", config_msg.data[0], config_msg.data[1]);
	while(1)
	{
		switch (current_state)
		{
			printf("Current state: %d\n", current_state);
			case IDLE:
				if(config_msg.data[0] > -1 && config_msg.data[0] < 3){
					current_state = config_msg.data[0];
					mode = config_msg.data[1];
					//LEGG TIL FAILED TO INIT
				}
				break;
			case USB:
				set_USB_mode(mode);
				USB_play_game();
				break;
			case PS2:
				set_PS2_mode(mode);
				PS2_play_game();
				break;
			default:
				break;
		}
	}
	return 0;
}

