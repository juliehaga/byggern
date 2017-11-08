/*
 * driver_DAC.c
 *
 * Created: 04.11.2017 15:32:05
 *  Author: julihag
 */ 

#include "driver_DAC.h"
#include "TWI_Master.h"
#include <avr/io.h>
#include "bit_functions.h"
#include <avr/interrupt.h>

void DAC_init(void){
	
	TWI_Master_Initialise();
	
	//prescale SCK to f_osc/64
	
	//set_bit(TWSR, TWPS1); 
	//set_bit(TWSR, TWPS0);
	
	
	//Set SDA og SCK til output
	set_bit(DDRD, PD0);
	set_bit(DDRD, PD1);
}

void DAC_send_data(uint8_t data){
	//Send motor voltage to DAC
	
	uint8_t address = 0b01010000; //8 bits slave address - OUT0
	uint8_t command = 0b00000000;		  //command choose DAC0
	
	uint8_t msg[3] = {address, command, data};
	printf("data = %d \n", data);
	TWI_Start_Transceiver_With_Data(msg, 3);
}
