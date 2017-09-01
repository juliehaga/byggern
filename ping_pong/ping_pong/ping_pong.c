/*
 * ping_pong.c
 *
 * Created: 01.09.2017 09:13:19
 *  Author: julihag
 */ 


#include <avr/io.h>
#include "driver_uart.h"
#include "bit_functions.h"
#include <util/delay.h>



int main(void)
{
   UART_init(31);
   while (1){
	   
	   /*UART_transmit('a');
	   _delay_ms(3000);
	   UART_transmit('b');
	   _delay_ms(3000);
	   */
	   char temp = UART_receive();
	   if (temp){
		   UART_transmit(temp);
	   }
	   
	 

	  
	   
	   
	   
	   //printf("Hello world\n");
		//char test = 'h';
	    //; 
		//USART_transmit('B'); 
   }
  
   
   return 0; 
}