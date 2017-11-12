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
void motor_set_dir(void);
void motor_reset_encoder(void);
int16_t motor_read_encoder(void); 

int motor_PI(int joystick_value);
void motor_calibration(void);

typedef enum{RIGHT, LEFT} motor_dir;


#endif /* DRIVER_MOTOR_H_ */