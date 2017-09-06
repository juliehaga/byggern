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
#include "register_init.h"

int main(void)
{
	
   UART_init(31);
   
   register_init();
   
   
   
   
   set_bit(PORTE, PE1);
   
   
   
   set_bit(PORTC, PC3);
   set_bit(PORTC, PC2);
   set_bit(PORTC, PC1);
   set_bit(PORTC, PC0);
   
   
   
   
   
   
   //SRAM_test();
   
   
   while (1){
	
	   
	   //set_bit(PORTA,PA7);
	      
	}
	
	return 0; 
}