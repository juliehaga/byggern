/*
 * SPI_driver.c
 *
 * Created: 11.10.2017 11:25:25
 *  Author: andrholt
 */ 

#include "SPI_driver.h"
#include "bit_functions.h"
#include <avr/io.h>
#include <util/delay.h>



void SPI_init_ps2(void){
	//SPI enable
	set_bit(SPCR, SPE); 
	//Data order LSB transmitted first
	set_bit(SPCR, DORD); 
	//Set SPI to master mode
	set_bit(SPCR, MSTR);

	//Clock polarity SCK is high when idle
	set_bit(SPCR, CPOL); 
	//Clock phase transmit
	set_bit(SPCR, CPHA);
	
	//Clock frequency to f_OSC/16
	//PS2 console has frequency 500 kHz
	set_bit(SPSR, SPR0);
	
	//set MOSI and SCK to output, all others input
	set_bit(DDRB, MOSI);
	set_bit(DDRB, SCK);
	set_bit(DDRB, SS);  //til CAN
	set_bit(DDRB, PB3); //ATT
}

uint8_t SPI_read_write(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(test_bit(SPSR, SPIF)));   //wait until SPIF-flag is set. 
	return SPDR;
}

uint8_t SPI_read_write_PS2(char cData){
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(test_bit(SPSR, SPIF)));   //wait until SPIF-flag is set.
	_delay_ms(30);
	return SPDR;
}


void SPI_activate_SS(){
	clr_bit(PORTB, SS);
}

void SPI_deactivate_SS(){
	set_bit(PORTB, SS);
}

void SPI_activate_SS_PS2(){
	clr_bit(PORTB, PB3);
}

void SPI_deactivate_SS_PS2(){
	set_bit(PORTB, PB3);
}