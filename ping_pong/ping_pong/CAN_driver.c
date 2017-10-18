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


int rx_int_flag = 0; 

void CAN_init(){
	//config-mode
	MCP2515_init();
	
	//enable interrupts in MCP
	//Interrupt when message received in RXB0
	MCP2515_bit_modify(MCP_CANINTE, 0x01, 0x01);	
	
	//enable interrupts in MCU
	MCUCR |= (1<<ISC00);
	MCUCR |= (1<<ISC01);
	GICR |= (1<<INT0);
	
	//Set loopback-mode
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK , MODE_LOOPBACK);
	

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
		MCP2515_request_to_send(0);
	}
}

int CAN_transmit_complete(){
	
	if ( test_bit(MCP2515_read(MCP_TXB0CTRL), 3)){
		return 0;
	}
	return 1;
}

Message CAN_recieve(){
	Message msg = {0,7,"no_data"}; 
	
	if(rx_int_flag){
		msg.ID = (MCP2515_read(MCP_RXB0SIDH) << 3 | MCP2515_read(MCP_RXB0SIDL) >> 5);
		msg.length = MCP2515_read(MCP_RXB0DLC) & 0x0F;

		for (int i = 0; i < msg.length ; i++){
			msg.data[i] = MCP2515_read(MCP_RXB0DM + i);
		}
	
	rx_int_flag = 0;
	}
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
}

ISR(INT0_vect){
	//RX0 interrupt flag set to 0
	CAN_int_vect();
}