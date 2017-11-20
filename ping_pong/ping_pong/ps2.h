/* 
 * PS2 controller on Atmel MCU
 * 
 * V1.0  
 * 
 * By: Lars Ivar Miljeteig, September 2010
 * Platform: AVR ATmega168 (avr-gcc)
 * Dependencies: avr/io avr/interrupt delay.h stdint.h larslib.h
 *
 * Reading data from a PlayStation 2 controller
 */

#ifndef PS2_H

#include <stdint.h>

#define PS2_H
#define R2_BUTTON_MASK 0x02
#define PS2_MOTOR_ON 0x01
#define PS2_MOTOR_OFF 0x00


typedef struct ps2{
	uint8_t lx, ly, rx, ry;
} ps2;

volatile uint8_t rx_buffer[20];
ps2 joy_values;


void ps2_init(void);
void ps2_poll(void);
void ps2_configmode(void);
void ps2_analogmode(void);
void ps2_returnpres(void);
void ps2_digitalgmode(void);
void ps2_exitconfig(void);
int ps2_R2_pushed(void);
ps2 ps2_joystick_values(void);


#endif // PS2_H
