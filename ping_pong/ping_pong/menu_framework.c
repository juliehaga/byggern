/*
 * menu_framework.c
 *
 * Created: 27.09.2017 14:05:47
 *  Author: andrholt
 */ 

#include "OLED_driver.h"
#include "menu_framework.h"
#include "driver_uart.h"
#include <stdlib.h>


#include <stddef.h>

int current_page = 1;
menu* display_menu;
joystick_dir last_joy_dir = CENTER;




void menu_setup(void){
	menu* menu_front_page = create_menu("How to steal");
	display_menu = menu_front_page;
	menu* sub1 = create_menu("Gal");
	menu* sub2 = create_menu("Kode");
	menu* sub3 = create_menu("USB-board");
	menu* subsub1 = create_menu("lur Bendik");
	menu* subsub2 = create_menu("facerape");

	create_submenu(menu_front_page, sub1);
	create_submenu(menu_front_page, sub2);
	create_submenu(menu_front_page, sub3);
	create_submenu(sub1, subsub1);
	create_submenu(sub2, subsub2);
	
	oled_reset();
	menu_sram_update(display_menu, current_page);
	oled_update();
}





void print_menu_oled(menu* menu_node, int page){
	oled_reset();
	oled_home();
	oled_print_string(menu_node->name);
	
	menu* current = menu_node->child;
	int page_count = 1; 
	while(current != NULL){
		oled_goto_page(page_count);
		oled_goto_column(15);
		oled_print_string(current->name);
		current = current->next_sibling;
		page_count++;
	}
	print_selection_sign(page);
	
}

void menu_sram_update(menu* menu_node, int selector_pos){
	int col = 0; 
	int page = 0; 
	oled_sram_reset();
	
	menu* current = menu_node->child;
	
	oled_sram_string(menu_node->name, page, col);
	
	page = 1;
	col = 2;
	while(current != NULL){
		oled_sram_string(current->name, page, col);
		current = current->next_sibling;
		page++;
	}
	oled_sram_char('*', selector_pos, 0);
	
}


menu* create_menu(char* new_name){
	menu* new_menu = (menu*)malloc(sizeof(menu));
	
	if(new_menu == NULL){
		printf("Out of memory! Failed to create menu");
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
	
	joystick_dir joy_dir = find_joystick_dir();
	printf("joystick dir %d \n", joy_dir);
	if(joy_dir != last_joy_dir){
		switch(joy_dir){
			case UP:
				if(current_page > 1){
					current_page--;
				}
				menu_sram_update(display_menu, current_page);
				oled_update();
				break;
			case DOWN:
				if(current_page < display_menu->number_of_childs){
					current_page++;
				}
				menu_sram_update(display_menu, current_page);
				oled_update();
				break;
			case RIGHT:
				display_menu = update_display_menu(display_menu, current_page, RIGHT);
				current_page = 1;
				menu_sram_update(display_menu, current_page);
				oled_update();
				break;
			case LEFT:
				display_menu = update_display_menu(display_menu, current_page, LEFT);
				current_page = 1;
				menu_sram_update(display_menu, current_page);
				oled_update();
				break;
			default:
				break;
		}
	}
	
	last_joy_dir = joy_dir;
}
