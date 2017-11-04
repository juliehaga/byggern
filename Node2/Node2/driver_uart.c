/*
 * driver_ATmega162.c
 *
 * Created: 01.09.2017 09:14:11
 *  Author: julihag
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "bit_functions.h"
#include "driver_uart.h"

FILE *uart; 



int UART_init(unsigned int ubrr){
/* 
Set baud rate
 */
	UBRR0L = ubrr;

/* 
Enable receiver and transmitter
 */
	UCSR0B =(1<<RXEN0)|(1<<TXEN0);
	
	uart = fdevopen(&UART_transmit, &UART_receive);
	
	
	return 0; 
}



int UART_transmit(unsigned char data, FILE *stream){
	
	//Wait for empty transmit buffer
	
	while(!( UCSR0A & (1<<UDRE0)) );
 
	//Put data into buffer, sends the data
 
	UDR0 = data;
	return 0; 
}

unsigned char UART_receive(){

	//Wait for data to be received

	while( !(UCSR0A & (1<<RXC0)) );
 
	//Get and return received data from buffer
 
	return UDR0;
}

unsigned char UART_receiveT(){

	//Wait for data to be received

	while( !(UCSR0A & (1<<RXC0)) );
	
	//Get and return received data from buffer
	
	return UDR0;
}

