/*
 * ps2.c
 *
 * Created: 11.10.2017 11:25:25
 *  Author: johanndk
 */ 


#include <util/delay.h>
#include <avr/io.h>
#include "bit_functions.h"
#include "ps2.h"
#include "SPI_driver.h"

// Commands for the controller
const uint8_t PS2_CONFIGMODE[5] = {0x01, 0x43, 0x00, 0x01, 0x00};
const uint8_t PS2_ANALOGMODE[9] = {0x01, 0x44, 0x00, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00};
const uint8_t PS2_DIGITALMODE[9] = {0x01, 0x44, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00};
const uint8_t PS2_SETUPMOTOR[9] = {0x01, 0x4D, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff};
const uint8_t PS2_RETURNPRES[9] = {0x01, 0x4f, 0x00, 0xFF, 0xFF, 0x03, 0x00, 0x00, 0x00};
const uint8_t PS2_EXITCONFIG[9] = {0x01, 0x43, 0x00, 0x00, 0x5a, 0x5a, 0x5a, 0x5a, 0x5a};


// Initialize the ps2 controller
void ps2_init()
{
	uint8_t d = 0x00;
	// Attention pin idle high
	_delay_ms(10);
	
	// Configure controller to send everything
	ps2_configmode();
	_delay_ms(250);
	ps2_analogmode();
	_delay_ms(250);
	ps2_returnpres();
	_delay_ms(250);
	ps2_exitconfig();
	
	SPI_deactivate_SS_PS2();

}


void ps2_poll(void)
{
    uint8_t i = 0;
	set_bit(PORTB, MOSI);
	set_bit(PORTB,SCK);

    SPI_activate_SS_PS2(); 

    // Send command main polling
    rx_buffer[0] = SPI_read_write_PS2(0x01); //ID
    rx_buffer[1] = SPI_read_write_PS2(0x42); 
    rx_buffer[2] = SPI_read_write_PS2(0x00); //get Data
	
    // Buttons:
    rx_buffer[3] = SPI_read_write_PS2(0x00); 
    rx_buffer[4] = SPI_read_write_PS2(0x00);     

    // Joystick:
    joy_values.rx = SPI_read_write_PS2(0x00);
    joy_values.ry = SPI_read_write_PS2(0x00);
    joy_values.lx = SPI_read_write_PS2(0x00);
    joy_values.ly = SPI_read_write_PS2(0x00);

	_delay_ms(1);
    SPI_deactivate_SS_PS2(); 
}


void ps2_send_cmd(const uint8_t *cmd, uint8_t length)
{
    uint8_t i = 0;
    SPI_activate_SS_PS2();
    for(i=0; i<length; i++){
		 rx_buffer[i] = SPI_read_write_PS2(cmd[i]);
	}
    SPI_deactivate_SS_PS2();    
}


void ps2_configmode()
{
    ps2_send_cmd(PS2_CONFIGMODE, 5);
}


void ps2_analogmode()
{
    ps2_send_cmd(PS2_ANALOGMODE, 9);
}

void ps2_digitalgmode()
{
	ps2_send_cmd(PS2_ANALOGMODE, 9);
}


void ps2_returnpres()
{
    ps2_send_cmd(PS2_RETURNPRES, 9);
}

void ps2_exitconfig()
{
    ps2_send_cmd(PS2_EXITCONFIG, 9);
}


int ps2_R2_pushed(void){
	//Shooter button
	return !((rx_buffer[4] & R2_BUTTON_MASK) == 2);
}

ps2 ps2_joystick_values(void){
	return joy_values;
}
