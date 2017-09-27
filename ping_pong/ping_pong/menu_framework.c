/*
 * menu_framework.c
 *
 * Created: 27.09.2017 14:05:47
 *  Author: andrholt
 */ 

#include "OLED_driver.h"
#include "menu_framework.h"




void print_menu_oled(menu_struct menu){
	oled_home();
	oled_print_string(menu.name);
}



/*








#define main_menu_size 4
#define submenu1_size 3
#define submenu2_size 0
#define submenu3_size 0

char* main_menu[main_menu_size] = {"MENU", "submenu1", "submenu2", "back"}; 
char* submenu1[submenu1_size] = { "submenuuuu1", "a", "b"};
char* submenu2[submenu2_size] = {};
char* submenu2[submenu3_size] = {}
 
int menu = 0;		//hvilken meny vi er på

menu* allmenus[10] ={}

struct menu{
	char* name;
	int size; 
	menu* sub_meny = NULL;
	menu* next_page = NULL;
	my_subs[size] = "back";
	void print_menu(void);
	};
	
julie.print_menu
	
menu main_menu("MENU", main_menu_size, NULL);
menu submenu1("submeny1", submenu1_size);
main_menu.next_menu =
menu submenu2( "submenu2", submenu2_size);
menu a("a",0);
menu b("b",0);
menu c("c",0);

main_menu.submenus[0] = submenu1;
main_menu.submenus[1] = submenu2; 

map menus<char*, char*[]>;

menu all[10];

all[0];
void menu_create(char* menu[], int size){
	oled_home();
	oled_print_string(menu[0]);
	for(int i = 1; i < size; i++){
		oled_pos(i, 16);
		oled_print_string(menu[i]);
	}
}
	
void update_menu(){
	switch(menu){
		case 0:
			menu_create(main_menu, main_menu_size);
			break;
		case 1:
			menu_create(submenu1, submenu1_size);
			break;
		case 2:
			menu_create(submenu2, submenu2_size);
			break;
	}
}

void menu_scroll_up(void){
	oled_goto_page(oled_return_page()+1);
	
}



void menu_scroll_down(void);

*/