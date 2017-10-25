/*
 * Node2.c
 *
 * Created: 25.10.2017 11:49:48
 *  Author: andrholt
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include "driver_uart.h"
#include "SPI_driver.h"
#include "MCP2515_driver.h"
#include "CAN_driver.h"

volatile uint8_t rx_int_flag = 0;

int main(void)
{
	
	cli();
	UART_init(MYUBRR);
	CAN_init();
	sei();
	
	char* test = "Johanne\n";
	
	Message msg;
	msg.length = 8;
	for (int i = 0; i < msg.length; i++){
		msg.data[i] = test[i];
	}
	msg.ID = 0;
	CAN_send(&msg);
	
    while(1)
    {
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

	