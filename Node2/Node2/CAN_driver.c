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
#include "SPI_driver.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>


extern volatile uint8_t rx_int_flag; 

int CAN_init(){
	volatile uint8_t value;
	printf("can init start\n");
	//config-mode
	SPI_init();
	MCP2515_reset();
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
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK , MODE_NORMAL);
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_NORMAL) {
		printf("MCP2515 is NOT in normal mode!\n");
		return 1;
	}
	
	//Set interrupts in MCU
	set_bit(PCMSK0, PCINT6);
	set_bit(PCICR, PCIE0);
	clr_bit(EICRA, ISC01);
	clr_bit(EICRA, ISC00);
		
	return 0;
}


void CAN_send(Message* msg){
	printf("Can send\n");
	if(CAN_transmit_complete()){
		
		//sending ID
		MCP2515_write(MCP_TXB0SIDH, (uint8_t)msg->ID >> 3);
		MCP2515_write(MCP_TXB0SIDL, (uint8_t)msg->ID << 5);
	
		//sending data length
		MCP2515_write(MCP_TXB0DLC, msg->length & 0x0F);
	
		//Sending data, max 8 bytes
		if(msg->length > 8){
			msg->length = 8;
		}
		for (int i = 0; i < msg->length; i++){
			MCP2515_write(MCP_TXB0D0 + i, msg->data[i]);  
		}
	
		//initiate message transmission
		
		MCP2515_request_to_send(1);
		
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
		
	
	msg.ID = (MCP2515_read(MCP_RXB0SIDH) << 3 | MCP2515_read(MCP_RXB0SIDL) >> 5);
	msg.length = MCP2515_read(MCP_RXB0DLC) & 0x0F;
	if(msg.length > 8){
		msg.length = 8;
	}
	for (int i = 0; i < msg.length ; i++){
		msg.data[i] = MCP2515_read(MCP_RXB0DM + i);
		//printf("Leser %c\n", msg.data[i]);
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
	//set recieve flag to 0
	MCP2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
	//set transmit flag to 0 
	MCP2515_bit_modify(MCP_CANINTF, 0x04, 0x00);
	rx_int_flag = 1;
	
}

ISR(PCINT0_vect){
	//RX0 interrupt flag set to 0
	CAN_int_vect();
}