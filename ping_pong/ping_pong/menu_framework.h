/*
 * menu_framework.h
 *
 * Created: 27.09.2017 14:05:58
 *  Author: andrholt
 */ 

#ifndef MENU_FRAMEWORK_H_
#define MENU_FRAMEWORK_H_



typedef struct{
	char* name;
	struct menu** sub_menus;
	struct menu* prev;
	struct menu* next; 
	int size_submenu;
	int current_submenus; 
}menu;



void print_menu_oled(menu* menu_print);

menu* create_menu(char* new_name, int size_submenus);
void create_submenu(menu* parent_menu, menu* sub_menu);






void menu_create_main(char* menu[], int size);
void meny_create_sub(void);
void menu_scroll_up(void);
void menu_scroll_down(void);
void menu_select(void);
void update_menu(void);



#endif /* MENU_FRAMEWORK_H_ */