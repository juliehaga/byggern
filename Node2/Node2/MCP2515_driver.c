/*
 * CAN_controller_driver.c
 *
 * Created: 11.10.2017 12:10:56
 *  Author: andrholt
 */ 

#include "SPI_driver.h"
#include "MCP2515.h"
#include "MCP2515_driver.h"
#include <string.h>


void MCP2515_reset(void){
	SPI_activate_SS();
	SPI_read_write(MCP_RESET);
	SPI_deactivate_SS();
}

uint8_t MCP2515_read(uint8_t address){
	uint8_t data;
	SPI_activate_SS();
	SPI_read_write(MCP_READ);
	SPI_read_write(address);
	data = SPI_read_write(0x00);
	SPI_deactivate_SS();
	return data;
}

void MCP2515_write(uint8_t address, char data){
	SPI_activate_SS();
	SPI_read_write(MCP_WRITE);
	SPI_read_write(address);
	SPI_read_write(data);
	SPI_deactivate_SS();
}

 void MCP2515_request_to_send(uint8_t command){
	SPI_activate_SS();
	if (command <= 7){
		SPI_read_write(MCP_RTS | command);
	}
	else{
		SPI_read_write(MCP_RTS);
	}
	SPI_deactivate_SS();
}

uint8_t MCP2515_read_status(void){
	uint8_t status;
	SPI_activate_SS();
	SPI_read_write(MCP_READ_STATUS);
	status = SPI_read_write(0xFF);
	status = SPI_read_write(0xFF);		//send same data two times
	SPI_deactivate_SS();	
	return status;
}


void MCP2515_bit_modify(uint8_t address, uint8_t mask_byte, uint8_t data_byte){
	SPI_activate_SS();
	SPI_read_write(MCP_BITMOD);
	SPI_read_write(address);
	SPI_read_write(mask_byte);
	SPI_read_write(data_byte);
	SPI_deactivate_SS();
}