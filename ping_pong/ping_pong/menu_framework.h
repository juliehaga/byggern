/*
 * menu_framework.h
 *
 * Created: 27.09.2017 14:05:58
 *  Author: andrholt
 */ 

#ifndef MENU_FRAMEWORK_H_
#define MENU_FRAMEWORK_H_



struct menu{
	char* name;
	struct menu* sub_menus;
	struct menu* prev;
	int size;
	void *(*print_menu)(struct menu*);
	
};

void print_menu_oled(menu_struct menu);
void menu_create_main(char* menu[], int size);
void meny_create_sub(void);
void menu_scroll_up(void);
void menu_scroll_down(void);
void menu_select(void);
void update_menu(void);



#endif /* MENU_FRAMEWORK_H_ */