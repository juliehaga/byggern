
/*
 * highscore.h
 *
 * Created: 15.11.2017 15:44:46
 *  Author: julihag
 */ 

#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

void oled_print_highscore(void);
int check_highscore(int score);
void insert_highscore(int place, int score, char* new_name);
void EEPROM_write(uint8_t ucData, unsigned int uiAddress);
unsigned char EEPROM_read(unsigned int uiAddress);
void reset_highscore_list(void);


	
#endif /* HIGHSCORE_H_ */