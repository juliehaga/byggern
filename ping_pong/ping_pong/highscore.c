
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

	char c; 
	//Read highscorelist from Eeprom
	for (int i = 0; i < 5 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			c = EEPROM_read(3*i+j);
			oled_sram_char(c,i+2,3+j);
		}
		oled_sram_string(int_to_str(i+1),i+2, 0);
		oled_sram_string(".", i+2, 1);
		oled_sram_string(int_to_str(EEPROM_read(i+15)), i+2, 10);
		
	}
	oled_update();
}


int check_highscore(int score){
	for (int i = 0; i < 5 ; i++ ){
		if(score > (EEPROM_read(i+15))){
			return i;
		}
	}
	return -1;
}

void insert_highscore(int place, int score, char* new_name){
	//Shift names in highscorelist
	for(int j = 14; j >= place*3 +3 ; j--){
		EEPROM_write(EEPROM_read(j-3), j);
	}
	//Shift scores in highscorelist
	for (int k = 19; k > 15 + place; k--){
		EEPROM_write(EEPROM_read(k-1), k);
	}
	//Insert new score
	EEPROM_write(score, 15 + place);
	
	//Insert new name
	for (int i = 0; i < 3; i++){
		EEPROM_write(new_name[i], place*3+i);
	}
}


void EEPROM_write(uint8_t ucData, unsigned int uiAddress){
	/* 
	Wait for completion of previous write
	*/
	
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	cli();
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