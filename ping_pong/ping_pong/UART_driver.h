/*
 * driver_ATmega.h
 *
 * Created: 01.09.2017 09:14:28
 *  Author: julihag
 */ 


#ifndef DRIVER_ATMEGA_H_
#define DRIVER_ATMEGA_H_

#define FOSC 4915200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

#include <stdio.h>

int UART_init( unsigned int ubrr);
unsigned char UART_receive();
int UART_transmit(unsigned char data, FILE *stream);
unsigned char UART_receiveT();
extern FILE *uart; 

#endif /* DRIVER_ATMEGA_H_ */