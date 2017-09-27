/*
 * menu_framework.h
 *
 * Created: 27.09.2017 14:05:58
 *  Author: andrholt
 */ 

#ifndef MENU_FRAMEWORK_H_
#define MENU_FRAMEWORK_H_

typedef struct menu_struct menu_struct;

struct menu_struct{
	char* name;
	menu_struct* next;
};

void print_menu_oled(menu_struct menu);
void menu_create(char* menu[], int size);
void menu_scroll_up(void);
void menu_scroll_down(void);
void menu_select(void);
void update_menu(void);



#endif /* MENU_FRAMEWORK_H_ */