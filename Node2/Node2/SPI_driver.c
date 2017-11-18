/*
 * SPI_driver.c
 *
 * Created: 11.10.2017 11:25:25
 *  Author: andrholt
 */ 

#include <stdio.h>
#include <avr/io.h>
#include "SPI_driver.h"
#include "bit_functions.h"

void SPI_init(void){
	//Set SPI to master mode
	set_bit(SPCR, MSTR);
	//set SPI clock rate = Fosc/16 
	set_bit(SPCR, SPR0);
	
	////Clock polarity SCK is high when idle
	set_bit(SPCR, CPOL);
	////Clock phase transmit
	set_bit(SPCR, CPHA);
	
	//set MOSI and SCK to output, all others input
	set_bit(DDRB, MOSI);
	set_bit(DDRB, SCK);
	set_bit(DDRB, SS);
	set_bit(DDRB, PB0);

	//SPI enable
	set_bit(SPCR, SPE);
	SPI_deactivate_SS();
}

uint8_t SPI_read_write(char cData){
	/* Start transmission */
	SPDR = cData;
	
	/* Wait for transmission complete */
	while(!(test_bit(SPSR, SPIF)));   //wait until SPIF-flag is set. 
	return SPDR;
}

void SPI_activate_SS(){
	clr_bit(PORTB, SS);
}

void SPI_deactivate_SS(){
	set_bit(PORTB, SS);
}

