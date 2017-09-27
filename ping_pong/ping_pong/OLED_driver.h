/*
 * OLED_driver.h
 *
 * Created: 20.09.2017 14:17:24
 *  Author: andrholt
 */ 



#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_
#include "stdint.h"



#define ASCII_OFFSET 32

void oled_init();
void oled_goto_page(int page);
void oled_home();
void oled_print_char(char c);
void oled_pos(int row,int column);
void oled_goto_column(int column);
void oled_fill_page(uint8_t page);
void oled_print_string(char* string);
int oled_return_page(void);
void oled_reset();



#endif /* OLED_DRIVER_H_ */