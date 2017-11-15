/*
 * OLED_driver.c
 *
 * Created: 20.09.2017 14:17:39
 *  Author: andrholt
 */ 
#include "OLED_driver.h"
#include <avr/pgmspace.h>
#include "fonts.h"
#include "joystick.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"



volatile char* OLED_c = (char*) 0x1000; //Write to address OLED command
volatile char* OLED_d = (char*) 0x1200; //Write to address OLED data
volatile char* SRAM = (char*) 0x1800; 


joystick_dir prev_joy_dir = CENTER;
static uint8_t current_page, current_col;
char* highscore_names[5];
int highscore_scores[5];

void oled_init(){
	//  display  off
	*OLED_c = 0xae;

	//segment  remap
	*OLED_c = 0xa1;	

	//common  pads  hardware:  alternative		
	*OLED_c = 0xda;			
	*OLED_c = 0x12;

	//common output scan direction:com63~com0
	*OLED_c = 0xc8;

	//multiplex  ration  mode:63
	*OLED_c = 0xa8;
	*OLED_c = 0x3f;

	//display divide ratio/osc. freq. mode
	*OLED_c = 0xd5;
	*OLED_c = 0x80;

	//contrast  control
	*OLED_c = 0x81;
	*OLED_c = 0x50;

	//set  pre-charge  period
	*OLED_c = 0xd9;
	*OLED_c = 0x21;

	 //Set  Memory  Addressing  Mode
	*OLED_c = 0x20;
	*OLED_c = 0x02;

	//VCOM  deselect  level  mode
	*OLED_c = 0xdb;
	*OLED_c = 0x30;

	//master  configuration
	*OLED_c = 0xad;

	//out follows RAM content 
	*OLED_c = 0x00;
	
	//set  normal  display
	*OLED_c = 0xa4;
	*OLED_c = 0xa6;
	
	//  display  on
	*OLED_c = 0xaf;
	
	

	
}
void oled_sram_reset(){
	for(int i = 0; i < 128*8; i++){
		SRAM[i] = ' ';
	}
}
void oled_reset(){
	
	for (uint8_t i = 0 ; i < 8; i++){
		oled_pos(i, 0);
		for (uint16_t i = 0 ; i < 128; i++){
			*OLED_d = 0x00;
		}
	}
}

void oled_goto_page(int page){
	*OLED_c = (page | 0xb0);
	current_page = page;
}


void oled_goto_column(int column){
	*OLED_c = (column & 0x0f); //clearer de 4 første bitsene
	*OLED_c = ((column & 0xf0) >> 4) | (0x10);
	current_col = column;
}

int oled_return_page(void){
	return current_page;
}

void oled_pos(int row,int column){
	oled_goto_page(row);
	oled_goto_column(column);
}


void oled_home(){
	oled_pos(0,0);
}


void oled_fill_page(uint8_t page){
	oled_pos(page, 0);
	for (uint16_t i = 0 ; i < 128; i++){
		*OLED_d = 0xff;
	}
}

void oled_print_char(char c){
	for (uint8_t i = 0 ; i < 8 ; i++){  //i < 8 fordi vi bruker font8
		*OLED_d = pgm_read_byte(&(font8[c - ASCII_OFFSET][i]));
	}
}


void oled_update(){
	oled_reset();
	oled_home();
	for(int i = 0; i<8; i++){
		oled_pos(i,0);
		for(int j = 0; j < 16; j++){
			oled_print_char(oled_read_SRAM(i, j)); 
		}
	}
}

void oled_sram_string(char* string, int page, int start_col){
	int col = start_col;
	
	for(uint8_t i = 0 ; i < strlen(string) ; i++){
		if (i+start_col == 16){
			//16 char per column, linjeskift
			page = (page+1)%8;
			col = start_col;
		}
		oled_sram_char(string[i], page, col);
		col++;
	}
}


void oled_sram_char(char c, int page, int col){
	SRAM[128 * page + col] = c;
}


char oled_read_SRAM(int page, int col){
	return SRAM[128 * page + col];
}

char* oled_type_in_name(char* score){
	char* name = "AAA";
	//char* score_send = "";
	//itoa(score, score_send, 10);
	oled_sram_reset();
	oled_sram_string("NEW HIGHSCORE", 0, 0);
	oled_sram_string("^", 3, 0);
	oled_sram_string(name, 4, 0);
	oled_sram_string("v", 5, 0);
	oled_sram_string(score, 4, 10);
	oled_update();
	int i = 0;
	char current_letter = 'A';

	while (i < 3){
		if(button_read(RIGHT_BUTTON)){
			break;
		}
		joystick_dir joy_dir = find_joystick_dir();
		if(prev_joy_dir != joy_dir){
			
			switch(joy_dir){
				case UP:
					if(current_letter == 'A'){
						current_letter = 'Z';
					}else{
					current_letter--;
					}
					break;
				case DOWN:
					if(current_letter == 'Z'){
						current_letter = 'A';
						}else{
						current_letter++;
						break;
					}
				case RIGHT:
					if(i < 2){
						current_letter = 'A';
						i++;
						oled_sram_string("^", 3, i);
						oled_sram_string("v", 5, i);
						oled_sram_string(" ", 3, i-1);
						oled_sram_string(" ", 5, i-1);
					}
					break;
				case LEFT:
					if(i>0){
						current_letter = name[i-1];
						i--;
						oled_sram_string("^", 3, i);
						oled_sram_string("v", 5, i);
						oled_sram_string(" ", 3, i+1);
						oled_sram_string(" ", 5, i+1);
					}
					break;
				default:
					break;
				
	
				
			}
			prev_joy_dir = joy_dir;
			name[i] = current_letter;
			oled_sram_string(name, 4, 0);
			oled_update();
		}		
	}
	return name;
}

void oled_play_game(int life, int score){
	char* score_send = ""; 
	itoa(score, score_send, 10);
	oled_sram_reset();
	oled_sram_string("PINGPONG GAME", 0, 0);
	oled_sram_string("LIVES", 3, 0);
	oled_sram_string("SCORE", 3, 9);
	oled_sram_char(life + '0', 5, 2);
	oled_sram_string(score_send, 5, 10);
	oled_update();
		
}
void oled_game_over(void){
	oled_sram_reset(); 
	oled_sram_string("YOU LOSE", 4, 0); 
	oled_update(); 
}

void oled_play_again(){
	oled_sram_reset();
	oled_sram_string("Play again?", 0, 0); 
	oled_sram_string("YES", 4, 0); 
	oled_sram_string("NO", 4, 9);
	oled_update();
}

void oled_print_highscore(){
	oled_sram_reset();
	oled_sram_string("HIGHSCORE", 0, 3);
	for(int i = 0; i < 5 ; i++){
		oled_sram_string(int_to_str(i+1),i+1, 0);
		oled_sram_string(".", i+1, 1);
		oled_sram_string(highscore_names[i], i+1, 3);
		oled_sram_string(int_to_str(highscore_scores[i]), i+1, 10);
	}
	oled_update();
}

char* int_to_str(int data){
	char* data_str = "";
	itoa(data, data_str, 10);
	return data_str;
}

/*
void read_highscore_list(void){
	FILE *fp; 
	fp = fopen("highscore.txt","a");
	char read_string[255];
	fgets(read_string, 255, (FILE*)fp);
	for(int i = 0; i < 30; i++){
		printf("bokstav: %c", read_string[i]);
	}
	
	
	fclose(fp);
	
}
*/