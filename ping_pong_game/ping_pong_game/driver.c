
#ifndef driver
#define driver
#include <avr/io.h>
#include "driver.h"


void USART_Init(unsigned int ubrr ){
/* 
Set baud rate
 */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UBRR1H = (unsigned char)ubrr;
	UBRR1L = (unsigned char)ubrr;
/* 
Enable receiver and transmitter
 */
	UCSR0B = (1<<RXCIE0)|(1<<TXCIE0);
/* 
Set frame format: 8data, 2stop bit
 */
	UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
}

//URSEL - USART register select: Controls which of the two registers will be written
// 0 - UBRRH
// 1 - UCSRC


void USART_transmit(unsigned char data){
	/* 
	Wait for empty transmit buffer
	*/
	while( !( UCSR0A & (1<<UDRE0)) );
/* 
Put data into buffer, sends the data
 */
	UDR1 = data;
}


unsigned char USART_Recieve(void){
	/*wait for data to be recieved*/
	while(!(UCSR0A & (1<<RXC0)));
	
	/*get and return recieved data from buffer*/
	return UDR1;
}


#endif