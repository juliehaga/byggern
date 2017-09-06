/*
 * ping_pong.c
 *
 * Created: 01.09.2017 09:13:19
 *  Author: julihag
 */ 


#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "driver_uart.h"
#include "bit_functions.h"

int main(void)
{
	
   UART_init(31);
   unsigned char a[8] = "hewf"; 
   
   //unsigned char t = UART_receive();

   while (1){

		printf("%s\n", a);
		scanf("%s", &a);
		//unsigned char t = UART_receiveT();
		//printf("Here %c\n", t);
		

	   /*UART_transmit('a');
	   
	   UART_transmit('b');
	   _delay_ms(3000);
	   
	   char temp = UART_receive();
	   if (temp){
		   UART_transmit(temp);
	   }
	   */
	   	   
	   //printf("Hello world\n");
		//char test = 'h';
	    //; 
		//USART_transmit('B'); 
	}
	return 0; 
}