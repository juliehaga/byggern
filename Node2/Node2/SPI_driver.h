/*
 * SPI_driver.h
 *
 * Created: 11.10.2017 11:25:49
 *  Author: andrholt
 */ 

#include "stdint.h"

#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_
#define FOSC2 16000000
#define SCK PB1
#define MISO PB3
#define MOSI PB2
#define SS PB0


void SPI_init(void);
uint8_t SPI_read_write(char cData);
void SPI_activate_SS(void);
void SPI_deactivate_SS(void);


#endif /* SPI_DRIVER_H_ */