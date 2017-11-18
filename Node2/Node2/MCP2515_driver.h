/*
 * CAN_controller_driver.h
 *
 * Created: 11.10.2017 12:11:11
 *  Author: andrholt
 */ 


#ifndef CAN_CONTROLLER_DRIVER_H_
#define CAN_CONTROLLER_DRIVER_H_

#include "stdint.h"

void MCP2515_reset(void);
uint8_t MCP2515_read_status(void);
uint8_t MCP2515_read(uint8_t address);
void MCP2515_write(uint8_t address, char data);
void MCP2515_request_to_send(uint8_t command);
void MCP2515_bit_modify(uint8_t address, uint8_t mask_byte, uint8_t data_byte);

#endif /* CAN_CONTROLLER_DRIVER_H_ */