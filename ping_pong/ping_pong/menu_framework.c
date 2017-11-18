/*
 * menu_framework.c
 *
 * Created: 27.09.2017 14:05:47
 *  Author: andrholt
 */ 

#include "OLED_driver.h"
#include "menu_framework.h"
#include "UART_driver.h"
#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>


#include <stddef.h>

int current_page = 1;
menu* display_menu;
static menu* current_menu;
joystick_dir last_joy_dir = CENTER;
int difficulty = EASY;


extern states current_state; 


void menu_setup(void){
	menu* menu_front_page = create_menu("PingPongShow");
	display_menu = menu_front_page;

	menu* play = create_menu("Start new game");
	menu* highscore_menu = create_menu("Highscore");
	menu* play_usb = create_menu("Control: USB");
	menu* play_ps2 = create_menu("Control: PS2");
	menu* usb_easy = create_menu("Easy");
	menu* usb_medium = create_menu("Medium");
	menu* usb_hard = create_menu("Hard");
	menu* ps2_easy = create_menu("Easy");
	menu* ps2_medium = create_menu("Medium");
	menu* ps2_hard = create_menu("Hard");
	menu* highscore_view = create_menu("View");
	menu* highscore_reset = create_menu("Reset");
	menu* reset_yes = create_menu("YES");
	menu* reset_no = create_menu("NO");
	
	create_submenu(menu_front_page, play);
	create_submenu(menu_front_page, highscore_menu);
	create_submenu(play, play_usb);
	create_submenu(play, play_ps2);
	create_submenu(play_usb, usb_easy);
	create_submenu(play_usb, usb_medium);
	create_submenu(play_usb, usb_hard);
	create_submenu(play_ps2, ps2_easy);
	create_submenu(play_ps2, ps2_medium);
	create_submenu(play_ps2, ps2_hard);
	create_submenu(highscore_menu, highscore_view);
	create_submenu(highscore_menu, highscore_reset);
	create_submenu(highscore_reset, reset_yes);
	create_submenu(highscore_reset, reset_no);
	
	oled_reset();
	menu_sram_update(display_menu, current_page);
	oled_update();
	current_menu = display_menu->child;
}




void menu_sram_update(menu* menu_node, int selector_pos){
	int col = 0; 
	int page = 0; 
	oled_sram_reset();
	
	menu* current = menu_node->child;
	
	oled_sram_string(menu_node->name, page, col);
	oled_sram_string("----------------", page+1, col);
	
	
	page = 2;
	col = 2;
	while(current != NULL){
		oled_sram_string(current->name, page, col);
		current = current->next_sibling;
		page++;
	}
	oled_sram_char('*', selector_pos+1, 0);
	
}


menu* create_menu(char* new_name){
	menu* new_menu = (menu*)malloc(sizeof(menu));
	
	if(new_menu == NULL){
		printf("Out of mem\n");
		exit(1);
	}
	
	new_menu->name = new_name;
	new_menu->next_sibling = NULL;
	new_menu->prev_sibling = NULL;
	new_menu->parent = NULL;
	new_menu->child = NULL;
	new_menu->number_of_childs = 0;
	
	return new_menu;
}

menu* create_submenu(menu* parent_menu, menu* child_menu){ //tar inn liste av submenu struct
	if (parent_menu->child == NULL){
		//make new child
		parent_menu->child = child_menu;
	}
	
	else{
		//make new sibling
		menu* current = parent_menu->child;
		while (current->next_sibling != NULL){
			current = current->next_sibling;
		}
		
		current->next_sibling =child_menu;
		child_menu->prev_sibling =current;
		
	}
	parent_menu->number_of_childs++;
	child_menu->parent = parent_menu;
	
	return parent_menu;
}


menu* update_display_menu(menu* current_menu, int page, joystick_dir dir){
	menu* current = current_menu->child;
	if(dir == RIGHT){
		for(int i = 1; i < page; i++){
				current = current->next_sibling;
		}
	}else{
		current = current_menu->parent;
	}
	
	if(current != NULL){
		return current;
	}
	return current_menu;
}


void print_selection_sign(int page){
	oled_goto_column(0);
	oled_goto_page(page);
	oled_print_string("*");
}


void main_menu(void){
	
	int end_menu = 0; 
	joystick_dir joy_dir = find_joystick_dir();
	if(joy_dir != last_joy_dir){
		switch(joy_dir){
			case UP:
				if(current_page > 1){
					current_menu = current_menu->prev_sibling;
					current_page--;
				}
				menu_sram_update(display_menu, current_page);
				oled_update();
				break;
			case DOWN:
				if(current_page < display_menu->number_of_childs){
					current_menu = current_menu ->next_sibling;
					current_page++;
				}
				menu_sram_update(display_menu, current_page);
				oled_update();
				break;
			case RIGHT:
				if(current_menu->child != NULL){
					display_menu = update_display_menu(display_menu, current_page, RIGHT);
					current_page = 1;
					menu_sram_update(display_menu, current_page);
					oled_update();
					current_menu = current_menu->child;
				}
				else if(current_menu->parent->parent != NULL){
					end_menu = 1;
				}

				break;
		
			case LEFT:
				if(current_menu->parent->parent != NULL){
					display_menu = update_display_menu(display_menu, current_page, LEFT);
					current_page = 1;
					menu_sram_update(display_menu, current_page);
					oled_update();
					current_menu = current_menu->parent->parent->child;
				}
				
				break;
			default:
				break;
		}
		
	}
	
	last_joy_dir = joy_dir;

	
	if(end_menu){
		const char* menu_title = current_menu->name;
		if (!strcmp(menu_title,"Easy") && !strcmp(current_menu->parent->name, "Control: PS2")){
			current_state = PLAY;
			controller = PS2;
			difficulty = EASY;
		}else if (!strcmp(current_menu->name, "Medium")&& !strcmp(current_menu->parent->name, "Control: PS2")){
			current_state = PLAY;
			controller = PS2;
			difficulty = MEDIUM;
		}else if (!strcmp(current_menu->name, "Hard")&& !strcmp(current_menu->parent->name, "Control: PS2")){
			current_state = PLAY;
			controller = PS2;
			difficulty = HARD;
		}

		else if (!strcmp(current_menu->name,"Easy") && !strcmp(current_menu->parent->name, "Control: USB")){
			current_state = PLAY;
			controller = USB;
			difficulty = EASY;
			
		}else if (!strcmp(current_menu->name, "Medium")&& !strcmp(current_menu->parent->name, "Control: USB")){
			current_state = PLAY;
			controller = USB;
			difficulty = MEDIUM;
		}else if (!strcmp(current_menu->name, "Hard")&& !strcmp(current_menu->parent->name, "Control: USB")){
			current_state = PLAY;
			controller = USB;
			difficulty = HARD;
		}
		else if (!strcmp(current_menu->name,"View")){
			current_state = HIGHSCORE;
		}
		else if (!strcmp(current_menu->name, "YES")){
			current_state = RESET_HIGHSCORE;
			oled_sram_reset();
			oled_sram_string("****************",0,0);
			oled_sram_string("Highscore list",3,1);
			oled_sram_string("reset", 4, 5);
			oled_sram_string("****************",7,0);
			oled_update();
			_delay_ms(2000);
			
		}
		else if (!strcmp(current_menu->name, "NO")){
			current_state = IDLE;
		}
	}
}
