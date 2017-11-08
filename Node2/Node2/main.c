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

volatile uint8_t rx_int_flag = 0;

int main(void)
{
	
	cli();
	UART_init(MYUBRR);
	CAN_init();
	servo_init();
	ADC_init();
	motor_init();
	DAC_init();
	sei();			//global interrupt enable

	
	

	
	while(1)
	{	
		if(rx_int_flag){
			Message recieve_msg = CAN_recieve();
			
			for (int i = 0; i < recieve_msg.length; i ++){
				//printf("%d", recieve_msg.data[i]);
				//printf("\n");
			}
			uint8_t joystick_pos_x = recieve_msg.data[0];
			uint8_t joystick_pos_y = recieve_msg.data[1];
			//printf("X = %d \t", recieve_msg.data[0]);
			//printf("y = %d \n", recieve_msg.data[1]);
			servo_set_pos(joystick_pos_y);
			motor_drive(joystick_pos_x);
			
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

