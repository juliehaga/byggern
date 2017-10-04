/*
 * menu_framework.h
 *
 * Created: 27.09.2017 14:05:58
 *  Author: andrholt
 */ 

#ifndef MENU_FRAMEWORK_H_
#define MENU_FRAMEWORK_H_



typedef struct menu{
	char* name;
	struct menu* next_sibling;
	struct menu* prev_sibling;
	struct menu* child;
	struct menu* parent; 
	int number_of_childs; 
}menu;



void print_menu_oled(menu* menu_print);

menu* create_menu(char* new_name);
menu* create_submenu(menu* parent_menu, menu* child_menu);








#endif /* MENU_FRAMEWORK_H_ */