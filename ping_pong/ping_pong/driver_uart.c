/*
 * driver_ATmega162.c
 *
 * Created: 01.09.2017 09:14:11
 *  Author: julihag
 */ 

#include <avr/io.h>
#include "bit_functions.h"

int UART_init(unsigned int ubrr ){
/* 
Set baud rate
 */
	UBRR0L = ubrr;
	//UBRR0H = (unsigned char)(ubrr>>8);
	//UBRR0L = (unsigned char)ubrr;
/* 
Enable receiver and transmitter
 */
	UCSR0B =(1<<RXEN0)|(1<<TXEN0);
	//set_bit(UCSR0B,RXCIE0);
	//set_bit(UCSR0B,TXCIE0);
	
/* 
Set frame format: 8data, 2stop bit
 */
	//set_bit(UCSR0C,URSEL0);
	//set_bit(UCSR0C,USBS0);
	//set_bit(UCSR0C,UCSZ00);
	
	return 0; 

}

int UART_transmit(unsigned char data){
	
	//Wait for empty transmit buffer
	
	while( !( UCSR0A & (1<<UDRE0)) );
 
	//Put data into buffer, sends the data
 
	UDR0 = data;
	return 0; 
}

unsigned char UART_receive(void){

	//Wait for data to be received

	while( !(UCSR0A & (1<<RXC0)) );
 
	//Get and return received data from buffer
 
	return UDR0;
}