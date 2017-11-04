/*
 * driver_DAC.c
 *
 * Created: 04.11.2017 15:32:05
 *  Author: julihag
 */ 

#include "driver_DAC.h"
#include "TWI_Master.h"


void DAC_send_data(uint8_t data){
	//Send motor voltage to DAC
	
	uint8_t address = 0b01010000; //Slave address - OUT0
	uint8_t command = 0b0		  //Command - hvorfor 0?
	
	uint8_t message[3] = {address, command, data};
	
	TWI_Start_Transceiver_With_Data(message, 3);
}
