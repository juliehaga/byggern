
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
void read_highscore_list(void);
void update_highscore_list(void);
void insert_highscore(int place, int score, char* new_name);
void EEPROM_write(uint8_t ucData, unsigned int uiAddress);
void reset_highscore_list();
unsigned char EEPROM_read(unsigned int uiAddress);

static char* highscore_names[5] = {"AND", "JOH", "JUL", "AAA", "BEN"};
static int highscore_scores[5] = {10, 8, 7, 6, 5};
	
#endif /* HIGHSCORE_H_ */