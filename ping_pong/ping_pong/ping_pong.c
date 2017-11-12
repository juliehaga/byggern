/*
 * ping_pong.c
 *
 * Created: 01.09.2017 09:13:19
 *  Author: julihag
 */ 

#define F_CPU 4915200

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>


#include "driver_uart.h"
#include "bit_functions.h"
#include "register_init.h"
#include "sram_test.h"
#include "OLED_driver.h"
#include "ADC_driver.h"
#include "joystick.h"
#include "menu_framework.h"
#include "CAN_driver.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "MCP2515.h"


volatile uint8_t ADC_ready = 0;
volatile uint8_t rx_int_flag = 0;





//volatile uint8_t* a = 0x1400;


int main(void) {
	// Disable global interrupts
	cli();
	UART_init(31);
	register_init();
	oled_init();
	ADC_init();
	CAN_init();
	//Enable global interrupts
	sei();
	
	
	

	
	while(1){
		CAN_send_msg();
		
		//printf("Y %d \t", ADC_read(CHANNEL_X));
		//printf("X %d\n", ADC_read(CHANNEL_Y));
	
		if(ADC_ready){
			ADC_ready = 0;
		}
		
		/*
		if(rx_int_flag){
			//printf("flagget er satt til 1\n");
			Message recieve_msg = CAN_recieve();
			
			for (int i = 0; i < recieve_msg.length; i ++){
				printf("%c", recieve_msg.data[i]);
			}
		}
		*/
	}
	return 0;
}

