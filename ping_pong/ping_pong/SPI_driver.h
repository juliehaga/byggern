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
#define SCK PB7
#define MISO PB6
#define MOSI PB5
#define SS PB4


void SPI_init(void);
uint8_t SPI_read_write(char cData);
uint8_t SPI_read_write_PS2(char cData);
void SPI_activate_SS(void);
void SPI_deactivate_SS(void);
void SPI_activate_SS_2(void);
void SPI_deactivate_SS_2(void);


#endif /* SPI_DRIVER_H_ */