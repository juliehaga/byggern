/*
 * driver_motor.h
 *
 * Created: 04.11.2017 14:41:14
 *  Author: julihag
 */ 


#ifndef DRIVER_MOTOR_H_
#define DRIVER_MOTOR_H_


void motor_init(void); 
void motor_drive(int joystick_value);
void motor_set_dir(int dir);


#endif /* DRIVER_MOTOR_H_ */