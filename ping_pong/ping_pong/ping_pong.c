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
   
   set_bit(DDRA,PA7);
   set_bit(DDRE, DDE1);
   set_bit(PORTE, PE1);	
   
   //enabler SRAM i MCU
   set_bit(MCUCR, SRE);
   set_bit(SFIOR, XMM0);
   
   
   SRAM_test();
   
   
   while (1){
	  
	   
	   //set_bit(PORTA,PA7);
	      
	}
	
	return 0; 
}