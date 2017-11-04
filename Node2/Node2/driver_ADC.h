/*
 * driver_ADC.h
 *
 * Created: 01.11.2017 17:35:15
 *  Author: julihag
 */ 


#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

#include <stdint.h>

void ADC_init(void); 
uint16_t ADC_read(void);


#endif /* DRIVER_ADC_H_ */