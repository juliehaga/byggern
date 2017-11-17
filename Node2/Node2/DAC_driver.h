/*
 * driver_DAC.h
 *
 * Created: 04.11.2017 15:32:18
 *  Author: julihag
 */ 


#ifndef DRIVER_DAC_H_
#define DRIVER_DAC_H_

#include <stdint.h>


void DAC_send_data(uint8_t data);
void DAC_init(void);



#endif /* DRIVER_DAC_H_ */