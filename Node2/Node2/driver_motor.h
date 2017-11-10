/*
 * driver_motor.h
 *
 * Created: 04.11.2017 14:41:14
 *  Author: julihag
 */ 


#ifndef DRIVER_MOTOR_H_
#define DRIVER_MOTOR_H_

#include <stdint.h>

void motor_init(void); 
void motor_drive(int joystick_value);
void motor_set_dir(int dir);
void motor_reset_encoder(void);
int16_t motor_read_encoder(void); 
int motor_velocity(void);
void motor_PI(int joystick_value);
void motor_calibration(void);


#endif /* DRIVER_MOTOR_H_ */