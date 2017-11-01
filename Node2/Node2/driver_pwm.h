/*
 * timer.h
 *
 * Created: 01.11.2017 10:39:41
 *  Author: julihag
 */ 


#ifndef TIMER_H_
#define TIMER_H_

void pwm_init(void);
void pwm_set_period(float sec);
void pwm_set_pulse_width(float sec);


#endif /* TIMER_H_ */