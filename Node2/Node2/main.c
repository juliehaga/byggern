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

volatile uint8_t rx_int_flag = 0;
uint8_t slider_pos_r = 132;
int output = 0;
int flag = 0;

int main(void)
{
	
	cli();
	UART_init(MYUBRR);
	CAN_init();
	servo_init();
	ADC_init();
	motor_init();
	solenoid_init();
	sei();			//global interrupt enable

	while(1)
	{	
		
	
		//printf("ENCODER: %d\n",motor_read_encoder());
		if(rx_int_flag){
			printf("can received \n");
			
			Message recieve_msg = CAN_recieve();
			
			slider_pos_r = recieve_msg.data[0];
			uint8_t joystick_pos_x = recieve_msg.data[1];
			int solenoid_button = recieve_msg.data[2];
			
			printf("x_pos %d \t ", joystick_pos_x);
			printf("Button %d \t ", solenoid_button);
			printf("slider r %d \n", slider_pos_r);
			servo_set_pos(joystick_pos_x);
			
			if (solenoid_button == 2){
				printf("shoot\n");
				solenoid_shoot();
				solenoid_button = 0;
			}
			
			
			
		}
		
		if(flag == 1){
			motor_drive(motor_PI(slider_pos_r));
			flag = 0;
		}
		
		
		
		
		

		/*
		if(IR_game_over()){
		printf("Digital filter: %d \n", IR_digital_filter());
		printf("you loose \n");
		}*/
		

		_delay_ms(1);
		
	}
	return 0;
}

ISR(TIMER3_OVF_vect){

	flag = 1;
}