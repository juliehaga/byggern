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

void oled_init(void);
void oled_goto_page(int page);
void oled_home(void);
void oled_print_char(char c);
void oled_pos(int row,int column);
void oled_goto_column(int column);
void oled_fill_page(uint8_t page);
void oled_print_string(char* string);
int oled_return_page(void);
void oled_reset(void);
void oled_update(void);
void oled_sram_string(char* string, int page, int start_col);
void oled_sram_char(char c, int page, int col);
char oled_read_SRAM(int page, int col);
void oled_sram_reset(void);
char* oled_type_in_name( char* score);
void oled_play_game(int life, int score); 
void oled_game_over(void); 
void oled_play_again(void);

char* int_to_str(int data);


#endif /* OLED_DRIVER_H_ */