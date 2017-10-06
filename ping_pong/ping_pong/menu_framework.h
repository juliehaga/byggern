/*
 * menu_framework.h
 *
 * Created: 27.09.2017 14:05:58
 *  Author: andrholt
 */ 

#ifndef MENU_FRAMEWORK_H_
#define MENU_FRAMEWORK_H_
 
#include "joystick.h"

typedef struct menu{
	char* name;
	struct menu* next_sibling;
	struct menu* prev_sibling;
	struct menu* child;
	struct menu* parent; 
	int number_of_childs; 
}menu;



<<<<<<< HEAD
void print_menu_oled(menu* menu_print, int page);

=======
void print_menu_oled(menu* menu_print);
void print_menu_page(void);
>>>>>>> d8fe2f8554f76637ee35c7a76ac53d0a72acce3e
menu* create_menu(char* new_name);
menu* create_submenu(menu* parent_menu, menu* child_menu);
menu* update_display_menu(menu* current_menu, int page, joystick_dir dir);

void print_selection_sign(int page);






#endif /* MENU_FRAMEWORK_H_ */