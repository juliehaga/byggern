/*
 * ADC_driver.h
 *
 * Created: 20.09.2017 10:47:40
 *  Author: andrholt
 */ 


#ifndef ADC_DRIVER_H_
#define ADC_DRIVER_H_
#include "stdint.h"



int ADC_init(void);
uint8_t ADC_read(uint8_t channel);
int joy_stick_read(int channel);
int slider_read(int channel);
int buttons_read(int button);



#endif /* ADC_DRIVER_H_ */