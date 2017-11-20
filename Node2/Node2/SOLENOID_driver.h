/*
 * driver_solenoid.h
 *
 * Created: 12.11.2017 14:48:48
 *  Author: julihag
 */ 


#ifndef DRIVER_SOLENOID_H_
#define DRIVER_SOLENOID_H_
#include <avr/io.h>

void solenoid_init(void);
void solenoid_shoot(void);

#endif /* DRIVER_SOLENOID_H_ */