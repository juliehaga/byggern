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
void motor_power(int joystick_value);
void motor_set_dir(void);
void motor_reset_encoder(void);
int16_t motor_read_encoder(void); 
int16_t motor_read_encoder_unscaled(void);

int motor_PID(int slider_value, float Kp, float Ki, float Kd);
void motor_calibration(void);
void motor_velocity_control(int joystick_value);


typedef enum{RIGHT, LEFT} motor_dir;


#endif /* DRIVER_MOTOR_H_ */