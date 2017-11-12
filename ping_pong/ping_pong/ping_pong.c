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

int button_pushed = 0;



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
	
	
	menu_setup();

	
	while(1){
		printf("MENU: %d\n", main_menu());

		//CAN_send_msg();
		
		
	
		
		
		
		if(ADC_ready){
			ADC_ready = 0;
		}
		
	}
	return 0;
}

