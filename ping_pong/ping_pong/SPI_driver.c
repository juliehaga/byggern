/*
 * SPI_driver.c
 *
 * Created: 11.10.2017 11:25:25
 *  Author: andrholt
 */ 

#include "SPI_driver.h"
#include "bit_functions.h"
#include <avr/io.h>


void SPI_init(void){
	//SPI enable
	set_bit(SPCR, SPE);
	//Data order MSB transmitted first
	clr_bit(SPCR, DORD);
	//Set SPI to master mode
	set_bit(SPCR, MSTR);
	//set SPI clock rate = Fosc/16
	set_bit(SPCR, SPR0);
	
	//set MOSI and SCK to output, all others input
	set_bit(DDRB, MOSI);
	set_bit(DDRB, SCK);
	set_bit(DDRB, SS);

}

uint8_t SPI_read_write(char cData){
	/* Start transmission */
	
	SPDR = cData;


	printf("Test bit %d\n",test_bit(SPSR, SPIF));
	/* Wait for transmission complete */
	
	while(!(test_bit(SPSR, SPIF)));   //wait until SPIF-flag is set. 
	printf("forbi while, yei");

	return SPDR;
}

void SPI_activate_SS(){
	clr_bit(PORTB, SS);
}

void SPI_deactivate_SS(){
	set_bit(PORTB, SS);
}

