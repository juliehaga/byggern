/*
 * CAN_driver.c
 *
 * Created: 11.10.2017 14:54:47
 *  Author: andrholt
 */ 

#include "MCP2515.h"
#include "MCP2515_driver.h"
#include "CAN_driver.h"
#include "bit_functions.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

extern volatile uint8_t rx_int_flag; 

int CAN_init(){
	volatile uint8_t value;
	
	//config-mode
	MCP2515_init();
	_delay_ms(1);
	//enable interrupts in MCP
	//Interrupt when message received in RXB0
		
	
	
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_CONFIG) {
		printf("MCP2515 is NOT in config mode after reset!\n");
		return 1;
	}
	
	MCP2515_bit_modify(MCP_CANINTE, 0x01, 0x01);
	MCP2515_bit_modify(MCP_RXB0CTRL, 0x60, 0xFF);
	
	//Set loopback-mode
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK , MODE_LOOPBACK);
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_LOOPBACK) {
		printf("MCP2515 is NOT in loopback mode!\n");
		return 1;
	}
	printf("Successfully initialize CAN\n");
	return 0;
}


void CAN_send(Message* msg){
	if(CAN_transmit_complete()){
		
		//sending ID
		MCP2515_write(MCP_TXB0SIDH, (uint8_t)msg->ID >> 3);
		MCP2515_write(MCP_TXB0SIDL, (uint8_t)msg->ID << 5);
	
		//sending data length
		MCP2515_write(MCP_TXB0DLC, msg->length & 0x0F);
	
		//Sending data, max 8 bytes
		for (int i = 0; i < msg->length; i++){
			MCP2515_write(MCP_TXB0D0 + i, &msg->data[i]);  
		}
	
		//initiate message transmission
		
		MCP2515_request_to_send(1);
		printf("interrrr\n");
		printf("TXB0CTRL %02x\n", MCP2515_read(MCP_TXB0CTRL));
	}
}

int CAN_transmit_complete(){
	if ( test_bit(MCP2515_read(MCP_TXB0CTRL), 3)){
		return 0;
	}
	return 1;
}

Message CAN_recieve(){
	Message msg; 
		
	uint8_t status = MCP2515_read_status();
	uint8_t b = 'b'; 
	printf("Status: %2x\n", status);
	
	
	
	msg.ID = (MCP2515_read(MCP_RXB0SIDH) << 3 | MCP2515_read(MCP_RXB0SIDL) >> 5);
	msg.length = MCP2515_read(MCP_RXB0DLC) & 0x0F;

	for (int i = 0; i < msg.length ; i++){
		msg.data[i] = MCP2515_read(MCP_RXB0DM + i);
	}
	rx_int_flag = 0;
	return msg; 
}

int CAN_error(){
	if(test_bit(MCP2515_read(MCP_TXB0CTRL), 4)){
		return -1;
	} else if (test_bit(MCP2515_read(MCP_TXB0CTRL), 5)){
		return -2;
	}
	return 0; 
}

void CAN_int_vect(){
	//set flag to 0
	MCP2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
	rx_int_flag = 1;
	printf("rx flag satt til 1\n");
}

ISR(INT0_vect){
	printf("int vektor\n");
	//RX0 interrupt flag set to 0
	CAN_int_vect();
}