
/*
 * highscore.c
 *
 * Created: 15.11.2017 15:44:32
 *  Author: julihag
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "highscore.h"
#include "OLED_driver.h"

void oled_print_highscore(void){
	oled_sram_reset();
	oled_sram_string("HIGHSCORE", 0, 3);
	read_highscore_list();
	
	for(int i = 0; i < 5 ; i++){
		oled_sram_string(highscore_names[i], i+2, 3);
		oled_sram_string(int_to_str(i+1),i+2, 0);
		oled_sram_string(".", i+2, 1);
		oled_sram_string(int_to_str(highscore_scores[i]), i+2, 10);
		
	}
	oled_update();
}


int check_highscore(int score){
	for (int i = 0; i < 5 ; i++ ){
		if(score > highscore_scores[i]){
			return i;
		}
	}
	return -1;
}

void insert_highscore(int place, int score, char* new_name){
	for(int j = 4 ; j > place ; j--){
		highscore_scores[j] = highscore_scores[j-1];
		highscore_names[j] =  highscore_names[j-1];
	}
	highscore_scores[place] = score;
	highscore_names[place] =  new_name;
	update_highscore_list();
}
	
	
void read_highscore_list(void){
	for (int i = 0; i < 5 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			highscore_names[i][j] = EEPROM_read(3*i+j);
		}
	}
	for (int i = 0; i < 5 ; i++){
		highscore_scores[i] = EEPROM_read(i+15);
	}
}

void update_highscore_list(void){
	for (int i = 0; i < 5 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			EEPROM_write(highscore_names[i][j], 3*i+j);
		}
	}
	for (int i = 0; i < 5 ; i++){
		EEPROM_write(highscore_scores[i], 15+i);
	}
}


void EEPROM_write(uint8_t ucData, unsigned int uiAddress){
	/* 
	Wait for completion of previous write
	*/
	cli();
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
	sei(); 
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

void reset_highscore_list(){
	for (int i = 0; i < 5 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			EEPROM_write('-', 3*i+j);
		}
	}
	for (int i = 0; i < 5 ; i++){
		EEPROM_write(0, 15+i);
	}
}