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
#include "sram_test.h"

int main(void)
{
	
   UART_init(31);
   
   register_init();
   

   
   //SRAM_test();
   //volatile char *ext_ram = (char *) 0x1000; // Start address for the SRAM 
   
   while (1){
	printf("hei\r\n");
	
	      
	}
	
	return 0; 
}