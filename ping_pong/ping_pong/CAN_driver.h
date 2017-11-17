/*
 * CAN_driver.h
 *
 * Created: 11.10.2017 14:54:57
 *  Author: andrholt
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_
#include "stdint.h"

typedef struct Message{
	int ID;
	int length;
	uint8_t data[8];			//One message is max 8 characters
	}Message;

int CAN_init();
void CAN_send(Message* msg);
int CAN_transmit_complete();
Message CAN_recieve(); 
int CAN_error(); 
void CAN_int_vect();  
void CAN_send_controllers(void);
void CAN_send_start(void);
void CAN_send_ps2_controllers(void);


#endif /* CAN_DRIVER_H_ */