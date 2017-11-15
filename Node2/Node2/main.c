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
uint8_t slider_pos_r =0;
uint8_t joystick_pos_x;
int output = 0;
int timer_flag = 0;
int IR_value = 0; 
int last_IR_value = 0; 

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
		
		if(rx_int_flag){
			
			Message recieve_msg = CAN_recieve();
			
			joystick_pos_x = recieve_msg.data[0];
			slider_pos_r = recieve_msg.data[1];
			int solenoid_button = recieve_msg.data[2];
			
			
			servo_set_pos(joystick_pos_x);
			
			if (solenoid_button == 2){
				printf("shoot\n");
				solenoid_shoot();
				solenoid_button = 0;
			}
			rx_int_flag = 0; 
		}
		
		if(timer_flag == 1){
			clr_bit(TIMSK3, TOIE3);
			//printf("PI input %d \t", slider_pos_r);
			//printf("Encoder %d \n", motor_read_encoder());
			
			motor_drive(motor_PID(slider_pos_r));
			set_bit(TIMSK3, TOIE3);
			timer_flag = 0;
		}
		IR_value = IR_game_over();
		
		if(IR_value == 1){
			printf("Can melding, spill over\n");
			Message msg = {1, 1, 0};
			CAN_send(&msg);
			while(!rx_int_flag);			//waiting for message about new game
			rx_int_flag = 0; 
		}

		_delay_ms(1);
		
	}
	return 0;
}


ISR(TIMER3_OVF_vect){
	timer_flag = 1;
	
}