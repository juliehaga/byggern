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
#include "TWI_Master.h"

volatile uint8_t rx_int_flag = 0;

int main(void)
{
	
	cli();
	UART_init(MYUBRR);
	CAN_init();
	servo_init();
	ADC_init();
	TWI_Master_Initialise();
	sei();			//global interrupt enable
	/*
	char* test = "Johanne\n";
	
	Message msg;
	msg.length = 8;
	for (int i = 0; i < msg.length; i++){
		msg.data[i] = test[i];
	}
	msg.ID = 0;
	CAN_send(&msg);
	*/
	//pwm_set_pulse_width(0.015);
	
    while(1)
    {
		
		
		if(rx_int_flag){
			Message recieve_msg = CAN_recieve();
			
			for (int i = 0; i < recieve_msg.length; i ++){
				printf("%d", recieve_msg.data[i]);
				printf("\n");
			}
			uint8_t joystick_pos = recieve_msg.data[0];
			servo_set_pos(joystick_pos);
			
			
		}
		
	/*
		if(IR_game_over()){
			printf("Digital filter: %d \n", IR_digital_filter());
			printf("you loose \n");
		}
*/
		
		
		_delay_ms(1);
		
		
	}
	return 0;
}

	