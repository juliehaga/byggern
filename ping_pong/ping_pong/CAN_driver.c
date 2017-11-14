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
#include "joystick.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile uint8_t rx_int_flag; 

uint8_t last_joystick_pos_x = 0;
uint8_t last_slider_pos_l = 0;
uint8_t last_button_l = 0;

Message msg;

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
	MCP2515_bit_modify(MCP_CANCTRL, MODE_MASK , MODE_NORMAL);
	
	value = MCP2515_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_NORMAL) {
		printf("MCP2515 is NOT in normal mode!\n");
		return 1;
	}
	
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
	Message receive_msg; 
		
	
	receive_msg.ID = (MCP2515_read(MCP_RXB0SIDH) << 3 | MCP2515_read(MCP_RXB0SIDL) >> 5);
	receive_msg.length = MCP2515_read(MCP_RXB0DLC) & 0x0F;
	if(receive_msg.length > 8){
		receive_msg.length = 8;
	}
	for (int i = 0; i < receive_msg.length ; i++){
		receive_msg.data[i] = MCP2515_read(MCP_RXB0DM + i);
		//printf("Leser %c\n", msg.data[i]);
	}
	rx_int_flag = 0;
	
	return receive_msg; 
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


void CAN_send_controllers(void){
	
	uint8_t joy_pos_x = joystick_read(CHANNEL_X);
	//uint8_t joy_pos_y = joystick_read(CHANNEL_Y);
	//uint8_t slider_pos_r = slider_read(SLIDER_R);
	uint8_t slider_pos_l = slider_read(SLIDER_L);
	
	int button_l = button_read(1);

	if(abs(joy_pos_x - last_joystick_pos_x) > 10 || abs(slider_pos_l - last_slider_pos_l) > 10 || (button_l != last_button_l)){
		Message msg;
		
		msg.length = 3;
		msg.data[0] = joy_pos_x;
		msg.data[1] = slider_pos_l;
		msg.data[2] = button_l;
		msg.ID = 0;
		
		CAN_send(&msg);
		last_joystick_pos_x = joy_pos_x;
		last_slider_pos_l = slider_pos_l;
		last_button_l = button_l;
		
	}
}

void CAN_send_start(void){
	Message msg;
	msg.length = 1;
	msg.data[0] = 1;
	msg.ID = 0;
	
	CAN_send(&msg);
}

ISR(INT0_vect){
	//RX0 interrupt flag set to 0
	CAN_int_vect();
}

