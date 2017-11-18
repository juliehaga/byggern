/*
 * joystick.h
 *
 * Created: 04.10.2017 16:22:13
 *  Author: andrholt
 */ 


#ifndef JOYSTICK_H_
#define JOYSTICK_H_


#define CHANNEL_Y 4	
#define CHANNEL_X 5		
#define SLIDER_L 6
#define SLIDER_R 7

#define LEFT_BUTTON 1
#define RIGHT_BUTTON 2

typedef enum{UP, DOWN, RIGHT, LEFT, CENTER} joystick_dir;


int joystick_read(int channel);
int button_read(int button);
void send_slider_pos(void);
int read_joystick_button(void); 
joystick_dir find_joystick_dir(void); 



#endif /* JOYSTICK_H_ */