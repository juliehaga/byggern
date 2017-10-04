/*
 * menu_framework.c
 *
 * Created: 27.09.2017 14:05:47
 *  Author: andrholt
 */ 

#include "OLED_driver.h"
#include "menu_framework.h"
#include <stddef.h>



void print_menu_oled(menu* menu_node){
	oled_home();
	oled_print_string(menu_node->name);
	oled_goto_column(15);
	menu* counter = menu_node->sub_menus;
	
	
	for (int i = 1; i < menu_node->size_submenu+1; i++){
		oled_goto_page(i);
		oled_print_string(counter->name);
		counter += 1;
	}
}

menu* create_menu(char* new_name, int size_submenus){
	menu* new_menu = (menu*)malloc(sizeof(menu));
	
	if(new_menu == NULL){
		printf("Out of memory! Failed to create menu");
		exit(1);
	}
	new_menu->sub_menus = (menu*)malloc((size_submenus)*sizeof(menu));
	new_menu->sub_menus = NULL;
	
	new_menu->size_submenu = size_submenus;
	new_menu->name = new_name;
	new_menu->prev = NULL;
	new_menu->current_submenus = 0; 
	
	return new_menu;
}

void create_submenu(menu* parent_menu, menu* sub_menu){ //tar inn liste av submenu structs

	parent_menu->sub_menus = sub_menu;

	return parent_menu;
}

