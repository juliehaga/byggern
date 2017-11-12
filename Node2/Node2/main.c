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
	DAC_init();
	motor_init();
	sei();			//global interrupt enable
	
	motor_calibration();

	while(1)
	{	
		//printf("ENCODER: %d\n",motor_read_encoder());
		if(rx_int_flag){
			printf("can received \n");
			Message recieve_msg = CAN_recieve();
			
			for (int i = 0; i < recieve_msg.length; i ++){
				//printf("%d", recieve_msg.data[i]);
				//printf("\n");
			}
			uint8_t joystick_pos_x = recieve_msg.data[1];
			uint8_t slider_pos_r = recieve_msg.data[0];
			//printf("servo = %d \t", recieve_msg.data[1]);
			//printf("slider = %d \n", recieve_msg.data[0]);
			servo_set_pos(joystick_pos_x);
			motor_PI(slider_pos_r);
			
			
		}
		
		
		
		
		//printf("%d\n",motor_read_encoder());
		

		/*
		if(IR_game_over()){
		printf("Digital filter: %d \n", IR_digital_filter());
		printf("you loose \n");
		}*/
		

		_delay_ms(1);
		
		
	}
	return 0;
}

